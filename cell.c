#include "cell.h"

/*
cell_s* cell_new(point_s* point, int height) {
    cell_s* cell = (cell_s*)malloc(sizeof(cell_s));
    if (cell == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->point = point_new(point->x, point->y);
    if(cell->point == NULL){
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->height = height;
    return cell;
}
*/

cell_s* cell_new(float x, float y, int height) {
    cell_s* cell = (cell_s*)malloc(sizeof(cell_s));
    if (cell == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->point = point_new(0, 0);
    if (cell->point == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        free(cell);
        exit(EXIT_FAILURE);
    }
    point_set_x(cell->point, x);
    point_set_y(cell->point, y);
    cell->height = height;
    return cell;
}

void cell_set_point(cell_s* cell, point_s* point) {
    if (cell == NULL || point == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->point->x = point->x;
    cell->point->y = point->y;
}

void cell_set_height(cell_s* cell, int height) {
    if (cell == NULL) {
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->height = height;
}

bool cell_is_equal(cell_s* cell1, cell_s* cell2) {
    if (cell1 == NULL || cell2 == NULL) {
        fprintf(stderr, "Invalid pointer adress!\n");
        exit(EXIT_FAILURE);
    }
    return point_is_equal(cell1->point, cell2->point) && (cell1->height == cell2->height);
}

cell_s* cell_copy(cell_s* cell) {
    cell_s* cell_copy = cell_new(0, 0, 0);
    cell_set_point(cell_copy, cell->point);
    cell_set_height(cell_copy, cell->height);
    return cell_copy;
}

void cell_delete(cell_s* cell) {
    point_delete(cell->point);
    free(cell);
}