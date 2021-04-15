#include "hash_table.h"

#ifndef __TOOLS_H__
#define __TOOLS_H__

/**
 * @brief Different direction used to define an edge of a map
 **/
typedef enum {
    NORTH = 0,
    EST = 1,
    SOUTH = 2,
    WEST = 3,
} direction;

/**
 * @brief Different end result for the fonction fill_map_edge_from_direction_list
 **/
typedef enum {
    SHAPE_IS_PAVABLE = 0,
    SHAPE_IS_NOT_PAVABLE = 1,
    SHAPE_IS_DICONECTED = 2,
    ERROR_DIRECTION_TABLE = 3,
    ERROR_MAP = 4,
} how_fill_fonction_worked;


how_fill_fonction_worked fill_map_edge_from_direction_list(direction list_of_direction[], hash_s* map_of_height);


#endif  // __TOOLS_H__