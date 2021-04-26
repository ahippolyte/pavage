#include "pavage.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

coordinate_s next_coordinate(coordinate_s *c, direction d) {
    if (d == NORTH) {
        c->y++;
    }
    if (d == SOUTH) {
        c->y--;
    }
    if (d == EST) {
        c->x++;
    }
    if (d == WEST) {
        c->x--;
    }
    return *c;
}
