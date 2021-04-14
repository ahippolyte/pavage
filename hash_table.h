#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "coordinate.h"

/**
 * @file hash_table.h
 * @brief Hash table structure.
 * @details See @ref index for further details.
 **/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef struct cell
{
    coordinate_s * key;
    int high;
} cell_s;

typedef struct hach
{
    cell_s *p_cell;
    uint size;
} hach_s;

/**
 * @brief Creates a new empty hash table.
 * @return an empty hash table
 **/
hach_s *hach_new(void);

/**
 * @brief Add or update in the hash table the height of the key.
 * @param p_table the hash table
 * @param key the coordinate
 * @param data the height 
 **/
void hach_add(hach_s *p_table, const char *key, void *data);

/**
 * @brief Find in the hash table the height of the key.
 * @param p_table the hash table
 * @param key the coordinate
 * @return the height of the coordinate if it find it
 **/
void *hach_search(hach_s *p_table, const char *key);

/**
 * @brief Deletes the hash table and frees the allocated memory.
 * @param p_table the hash table to delete
 **/
void hach_delete(hach_s **p_table);

#endif  // __HASH_TABLE_H__