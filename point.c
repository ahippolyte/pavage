#include "point.h"

point_s *point_new(float x, float y) {
    point_s *point = (point_s *)malloc(sizeof(point_s));
    if (point == NULL) {
        fprintf(stderr, "Point allocation failed!");
        exit(EXIT_FAILURE);
    }
    point->x = x;
    point->y = y;
    return point;
}

point_s* point_copy(point_s* point){
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    point_s* copy = point_new(point->x, point->y);
    if (copy == NULL) {
        fprintf(stderr, "Point allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return copy;
}

void point_set_x(point_s *point, float x) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    point->x = x;
}

void point_set_y(point_s *point, float y) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer adress\n");
        exit(EXIT_FAILURE);
    }
    point->y = y;
}

void point_print(const point_s *point) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer reference!\n");
        exit(EXIT_FAILURE);
    }
    printf("(%f, %f)\n", point->x, point->y);
    return;
}

bool point_is_equal(const point_s *point_1, const point_s *point_2) {
    if (point_1 == NULL || point_2 == NULL) {
        fprintf(stderr, "Invalid pointer reference!\n");
        exit(EXIT_FAILURE);
    }
    if (point_1->x == point_2->x && point_1->y == point_2->y) {
        return true;
    }
    point_print(point_1);
    point_print(point_2);
    return false;
}

void point_delete(point_s *point) { free(point); }