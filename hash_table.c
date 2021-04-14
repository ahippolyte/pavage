#include "hash_table.h"

hach_s *hach_new(void)
{
    hach_s *p_table = malloc(sizeof(hach_s));
    if (p_table == NULL)
    {
        printf("Allocation failed!");
        exit(EXIT_FAILURE);
    }
    p_table->size = 0;

    p_table->p_cell = malloc(p_table->size*sizeof(cell_s));
    if(p_table->p_cell == NULL){
        printf("Allocation failed!");
        exit(EXIT_FAILURE);
    }

    p_table->p_cell->key = malloc(sizeof(coordinate_s));
    if(p_table->p_cell->key == NULL){
        printf("Allocation failed!");
        exit(EXIT_FAILURE);
    }

    return (p_table);
}

void hach_add(hach_s *p_table, const char *key, void *data){

    if (p_table != NULL && key != NULL)
    {
        int i = 0;
        cell_s *p_cell = NULL;
        char *tmp_key = NULL;

        while (i < p_table->size)
        {
            if (strcmp(p_table->p_cell[i].key, key) == 0)
            {
                p_cell = &p_table->p_cell[i];
                break;
            }
            i++;
        }

        if (p_cell == NULL)
        {
            p_table->size++;
            tmp = realloc(p_table->p_cell, sizeof(*p_table->p_cell) * p_table->size);
            if (tmp != NULL)
            {
                p_table->p_cell = tmp;
                p_cell = &p_table->p_cell[p_table->size - 1];
                p_cell->key = NULL;
            }
            else
            {
                fprintf(stderr, "Memoire insufisante\n");
                exit(EXIT_FAILURE);
            }

            tmp = realloc(p_cell->key, sizeof(*p_cell->key) * (strlen(key) + 1));
            if (tmp != NULL)
            {
                p_cell->key = tmp;
                strcpy(p_cell->key, key);
                p_cell->data = data;
            }
            else
            {
                fprintf(stderr, "Memoire insufisante\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void *hach_search(hach_s *p_table, const char *key)
{
    void *data = NULL;
    if (p_table != NULL && key != NULL)
    {
        int i = 0;
        while (i < p_table->size)
        {
            if (strcmp(p_table->p_cell[i].key, key) == 0)
            {
                data = p_table->p_cell[i].data;
                break;
            }
            i++;
        }
    }
    return (data);
}

void hach_delete(hach_s **p_table)
{
    int i;
    for (i = 0; i < (*p_table)->size; i++)
        free((*p_table)->p_cell[i].key);
    free((*p_table)->p_cell);
    free(*p_table);
    *p_table = NULL;
    return;
}