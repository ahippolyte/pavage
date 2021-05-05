#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.h"

typedef unsigned int uint;

/**
 * @brief Different direction used to define an edge of a map
 **/
typedef enum {
    NORTH,
    EST,
    SOUTH,
    WEST,
} direction;

typedef struct{
    point_s *point;
    int height;
}cell_s;

cell_s* cell_new(point_s* s, int height);

bool cell_is_equal(cell_s* cell1, cell_s* cell2);

void cell_delete(cell_s* cell);

int cell_tab_get_height(cell_s* *tab, point_s* p);