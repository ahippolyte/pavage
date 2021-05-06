#include "hash_table.h"

hash_s *hash_new(uint size) {
    hash_s *hash = (hash_s *)malloc(sizeof(hash_s));
    if (hash == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    hash->p_cell = (cell_s **)malloc(size * sizeof(cell_s));
    if (hash->p_cell == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < size; i++) {
        hash->p_cell[i] = cell_new(0, 0, 0);
    }
    hash->size = size;
    hash->index = 0;

    return hash;
}

void hash_print(hash_s *hash) {
    if (hash == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    printf(" ______________________\n");
    printf("|_____ HASH TABLE _____|\n\n");
    printf("Size: %u\n", hash->size);
    printf("________________________\n\n");
    for (uint i = 0; i < hash->size; i++) {
        printf("ELEMENT %u\n", i);
        printf("points: ");
        point_print(hash->p_cell[i]->point);
        printf("Height: %d\n", hash->p_cell[i]->height);
        printf("---------\n");
    }
    printf(" _______________________ \n");
    printf("|_________ END _________|\n");
    return;
}

void hash_add(hash_s *hash, point_s *point, int height) {
    if (hash == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if (hash->index > hash->size) {
        printf("Hash is full!\n");
        return;
    }

    cell_set_point(hash->p_cell[hash->index], point);
    cell_set_height(hash->p_cell[hash->index], height);
    hash->index++;

    return;
}

int hash_search(hash_s *hash, const point_s *point) {
    if (hash == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < hash->size; i++) {
        if (point_is_equal(hash->p_cell[i]->point, point) == true) {
            return hash->p_cell[i]->height;
        }
    }

    return INT_MAX;
}

void hash_delete(hash_s *hash) {
    if (hash == NULL) {
        fprintf(stderr, "Invalid pointer adress!");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < hash->size; i++) {
        cell_delete(hash->p_cell[i]);
    }
    free(hash->p_cell);
    free(hash);
}