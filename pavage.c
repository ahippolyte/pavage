#include "pavage.h"

how_fill_fonction_worked fill_map_edge_from_direction_list_recur(queue_s *list_of_direction, hash_s *map_of_height, point_s *last_point,
                                                                 point_s **inter_points, uint *nb_inter_points) {
    if (list_of_direction == NULL) {
        return ERROR_DIRECTION_TABLE;
    }

    if (map_of_height == NULL) {
        return ERROR_MAP;
    }

    point_s *starting_point = point_new(0, 0);

    if (queue_is_empty(list_of_direction)) {
        if (point_is_equal(last_point, starting_point)) {
            return EDGE_IS_CONNECTED;
        } else {
            return EDGE_IS_DISCONNECTED;
        }
    }

    direction new_direction = queue_peek(list_of_direction);
    queue_dequeue(list_of_direction);
    point_s *new_point = next_point(last_point, new_direction);

    if (new_direction == NORTH) {
        inter_points[*nb_inter_points] = point_new(new_point->x, new_point->y - 0.5);
        nb_inter_points++;
    } else if (new_direction == SOUTH) {
        inter_points[*nb_inter_points] = point_new(new_point->x, new_point->y - 0.5);
        *nb_inter_points++;
    }

    if (point_is_equal(new_point, starting_point) && queue_is_empty(list_of_direction)) {
        if (calculate_height(last_point, hash_search(map_of_height, last_point), new_direction) == 0) {
            return SHAPE_IS_MAYBE_PAVABLE;
        } else {
            return SHAPE_IS_NOT_PAVABLE;
        }
    }

    if (hash_search(map_of_height, new_point) != INT_MAX) {
        return EDGE_IS_DISCONNECTED;
    }

    hash_add(map_of_height, new_point, calculate_height(last_point, hash_search(map_of_height, last_point), new_direction));

    return fill_map_edge_from_direction_list_recur(list_of_direction, map_of_height, new_point, inter_points, nb_inter_points);
}

how_fill_fonction_worked fill_map_edge_from_direction_list(queue_s *list_of_direction, hash_s *map_of_height, point_s **inter_points,
                                                           uint *nb_inter_points) {
    point_s *first = point_new(0, 0);
    hash_add(map_of_height, first, 0);
    *nb_inter_points = 0;

    return fill_map_edge_from_direction_list_recur(list_of_direction, map_of_height, first, inter_points, nb_inter_points);
}

int Xmin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->x < min) {
            min = hash->p_cell[i]->key->x;
        }
    }
    return min;
}

int Xmax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->x > max) {
            max = hash->p_cell[i]->key->x;
        }
    }
    return max;
}

int Ymin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->y < min) {
            min = hash->p_cell[i]->key->y;
        }
    }
    return min;
}

int Ymax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->y > max) {
            max = hash->p_cell[i]->key->y;
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
    if ((int)old_point->x % 2 == (int)old_point->y % 2) {
        if (direction == EST || direction == WEST) {
            old_height--;
        }
        if (direction == NORTH || direction == SOUTH) {
            old_height++;
        }
    } else {
        if (direction == EST || direction == WEST) {
            old_height++;
        }
        if (direction == NORTH || direction == SOUTH) {
            old_height--;
        }
    }
    return old_height;
}
