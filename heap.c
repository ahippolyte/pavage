#include "heap.h"

heap_s *heap_new(uint size) {
    heap_s *heap = (heap_s *)malloc(sizeof(heap_s));
    if (heap == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    heap->array = (cell_s**)malloc(size * sizeof(cell_s*));
    if (heap->array == NULL) {
        fprintf(stderr, "Allocation failed\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    for(uint i=0; i<size; i++){
        heap->array[i] = (cell_s*)malloc(size*sizeof(cell_s));
        if(heap->array[i] == NULL){
            fprintf(stderr, "Allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        heap->array[i]->point = point_new(0,0);
        heap->array[i]->height = 0;
    }
    heap->size = size;
    heap->index = 0;
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
    for(uint i=0; i<heap->size; i++){
        cell_delete(heap->array[i]);
    }
    free(heap->array);
    free(heap);
}

bool heap_empty(heap_s *heap) {
    if (heap == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    if (heap->index == 0) {
        return true;
    }
    return false;
}

void heap_add(heap_s *heap, cell_s* cell) {
    if (heap == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }

    if (heap->index >= heap->size) {
        fprintf(stderr, "Heap is full!\n");
        return;
    }

    heap->index++;
    heap->array[heap->index] = cell;

    int i = heap->index;
    while (i > 1 && heap->array[i]->height < heap->array[i/2]->height) {
        cell_s* temp = heap->array[i/2];
        heap->array[i/2] = heap->array[i];
        heap->array[i] = temp;
        i /= 2;
    }
}

// Renvoie l'objet en haut du tas h, c'est-à-dire l'élément minimal
// selon f(), sans le supprimer. On supposera h!=NULL. Renvoie NULL si
// le tas est vide.
cell_s* heap_top(heap_s *heap) {
    if (heap_empty(heap)) return NULL;
    return heap->array[1];
}

// Comme heap_top() sauf que l'objet est en plus supprimé du
// tas. Renvoie NULL si le tas est vide.
cell_s* heap_pop(heap_s *heap) {
    cell_s* resultMin = heap_top(heap);

    heap->array[1] = heap->array[heap->index];
    heap->index--;

    int i = 1;
    while (2 * i <= (heap->index)) {
        if (2 * i + 1 > heap->index || heap->array[2 * i]->height < heap->array[2 * i + 1]->height) {
            if (heap->array[i]->height > heap->array[2 * i]->height) {
                cell_s* temp = heap->array[2 * i];
                heap->array[2 * i] = heap->array[i];
                heap->array[i] = temp;
            }
            i = 2 * i;
        } else {
            if (heap->array[i]->height < heap->array[2 * i + 1]->height) {
                cell_s* temp = heap->array[2 * i + 1];
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

    if (heap_empty(h)) {
        printf("Empty heap\n");
    }

    rule(2, "-");
    printf("\n");

    int haut = 0;  // hauteur du tas (=nombre de lignes)
    int j = h->index;
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
        for (int b = 0; b < B && (j < h->index); b++) {
            j++;
            printf(" ");  // cas pair
            printf("%02i", h->array[j]->height);
            point_print(h->array[j]->point);
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