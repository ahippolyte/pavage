#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "queue.h"

#ifndef __TOOLS_H__
#define __TOOLS_H__

/**
 * @brief Different end result for the fonction fill_map_edge_from_direction_list
 **/
typedef enum {
    SHAPE_IS_MAYBE_PAVABLE = 0,
    SHAPE_IS_NOT_PAVABLE = 1,
    SHAPE_IS_DICONECTED = 2,
    ERROR_DIRECTION_TABLE = 3,
    ERROR_MAP = 4,
} how_fill_fonction_worked;

how_fill_fonction_worked fill_map_edge_from_direction_list(queue_s *list_of_direction, hash_s* map_of_height);

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
 * @param c a pointer on a coordinate
 * @param d a direction
 * @return the next coordinate after the given direction
 * @pre @p c must be a valid pointer
 * */
coordinate_s * next_coordinate(coordinate_s *c, direction d);

int calculate_height(coordinate_s *old_coordinate, int old_height, direction direction);

#endif  // __TOOLS_H__