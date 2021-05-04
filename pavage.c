#include "pavage.h"

state fill_map_edge_from_direction_list(direction *list_of_direction, int nb_of_direction , hash_s *map_of_height) {
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

        if (hash_search(map_of_height, new_point) != INT_MAX) {
            return EDGE_IS_LOOPING;
        }

        hash_add(map_of_height, new_point, calculate_height(last_point, hash_search(map_of_height, last_point), new_direction));

        last_point = new_point;
    }

    if (!point_is_equal(new_point, first_point)) {
        point_delete(first_point);
        return EDGE_IS_DISCONNECTED;
    }
    point_delete(first_point);

    if (hash_search(map_of_height, last_point) != 0){
        return AREA_IS_NOT_PAVABLE;
    }

    return AREA_IS_MAYBE_PAVABLE;
}



/**   X Y min max   **/


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
    if ((int)old_point->x%2 == (int)old_point->y%2) {
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
