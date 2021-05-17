#include "point.h"

point_s *point_new(const float x, const float y){
    point_s *point = (point_s *)malloc(sizeof(point_s));
    if (point == NULL) {
        fprintf(stderr, "Allocation failed (point_new)\n");
        exit(EXIT_FAILURE);
    }
    point->x = x;
    point->y = y;
    return point;
}

point_s* point_copy(const point_s* point){
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress (point_copy)\n");
        exit(EXIT_FAILURE);
    }
    point_s* copy = point_new(point->x, point->y);
    if (copy == NULL) {
        fprintf(stderr, "Point allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return copy;
}

bool point_is_equal(const point_s *point_1, const point_s *point_2) {
    if (point_1 == NULL){
        fprintf(stderr, "Invalid pointer reference (point_is_equal 1)\n");
        exit(EXIT_FAILURE);
    }
    if (point_2 == NULL){
        fprintf(stderr, "Invalid pointer reference (point_is_equal 2)\n");
        exit(EXIT_FAILURE);
    }
    if (point_1->x == point_2->x && point_1->y == point_2->y) {
        return true;
    }
    return false;
}

bool point_check_coordinates(const point_s *point, const float x, const float y){
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer reference (point_check_coordinates)\n");
        exit(EXIT_FAILURE);
    }
    return (point->x == x && point->y == y);
}

void point_set_coordinates(point_s* point, const float x, const float y){
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress (point_set_coordinates)\n");
        exit(EXIT_FAILURE);
    }
    point->x = x;
    point->y = y;
}

void point_set_x(point_s *point, const float x) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress (point_set_x)\n");
        exit(EXIT_FAILURE);
    }
    point->x = x;
}

void point_set_y(point_s *point, const float y) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress (point_set_y)\n");
        exit(EXIT_FAILURE);
    }
    point->y = y;
}

void point_print(const point_s *point) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer reference (point_print)\n");
        exit(EXIT_FAILURE);
    }
    printf("(%f, %f)\n", point->x, point->y);
    return;
}

void point_delete(point_s *point) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress (point_delete)\n");
        exit(EXIT_FAILURE);
    }
    free(point); 
}