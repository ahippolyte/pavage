#include "pavage.h"

state fill_map_edge_from_direction_list(direction *list_of_direction, int nb_of_direction, hash_s *map_of_height, int *nb_half_point,
                                        point_s **half_points) {
    if (list_of_direction == NULL) {
        return ERROR_DIRECTION_TABLE;
    }

    if (map_of_height == NULL) {
        return ERROR_MAP;
    }

    point_s *last_point = point_new(0, 0);
    point_s *new_point = point_new(0, 0);
    direction new_direction = 0;
    
    for (int i = 0; i < nb_of_direction; i++) {
        new_direction = list_of_direction[i];
        //new_point = next_point(last_point, new_direction);
        point_set_coordinates(new_point, last_point->x, last_point->y);
        next_point(new_point, new_direction);


        if (hash_search(map_of_height, new_point) != INT_MAX && i != nb_of_direction - 1) {
            point_delete(last_point);
            point_delete(new_point);
            return EDGE_IS_LOOPING;
        }

        hash_add(map_of_height, new_point, calculate_height(last_point, hash_search(map_of_height, last_point), new_direction));
        
        if (new_direction == NORTH) {
            half_points[*nb_half_point] = point_new((last_point->x), (last_point->y) + 0.5);
            *nb_half_point += 1;
        }
        if (new_direction == SOUTH) {
            half_points[*nb_half_point] = point_new((last_point->x), (last_point->y) - 0.5);
            *nb_half_point += 1;
        }

        point_set_coordinates(last_point, new_point->x, new_point->y);
    }

    if (!point_check_coordinates(new_point, 0, 0)){
        point_delete(last_point);
        point_delete(new_point);
        return EDGE_IS_DISCONNECTED;
    }

    if (hash_search(map_of_height, last_point) != 0) {
        point_delete(last_point);
        point_delete(new_point);
        return AREA_IS_NOT_PAVABLE;
    }

    //point_delete(last_point);
    point_delete(new_point);
    return AREA_IS_MAYBE_PAVABLE;
}

bool is_map_pavable(heap_s *heap_of_point, hash_s *map_of_height, point_s **half_points, uint nb_half_points, int x_max) {
    cell_s *cellule;
    point_s *point;
    int hauteur;

    point_s *point_suivant = point_new(0,0);
    cell_s *new_cell;

    while (!heap_empty(heap_of_point)) {
        cellule = heap_pop(heap_of_point);

        point = cellule->point;
        hauteur = cellule->height;

        if (abs((int)point->x % 2) == abs((int)point->y % 2)) {  // On a du noirs en haut a gauche donc on ne doit tester que Nord et Sud

            // NORD
            point_set_coordinates(point_suivant, point->x, point->y);
            next_point(point_suivant, NORTH);
            if (is_inside(map_of_height, point_suivant, half_points, nb_half_points, x_max)) {
                if (hash_search(map_of_height, point_suivant) == INT_MAX) {
                    hash_add(map_of_height, point_suivant, hauteur + 1);
                    new_cell = cell_new(point_suivant->x, point_suivant->y, hauteur + 1);
                    heap_add(heap_of_point, new_cell);
                }

                else {
                    if (hash_search(map_of_height, point_suivant) != hauteur + 1 && hash_search(map_of_height, point_suivant) != hauteur + 3
                        && hash_search(map_of_height, point_suivant) != hauteur - 1 && hash_search(map_of_height, point_suivant) != hauteur - 3) {
                        cell_delete(cellule);
                        //cell_delete(new_cell);
                        point_delete(point_suivant);
                        heap_delete(heap_of_point);
                        return false;
                    }
                }
            }

            // SUD
            point_set_coordinates(point_suivant, point->x, point->y);
            next_point(point_suivant, SOUTH);
            if (is_inside(map_of_height, point_suivant, half_points, nb_half_points, x_max)) {
                if (hash_search(map_of_height, point_suivant) == INT_MAX) {
                    hash_add(map_of_height, point_suivant, hauteur + 1);
                    new_cell = cell_new(point_suivant->x, point_suivant->y, hauteur + 1);
                    heap_add(heap_of_point, new_cell);
                }

                else {
                    if (hash_search(map_of_height, point_suivant) != hauteur + 1 && hash_search(map_of_height, point_suivant) != hauteur + 3
                        && hash_search(map_of_height, point_suivant) != hauteur - 1 && hash_search(map_of_height, point_suivant) != hauteur - 3) {
                        cell_delete(cellule);
                        //cell_delete(new_cell);
                        point_delete(point_suivant);
                        heap_delete(heap_of_point);
                        return false;
                    }
                }
            }
        } else {
            // EST
            point_set_coordinates(point_suivant, point->x, point->y);
            next_point(point_suivant, EST);
            if (is_inside(map_of_height, point_suivant, half_points, nb_half_points, x_max)) {
                if (hash_search(map_of_height, point_suivant) == INT_MAX) {
                    hash_add(map_of_height, point_suivant, hauteur + 1);
                    new_cell = cell_new(point_suivant->x, point_suivant->y, hauteur + 1);
                    heap_add(heap_of_point, new_cell);
                }

                else {
                    if (hash_search(map_of_height, point_suivant) != hauteur + 1 && hash_search(map_of_height, point_suivant) != hauteur + 3
                        && hash_search(map_of_height, point_suivant) != hauteur - 1 && hash_search(map_of_height, point_suivant) != hauteur - 3) {
                        cell_delete(cellule);
                        //cell_delete(new_cell);
                        point_delete(point_suivant);
                        heap_delete(heap_of_point);
                        return false;
                    }
                }
            }

            // WEST
            point_set_coordinates(point_suivant, point->x, point->y);
            next_point(point_suivant, WEST);
            if (is_inside(map_of_height, point_suivant, half_points, nb_half_points, x_max)) {
                if (hash_search(map_of_height, point_suivant) == INT_MAX) {
                    hash_add(map_of_height, point_suivant, hauteur + 1);
                    new_cell = cell_new(point_suivant->x, point_suivant->y, hauteur + 1);
                    heap_add(heap_of_point, new_cell);
                }

                else {
                    if (hash_search(map_of_height, point_suivant) != hauteur + 1 && hash_search(map_of_height, point_suivant) != hauteur + 3
                        && hash_search(map_of_height, point_suivant) != hauteur - 1 && hash_search(map_of_height, point_suivant) != hauteur - 3) {
                        cell_delete(cellule);
                        //cell_delete(new_cell);
                        point_delete(point_suivant);
                        heap_delete(heap_of_point);
                        return false;
                    }
                }
            }
        }
        cell_delete(cellule);
    }

    //cell_delete(new_cell);
    point_delete(point_suivant);
    heap_delete(heap_of_point);
    return true;
}

