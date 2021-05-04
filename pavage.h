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
    EDGE_IS_LOOPING,
    EDGE_IS_DISCONNECTED,
    EDGE_IS_CONNECTED,  // Edge is an area
    AREA_IS_MAYBE_PAVABLE,
    AREA_IS_NOT_PAVABLE,
    AREA_IS_PAVABLE,
    ERROR_DIRECTION_TABLE,
    ERROR_MAP,
} state;

state fill_map_edge_from_direction_list(direction *list_of_direction, int nb_of_direction , hash_s *map_of_height, int* nb_half_point,point_s* *half_points);



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