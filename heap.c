#include "heap.h"

heap_s *heap_new(uint size) {
    heap_s *heap = (heap_s *)malloc(sizeof(heap_s));
    if (heap == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    heap->array = (int *)malloc((size+1) * sizeof(int));
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
    
    if (heap->n >= heap->nmax) {
        fprintf(stderr, "Heap is full!\n");
        return;
    }

    heap->n++;

    heap->array[heap->n] = value;
    int i = heap->n;
    while (i > 1 && heap->array[i] < heap->array[i / 2]) {
        int temp = heap->array[i / 2];
        heap->array[i / 2] = heap->array[i];
        heap->array[i] = temp;
        i /= 2;
    }
}

// Renvoie l'objet en haut du tas h, c'est-à-dire l'élément minimal
// selon f(), sans le supprimer. On supposera h!=NULL. Renvoie NULL si
// le tas est vide.
int heap_top(heap_s *heap) {
    if (heap_empty(heap)) return INT_MAX;
    return heap->array[1];
}

// Comme heap_top() sauf que l'objet est en plus supprimé du
// tas. Renvoie NULL si le tas est vide.
int heap_pop(heap_s *heap) {
    int resultMin = heap_top(heap);

    heap->array[1] = heap->array[heap->n];
    heap->n--;

    int i = 1;
    while (2 * i <= (heap->n)) {
        if (2 * i + 1 > heap->n || heap->array[2 * i] < heap->array[2 * i + 1]) {
            if (heap->array[i] > heap->array[2 * i]) {
                int temp = heap->array[2 * i];
                heap->array[2 * i] = heap->array[i];
                heap->array[i] = temp;
            }
            i = 2 * i;
        } else {
            if (heap->array[i] < heap->array[2 * i + 1]) {
                int temp = heap->array[2 * i + 1];
                heap->array[2 * i + 1] = heap->array[i];
                heap->array[i] = temp;
            }
            i = 2 * i + 1;
        }
    }
    return resultMin;
}

// affiche le contenu du tas h d'éléments de type t
// sous la forme d'un arbre

void rule(int n, char *s) {
    for (int i = 0; i < n; i++) printf("%s", s);
}

void heap_print(heap_s *h) {
    if (h == NULL) {
        printf("heap = NULL\n\n");
        return;
    }

    if(heap_empty(h)){
        printf("Empty heap\n");
    }

    rule(2, "-");
    printf("\n");

    int haut = 0;  // hauteur du tas (=nombre de lignes)
    int j = h->n;
    while (j > 0) haut++, j >>= 1;

    int s = 2 / 2;  // nombre de caractères avant le milieu du pattern
    int B = 1;      // B = nombre de patterns dans la ligne
    j = 0;          // j = nombre d'éléments déjà affichés

    for (int y = haut - 1; y >= 0; y--, B <<= 1) {  // on part du haut

        int pm = (s + 1) * (1 << y) - 1;
        int lb = (s + 1) * (1 << (y - 1)) - 1;
        int ep = 2 * pm + 1 - 2 * s;

        // ligne avec les éléments
        rule(pm - s, " ");
        for (int b = 0; b < B && (j < h->n); b++) {
            j++;
            printf(" ");  // cas pair
            printf("%02i ", h->array[j]);
            if (b < B - 1) rule(ep - 1, " ");  // -1 pour l'espace terminal
        }
        printf("\n");
        if (y == 0) break;  // fini si dernière ligne d'éléments

        // ligne avec les branchements
        rule(lb, " ");
        for (int b = 0; b < B; b++) {
            printf("┌");
            rule(lb, "─");
            printf("┴");
            rule(lb, "─");
            printf("┐");
            if (b < B - 1) rule(pm, " ");
        }
        printf("\n");
    }

    rule(2, "-");
    printf("\n\n");
}