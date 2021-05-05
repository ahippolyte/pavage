#include "pavage.h"

state fill_map_edge_from_direction_list(direction *list_of_direction, int nb_of_direction , hash_s *map_of_height, int* nb_half_point, point_s* *half_points) {
    if (list_of_direction == NULL) {
        return ERROR_DIRECTION_TABLE;
    }

    if (map_of_height == NULL) {
        return ERROR_MAP;
    }
    
    point_s * first_point = point_new(0, 0);
    point_s * last_point = first_point;
    direction new_direction = 0;
    point_s *new_point = NULL;

    for (int i = 0; i< nb_of_direction; i++){
        new_direction = list_of_direction[i];
        new_point = next_point(last_point, new_direction);

        if (hash_search(map_of_height, new_point) != INT_MAX && i != nb_of_direction-1) {
            return EDGE_IS_LOOPING;
        }

        cell_s* cell = cell_new(new_point, calculate_height(last_point, hash_search(map_of_height, last_point), new_direction));

        hash_add(map_of_height, cell);

        if (new_direction == NORTH){
            half_points[*nb_half_point] = point_new( (last_point->x), (last_point->y) + 0.5);
            *nb_half_point += 1;
        }
        if (new_direction == SOUTH){
            half_points[*nb_half_point] = point_new( (last_point->x), (last_point->y) - 0.5);
            *nb_half_point += 1;
        }

        last_point = new_point;
    }

    if (!point_is_equal(new_point, first_point)) {
        point_delete(first_point);
        return EDGE_IS_DISCONNECTED;
    }
    point_delete(first_point);

    if (hash_search(map_of_height, last_point) != 0){
        hash_print(map_of_height);
        return AREA_IS_NOT_PAVABLE;
    }

    return AREA_IS_MAYBE_PAVABLE;
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

point_s *next_point(point_s *c, direction d) {
    if (c == NULL) {
        fprintf(stderr, "invalid pointer adresse");
        exit(EXIT_FAILURE);
    }
    point_s *next_c = point_new(c->x, c->y);
    if (d == NORTH) {
        next_c->y++;
    }
    if (d == SOUTH) {
        next_c->y--;
    }
    if (d == EST) {
        next_c->x++;
    }
    if (d == WEST) {
        next_c->x--;
    }
    return next_c;
}

int calculate_height(point_s *old_point, int old_height, direction direction) {
    int height = old_height;
    if (abs((int)old_point->x%2) == abs((int)old_point->y%2)) {
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
