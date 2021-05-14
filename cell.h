#include "point.h"

#ifndef __CELL_H__
#define __CELL_H__

typedef unsigned int uint;

typedef struct {
    point_s* point;
    int height;
} cell_s;

// cell_s* cell_new(point_s* point, int height);

cell_s* cell_new(const float x, const float y, const int height);

cell_s* cell_copy(const cell_s* cell);

bool cell_is_equal(const cell_s* cell1, const cell_s* cell2);

void cell_set_point(cell_s* cell, const point_s* point);

void cell_set_height(cell_s* cell, const int height);

void cell_delete(cell_s* cell);

#endif  // __CELL_H__