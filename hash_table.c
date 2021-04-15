#include "hash_table.h"

hash_s *hash_new(void) {
    hash_s *p_table = malloc(sizeof(hash_s));
    if (p_table == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    p_table->size = 0;
    p_table->maxsize = 20;

    p_table->p_cell = malloc(p_table->maxsize * sizeof(cell_s));
    if (p_table->p_cell == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    for(uint i=0; i<p_table->size; i++){
        p_table->p_cell[i]->key = malloc(sizeof(coordinate_s));
        if (p_table->p_cell[i]->key == NULL) {
            fprintf(stderr, "Allocation failed!");
            exit(EXIT_FAILURE);
        }
        p_table->p_cell[i]->height = 0;
    }

    return p_table;
}

void hash_add(hash_s *p_table, const coordinate_s *key, int height) {
    if(p_table == NULL || key == NULL){
        printf("Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    p_table->size++;
    if (p_table->size >= p_table->maxsize) {
        realloc(p_table, 2 * p_table->maxsize * sizeof(hash_s));
        if (p_table == NULL) {
            fprintf(stderr, "Reallocation failed!");
            exit(EXIT_FAILURE);
        }
    }
    p_table->p_cell[p_table->size - 1]->key = coordinate_new(key->x, key->y);
    p_table->p_cell[p_table->size - 1]->height = height;

    return;
}


int *hash_search(hash_s *p_table, const coordinate_s *key) {
    if(p_table == NULL || key == NULL){
        printf("Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    for(uint i=0; i<p_table->size; i++){
        if(coordinate_compare(p_table->p_cell[i]->key, key) == true){
            return p_table->p_cell[i]->height;
        }
    }

    return INT_MAX;
}

void hash_delete(hash_s *p_table) {
    if(p_table == NULL){
        fprintf(stderr, "Invalid pointer adress!");
        exit(EXIT_FAILURE);
    }
    for(uint i=0; i<p_table->size; i++){
        coordinate_delete(p_table->p_cell[i]->key);
        free(p_table->p_cell[i]);
    }
    free(p_table->p_cell);
    free(p_table);
    return;
}

//Old functions

/**void hash_add(hash_s *p_table, const char *key, void *data) {
    if (p_table != NULL && key != NULL) {
        int i = 0;
        cell_s *p_cell = NULL;
        char *tmp_key = NULL;

        while (i < p_table->size) {
            if (strcmp(p_table->p_cell[i].key, key) == 0) {
                p_cell = &p_table->p_cell[i];
                break;
            }
            i++;
        }

        if (p_cell == NULL) {
            p_table->size++;
            tmp = realloc(p_table->p_cell, sizeof(*p_table->p_cell) * p_table->size);
            if (tmp != NULL) {
                p_table->p_cell = tmp;
                p_cell = &p_table->p_cell[p_table->size - 1];
                p_cell->key = NULL;
            } else {
                fprintf(stderr, "Memoire insufisante\n");
                exit(EXIT_FAILURE);
            }

            tmp = realloc(p_cell->key, sizeof(*p_cell->key) * (strlen(key) + 1));
            if (tmp != NULL) {
                p_cell->key = tmp;
                strcpy(p_cell->key, key);
                p_cell->data = data;
            } else {
                fprintf(stderr, "Memoire insufisante\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void *hash_search(hash_s *p_table, const char *key) {
    void *data = NULL;
    if (p_table != NULL && key != NULL) {
        int i = 0;
        while (i < p_table->size) {
            if (strcmp(p_table->p_cell[i].key, key) == 0) {
                data = p_table->p_cell[i].data;
                break;
            }
            i++;
        }
    }
    return (data);
}

void hash_delete(hash_s *p_table) {
    int i;
    for (i = 0; i < (*p_table)->size; i++) free((*p_table)->p_cell[i].key);
    free((*p_table)->p_cell);
    free(*p_table);
    *p_table = NULL;
    return;
}
**/