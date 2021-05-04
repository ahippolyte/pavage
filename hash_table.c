#include "hash_table.h"

hash_s *hash_new(void) {
    hash_s *p_table = (hash_s *)malloc(sizeof(hash_s));
    if (p_table == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    p_table->size = 0;
    p_table->maxsize = 20;

    p_table->p_cell = (cell_s **)malloc(p_table->maxsize * sizeof(cell_s));
    if (p_table->p_cell == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < p_table->maxsize; i++) {
        p_table->p_cell[i] = (cell_s *)malloc(sizeof(cell_s));
        if (p_table->p_cell[i] == NULL) {
            fprintf(stderr, "Allocation failed!");
            exit(EXIT_FAILURE);
        }
    }

    for (uint i = 0; i < p_table->size; i++) {
        p_table->p_cell[i]->key = (point_s *)malloc(sizeof(point_s));
        if (p_table->p_cell[i]->key == NULL) {
            fprintf(stderr, "Allocation failed!");
            exit(EXIT_FAILURE);
        }
        p_table->p_cell[i]->height = 0;
    }

    return p_table;
}

void hash_print(hash_s *p_table) {
    if (p_table == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    printf(" ______________________\n");
    printf("|_____ HASH TABLE _____|\n\n");
    printf("Size: %u\n", p_table->size);
    printf("Capacity: %u\n", p_table->maxsize);
    printf("________________________\n\n");
    for (uint i = 0; i < p_table->size; i++) {
        printf("ELEMENT %u\n", i);
        printf("points: ");
        point_print(p_table->p_cell[i]->key);
        printf("Height: %d\n", p_table->p_cell[i]->height);
        printf("---------\n");
    }
    printf(" _______________________ \n");
    printf("|_________ END _________|\n");
    return;
}

void hash_add(hash_s *p_table, const point_s *key, int height) {
    if (p_table == NULL || key == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    p_table->size++;
    if (p_table->size >= p_table->maxsize) {
        p_table = realloc(p_table, 2 * p_table->maxsize * sizeof(hash_s));
        if (p_table == NULL) {
            fprintf(stderr, "Reallocation failed!");
            exit(EXIT_FAILURE);
        }
    }
    p_table->p_cell[p_table->size - 1]->key = point_new(key->x, key->y);
    p_table->p_cell[p_table->size - 1]->height = height;

    return;
}

int hash_search(hash_s *p_table, const point_s *key) {
    if (p_table == NULL || key == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < p_table->size; i++) {
        if (point_is_equal(p_table->p_cell[i]->key, key) == true) {
            return p_table->p_cell[i]->height;
        }
    }

    return INT_MAX;
}

void hash_delete(hash_s *p_table) {
    if (p_table == NULL) {
        fprintf(stderr, "Invalid pointer adress!");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < p_table->maxsize; i++) {
        point_delete(p_table->p_cell[i]->key);
        free(p_table->p_cell[i]);
    }
    free(p_table->p_cell);
    free(p_table);
    return;
}