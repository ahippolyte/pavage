#include "point.h"

#ifndef __CELL_H__
#define __CELL_H__

typedef unsigned int uint;

typedef struct{
    point_s *point;
    int height;
}cell_s;


//cell_s* cell_new(point_s* point, int height);

cell_s* cell_new(float x, float y, int height);

void cell_set_point(cell_s* cell, point_s* point);

void cell_set_height(cell_s* cell, int height);

bool cell_is_equal(cell_s* cell1, cell_s* cell2);

cell_s* cell_copy(cell_s* cell);

void cell_delete(cell_s* cell);

#endif // __CELL_H__