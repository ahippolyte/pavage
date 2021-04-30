#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file point.h
 * @brief point structure.
 * @details See @ref index for further details.
 **/

#ifndef __point_H__
#define __point_H__

typedef struct point {
    float x;
    float y;
} point_s;

/**
 * @brief Creates a new point.
 * @param x the x point
 * @param y the y point
 * @return the point
 **/
point_s *point_new(int x, int y);

/**
 * @brief Print a point.
 * @param point the corresponding point
 **/
void point_print(const point_s *point);

/**
 * @brief Compare two points.
 * @param point_1 the first point
 * @param point_2 the second point
 * @pre @p point_1 must be a valid pointer toward a point structure.
 * @pre @p point_2 must be a valid pointer toward a point structure.
 * @return true if the two points are equal, false otherwise
 **/
bool point_is_equal(const point_s *point_1, const point_s *point_2);

/**
 * @brief Deletes the point and frees the allocated memory.
 * @param point the point to delete
 **/
void point_delete(point_s *point);

#endif  // __point_H__