#include "pavage.h"

/**       X/Y min/max      **/

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

coordinate_s next_coordinate(coordinate_s *c, direction d) {
    if (c == NULL) {
        fprintf(stderr, "invalid pointer adresse");
        exit(EXIT_FAILURE);
    }
    coordinate_s *next_c = coordinate_new(c->x, c->y);
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
    return *next_c;
}

int calculate_height(coordinate_s *old_coordinate, int old_height, direction direction) {
    if (old_coordinate->x % 2 == old_coordinate->y % 2) {
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
