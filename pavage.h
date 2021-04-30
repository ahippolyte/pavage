#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "queue.h"

#ifndef __TOOLS_H__
#define __TOOLS_H__

/**
 * @brief Different end result for the fonction fill_map_edge_from_direction_list
 **/
typedef enum {
    EDGE_IS_DISCONNECTED = 0,
    EDGE_IS_CONNECTED = 1,  // Edge is a shape
    SHAPE_IS_MAYBE_PAVABLE = 2,
    SHAPE_IS_NOT_PAVABLE = 3,
    SHAPE_IS_PAVABLE = 4,
    ERROR_DIRECTION_TABLE = 5,
    ERROR_MAP = 6,
} how_fill_fonction_worked;

how_fill_fonction_worked fill_map_edge_from_direction_list(queue_s *list_of_direction, hash_s *map_of_height);

/**
 * @param hash a pointer on a hash table
 * @return the smallest abscissas of a given hash table
 * @pre @p hash must be a valid pointer toward a hash_s structure
 * */
int Xmin(hash_s *hash);

/**
 * @param hash a pointer on a hash table
 * @return the highest abscissas of a given hash table
 * @pre @p hash must be a valid pointer toward a hash_s structure
 * */
int Xmax(hash_s *hash);

/**
 * @param hash a pointer on a hash table
 * @return the smallest ordinates of a given hash table
 * @pre @p hash must be a valid pointer toward a hash_s structure
 * */
int Ymin(hash_s *hash);

/**
 * @param hash a pointer on a hash table
 * @return the highest ordinates of a given hash table
 * @pre @p hash must be a valid pointer toward a hash_s structure
 * */
int Ymax(hash_s *hash);

/**
 * @param c a pointer on a point
 * @param d a direction
 * @return the next point after the given direction
 * @pre @p c must be a valid pointer
 * */
point_s *next_point(point_s *c, direction d);

int calculate_height(point_s *old_point, int old_height, direction direction);

#endif  // __TOOLS_H__