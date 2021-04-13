/**
 * @file coordinate.h
 * @brief coordinate structure.
 * @details See @ref index for further details.
 **/

#ifndef __COORDINATE_H__
#define __COORDINATE_H__

struct coordinate_s
{
    int x;
    int y;
};

/**
 * @brief Creates a new coordinate.
 * @param x the x coordinate
 * @param y the y coordinate
 * @return the coordinate
 **/
coordinate_s *coordinate_new(int x, int y);


/**
 * @brief Compare two coordinates.
 * @param coordinate_1 the first coordinate 
 * @param coordinate_2 the second coordinate
 * @pre @p coordinate_1 must be a valid pointer toward a coordinate structure.
 * @pre @p coordinate_2 must be a valid pointer toward a coordinate structure.
 * @return true if the two coordinates are equal, false otherwise
 **/
bool *coordinate_compare(coordinate_s *coordinate_1, coordinate_s *coordinate_2);


/**
 * @brief Deletes the coordinate and frees the allocated memory.
 * @param coordinate the coordinate to delete
 **/
void coordinate_delete(coordinate_s **coordinate)

#endif  // __COORDINATE_H__