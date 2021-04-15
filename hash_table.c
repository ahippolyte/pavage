#include "hash_table.h"

<<<<<<< HEAD
hash_s *hash_new(void) {
    hash_s *p_table = malloc(sizeof(hash_s));
    if (p_table == NULL) {
        fprintf(stderr, "Allocation failed!");
=======
hash_s *hash_new(void)
{
    hash_s *p_table = malloc(sizeof(hash_s));
    if (p_table == NULL)
    {
        printf("Allocation failed!");
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
        exit(EXIT_FAILURE);
    }
    p_table->size = 0;
    p_table->maxsize = 20;

<<<<<<< HEAD
    p_table->p_cell = malloc(p_table->maxsize * sizeof(cell_s));
    if (p_table->p_cell == NULL) {
        fprintf(stderr, "Allocation failed!");
=======
    p_table->p_cell = malloc(p_table->size * sizeof(cell_s));
    if (p_table->p_cell == NULL)
    {
        printf("Allocation failed!");
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
        exit(EXIT_FAILURE);
    }

    p_table->p_cell->key = malloc(sizeof(coordinate_s));
<<<<<<< HEAD
    if (p_table->p_cell->key == NULL) {
        fprintf(stderr, "Allocation failed!");
=======
    if (p_table->p_cell->key == NULL)
    {
        printf("Allocation failed!");
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
        exit(EXIT_FAILURE);
    }

    return (p_table);
}

<<<<<<< HEAD
void hash_add(hash_s *p_table, const coordinate_s *key, int high) {
    p_table->size++;
    if (p_table->size >= p_table->maxsize) {
        realloc(p_table, 2 * p_table->maxsize * sizeof(hash_s));
        if (p_table == NULL) {
            fprintf(stderr, "Reallocation failed!");
            exit(EXIT_FAILURE);
        }
    }
    p_table->p_cell[p_table->size - 1]->key->x = key->x;
    p_table->p_cell[p_table->size - 1]->key->y = key->y;
    p_table->p_cell[p_table->size - 1]->high = high;

    return;
}
=======
void hash_add(hash_s *p_table, const char *key, void *data)
{
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e

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
}**/

<<<<<<< HEAD
void *hash_search(hash_s *p_table, const char *key) {
=======
void *hash_search(hash_s *p_table, const char *key)
{
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
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

<<<<<<< HEAD
void hash_delete(hash_s **p_table) {
=======
void hash_delete(hash_s **p_table)
{
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
    int i;
    for (i = 0; i < (*p_table)->size; i++) free((*p_table)->p_cell[i].key);
    free((*p_table)->p_cell);
    free(*p_table);
    *p_table = NULL;
    return;
}