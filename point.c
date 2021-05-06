#include "point.h"

point_s *point_new(float x, float y) {
    point_s *point = (point_s*)malloc(sizeof(point_s));
    if (point == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    point->x = x;
    point->y = y;
    return point;
}

void point_set_x(point_s* point, float x) {
    if (point == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    point->x = x;
}

void point_set_y(point_s* point, float y) {
    if (point == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }
    point->y = y;
}

void point_print(const point_s *point) {
    if (point == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    printf("(%.1f, %.1f)\n", point->x, point->y);
    return;
}

bool point_is_equal(const point_s *point_1, const point_s *point_2) {
    if (point_1 == NULL || point_2 == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }
    if (point_1->x == point_2->x && point_1->y == point_2->y) {
        return true;
    }
    return false;
}

void point_delete(point_s *point) {
    free(point);
}