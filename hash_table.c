#include "hash_table.h"

hash_s *hash_new(const uint size) {
    hash_s *hash = (hash_s *)malloc(sizeof(hash_s));
    if (hash == NULL) {
        fprintf(stderr, "Hash allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    hash->p_cell = (cell_s **)malloc(size * sizeof(cell_s));
    if (hash->p_cell == NULL) {
        fprintf(stderr, "Hash cell tab allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=0; i<size; i++) {
        hash->p_cell[i] = cell_new(0, 0, 0);
    }
    hash->size = size;
    hash->index = 0;

    return hash;
}

point_s* hash_get_point(hash_s* hash, const uint index){
    if (hash == NULL) {
        fprintf(stderr, "Invalid pointer reference (hash_get_point)\n");
        exit(EXIT_FAILURE);
    }
    return hash->p_cell[index]->point;
}

int hash_get_index(hash_s *hash, const point_s *point){
    if (hash == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference (hash_get_index)\n");
        exit(EXIT_FAILURE);
    }
    
    for(uint i=0; i<hash->size; i++){
        if(point_is_equal(hash->p_cell[i]->point, point)){
            return i;
        }
    }
    return -1;
}

int hash_search(hash_s *hash, const point_s *point) {
    if (hash == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference (hash_search)\n");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < hash->size; i++) {
        if (point_is_equal(hash->p_cell[i]->point, point) == true) {
            return hash->p_cell[i]->height;
        }
    }

    return INT_MAX;
}

void hash_add(hash_s *hash, const point_s *point, const int height) {
    if (hash == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference (hash_add)\n");
        exit(EXIT_FAILURE);
    }

    if (hash->index >= hash->size) {
        printf("Hash is full!\n");
        return;
    }

    cell_set_point(hash->p_cell[hash->index], point);
    cell_set_height(hash->p_cell[hash->index], height);
    hash->index++;

    return;
}

void hash_print(const hash_s *hash) {
    if (hash == NULL) {
        fprintf(stderr, "Invalid pointer reference (hash_print)\n");
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

void hash_delete(hash_s *hash) {
    if (hash == NULL) {
        fprintf(stderr, "Invalid pointer adress (hash_delete)\n");
        exit(EXIT_FAILURE);
    }
    for (uint i = 0; i < hash->size; i++) {
        cell_delete(hash->p_cell[i]);
    }
    free(hash->p_cell);
    free(hash);
}