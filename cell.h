#include "point.h"

#ifndef __CELL_H__
#define __CELL_H__

typedef unsigned int uint;

typedef struct{
    point_s *point;
    int height;
}cell_s;

cell_s* cell_new(point_s* s, int height);

bool cell_is_equal(cell_s* cell1, cell_s* cell2);

void cell_delete(cell_s* cell);

#endif // __CELL_H__