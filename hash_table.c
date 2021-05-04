#include "hash_table.h"

hash_s* hash_new(uint size) {
    hash_s* hash = (hash_s*)malloc(sizeof(hash_s));
    if (hash == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    hash->p_cell = (cell_s**)malloc(size*sizeof(cell_s));
    if (hash->p_cell == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    for (uint i=0; i<size; i++) {
        hash->p_cell[i] = (cell_s*)malloc(sizeof(cell_s));
        if (hash->p_cell[i] == NULL) {
            fprintf(stderr, "Allocation failed!");
            exit(EXIT_FAILURE);
        }
    }

    for (uint i=0; i<size; i++) {
        hash->p_cell[i]->key = point_new(0,0);
        hash->p_cell[i]->height = 0;
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
        point_print(hash->p_cell[i]->key);
        printf("Height: %d\n", hash->p_cell[i]->height);
        printf("---------\n");
    }
    printf(" _______________________ \n");
    printf("|_________ END _________|\n");
    return;
}

void hash_add(hash_s *hash, const point_s *key, int height) {
    if (hash == NULL || key == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if(hash->index > hash->size){
        printf("Hash is full!\n");
        return;
    }

    hash->p_cell[hash->index]->key->x = key->x;
    hash->p_cell[hash->index]->key->y = key->y;
    hash->p_cell[hash->index]->height = height;
    hash->index++;

    return;
}

int hash_search(hash_s *hash, const point_s *key) {
    if (hash == NULL || key == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < hash->size; i++) {
        if (point_is_equal(hash->p_cell[i]->key, key) == true) {
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
        point_delete(hash->p_cell[i]->key);
        free(hash->p_cell[i]);
    }
    free(hash->p_cell);
    free(hash);
    return;
}