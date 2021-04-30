#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.h"

/**
 * @file hash_table.h
 * @brief Hash table structure.
 * @details See @ref index for further details.
 **/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef unsigned int uint;

typedef struct cell {
    point_s *key;
    int height;
} cell_s;

typedef struct hash {
    cell_s **p_cell;
    uint size;
    uint maxsize;
} hash_s;

/**
 * @brief Creates a new empty hash table.
 * @return an empty hash table
 **/
hash_s *hash_new(void);

/**
 * @brief Prints a whole hash table.
 * @param p_table the hash table
 **/
void hash_print(hash_s *p_table);

/**
 * @brief Add or update in the hash table the height of the key.
 * @param p_table the hash table
 * @param key the point
 * @param data the height
 **/
void hash_add(hash_s *p_table, const point_s *key, int height);

/**
 * @brief Find in the hash table the height of the key.
 * @param p_table the hash table
 * @param key the point
 * @return the height of the point if it find it
 **/
int hash_search(hash_s *p_table, const point_s *key);

/**
 * @brief Deletes the hash table and frees the allocated memory.
 * @param p_table the hash table to delete
 **/
void hash_delete(hash_s *p_table);

#endif  // __HASH_TABLE_H__