bool point_belong_to(point_s *point, point_s **tab, uint size) {
    for (uint i = 0; i < size; i++) {
        if (point_is_equal(point, tab[i])) {
            return true;
        }
    }
    return false;
}

bool is_inside(hash_s* hash_of_point, point_s *point, point_s **half_points, uint nb_half_points, int x_max) {
    if(hash_search(hash_of_point, point) != INT_MAX) return true;
    point_s *p = point_new(point->x, point->y+0.5);
    uint cpt = 0;
    while (p->x <= x_max) {
        if (point_belong_to(p, half_points, nb_half_points)) {
            cpt++;
        }
        next_point(p, EST);
    }
    if (cpt % 2 == 1){
        point_delete(p);
        return true;
    }
    point_delete(p);
    return false;
}

/**   X Y min max   **/

int Xmin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->point->x < min) {
            min = hash->p_cell[i]->point->x;
        }
    }
    return min;
}

int Xmax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->point->x > max) {
            max = hash->p_cell[i]->point->x;
        }
    }
    return max;
}

int Ymin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->point->y < min) {
            min = hash->p_cell[i]->point->y;
        }
    }
    return min;
}

int Ymax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->point->y > max) {
            max = hash->p_cell[i]->point->y;
        }
    }
    return max;
}

/**   Auxiliary function for fill_map_edge_from_direction_list   **/

void next_point(point_s *c, direction d) {
    if (c == NULL) {
        fprintf(stderr, "invalid pointer adresse");
        exit(EXIT_FAILURE);
    }
    
    if (d == NORTH) {
        point_set_y(c, c->y+1);
    }
    else if (d == SOUTH) {
        point_set_y(c, c->y-1);
    }
    else if (d == EST) {
        point_set_x(c, c->x+1);
    }
    else if (d == WEST) {
        point_set_x(c, c->x-1);
    }
}

int calculate_height(point_s *old_point, int old_height, direction direction) {
    int height = old_height;
    if (abs((int)old_point->x % 2) == abs((int)old_point->y % 2)) {
        if (direction == EST || direction == WEST) {
            height--;
        }
        if (direction == NORTH || direction == SOUTH) {
            height++;
        }
    } else {
        if (direction == EST || direction == WEST) {
            height++;
        }
        if (direction == NORTH || direction == SOUTH) {
            height--;
        }
    }
    return height;
}
