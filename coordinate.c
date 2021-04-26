#include "coordinate.h"

coordinate_s *coordinate_new(int x, int y) {
    coordinate_s *coordinate = malloc(sizeof(*coordinate));
    if (coordinate == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    coordinate->x = x;
    coordinate->y = y;
    return (coordinate);
}

void coordinate_print(const coordinate_s *coordinate) {
    if (coordinate == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    printf("(%d, %d)\n", coordinate->x, coordinate->y);
    return;
}

bool coordinate_is_equal(const coordinate_s *coordinate_1, const coordinate_s *coordinate_2) {
    if (coordinate_1 == NULL || coordinate_2 == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    if(coordinate_1->x == coordinate_2->x && coordinate_1->y == coordinate_2->y){
        return true;
    }
    return false;
}

void coordinate_delete(coordinate_s *coordinate) {
    free(coordinate);
    return;
}