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

cell_s* cell_new(const float x, const float y, const int height){
    cell_s* cell = (cell_s*)malloc(sizeof(cell_s));
    if (cell == NULL) {
        fprintf(stderr, "Cell allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->point = point_new(0, 0);
    if (cell->point == NULL) {
        fprintf(stderr, "Cell point allocation failed!\n");
        free(cell);
        exit(EXIT_FAILURE);
    }
    point_set_x(cell->point, x);
    point_set_y(cell->point, y);
    cell->height = height;
    return cell;
}

cell_s* cell_copy(const cell_s* cell){
    if (cell == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    cell_s* cell_copy = cell_new(0, 0, 0);
    cell_set_point(cell_copy, cell->point);
    cell_set_height(cell_copy, cell->height);
    return cell_copy;
}

bool cell_is_equal(const cell_s* cell1, const cell_s* cell2){
    if (cell1 == NULL || cell2 == NULL) {
        fprintf(stderr, "Invalid pointer reference !\n");
        exit(EXIT_FAILURE);
    }
    return point_is_equal(cell1->point, cell2->point) && (cell1->height == cell2->height);
}

void cell_set_point(cell_s* cell, const point_s* point){
    if (cell == NULL || point == NULL) {
        fprintf(stderr, "Invalid pointer reference!\n");
        exit(EXIT_FAILURE);
    }
    cell->point->x = point->x;
    cell->point->y = point->y;
}

void cell_set_height(cell_s* cell, const int height){
    if (cell == NULL) {
        fprintf(stderr, "Invalid pointer reference !\n");
        exit(EXIT_FAILURE);
    }
    cell->height = height;
}

void cell_delete(cell_s* cell) {
    if (cell == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    point_delete(cell->point);
    free(cell);
}