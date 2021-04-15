#include "coordinate.h"

coordinate_s *coordinate_new(int x, int y) {
    coordinate_s *coordinate = NULL;
    coordinate = malloc(sizeof(*coordinate));
    if (coordinate != NULL) {
        coordinate->x = x;
        coordinate->y = y;
    } else {
        fprintf(stderr, "Memoire insufisante\n");
        exit(EXIT_FAILURE);
    }
    return (coordinate);
}

void coordinate_print(const coordinate_s * coordinate){
    if(coordinate == NULL){
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    printf("(%d, %d)", coordinate->x, coordinate->y);
    return;
}

bool coordinate_compare(const coordinate_s *coordinate_1, const coordinate_s *coordinate_2) {
    if (coordinate_1 == NULL) {
        fprintf(stderr, "Coordonnées 1 invalides\n");
        exit(EXIT_FAILURE);
    }
    if (coordinate_2 == NULL) {
        fprintf(stderr, "Coordonnées 2 invalides\n");
        exit(EXIT_FAILURE);
    }
    if (coordinate_1->x != coordinate_2->x || coordinate_1->y != coordinate_2->y) {
        return false;
    }
    return true;
}

void coordinate_delete(coordinate_s *coordinate) {
    free(coordinate);
    return;
}