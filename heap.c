#include "heap.h"

heap_s *heap_new(uint size) {
    heap_s *heap = (heap_s *)malloc(sizeof(heap_s));
    if (heap == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    heap->array = (int *)malloc(size * sizeof(int));
    if (heap->array == NULL) {
        fprintf(stderr, "Allocation failed\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    heap->nmax = size;
    heap->n = 0;
    return heap;
}

// Détruit le tas h. On supposera h!=NULL. Attention ! Il s'agit de
// libérer ce qui a été alloué par heap_create(). NB: Les objets
// stockés dans le tas n'ont pas à être libérés.
void heap_delete(heap_s *heap) {
    if (heap == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    free(heap->array);
    free(heap);
}

bool heap_empty(heap_s *heap) {
    if (heap == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    if (heap->n == 0) {
        return true;
    }
    return false;
}

void heap_add(heap_s *heap, int value) {
    if (heap == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }

    heap->n++;
    if (heap->n >= heap->nmax) {
        fprintf(stderr, "Heap is full!\n");
        exit(EXIT_FAILURE);
    }

    heap->array[heap->n] = value;

    while (heap->n > 1 && heap->array[heap->n] > heap->array[heap->n / 2]) {
        int temp = heap->array[heap->n];
        heap->array[heap->n / 2] = heap->array[heap->n];
        heap->array[heap->n] = temp;
    }
}

// Renvoie l'objet en haut du tas h, c'est-à-dire l'élément minimal
// selon f(), sans le supprimer. On supposera h!=NULL. Renvoie NULL si
// le tas est vide.
int heap_top(heap_s *heap) {
    if (!heap_empty(heap)) return heap->array[1];
    return INT_MAX;
}

// Comme heap_top() sauf que l'objet est en plus supprimé du
// tas. Renvoie NULL si le tas est vide.
int heap_pop(heap_s *heap) { return 0; }

// affiche le contenu du tas h d'éléments de type t
// sous la forme d'un arbre
void heap_print(heap_s *heap) { printf("Min : %d\n", heap->array[1]); }