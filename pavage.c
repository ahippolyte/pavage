#include "pavage.h"

<<<<<<< HEAD
/**       X/Y min/max      **/
=======



how_fill_fonction_worked fill_map_edge_from_direction_list(queue_s *list_of_direction, hash_s* map_of_height){

    hash_add(map_of_height,coordinate_new(0,0),0);

    return fill_map_edge_from_direction_list_recur(list_of_direction[], map_of_height, coordinate_new(0,0));
}



fill_map_edge_from_direction_list_recur(queue_s *list_of_direction, hash_s* map_of_height, coordinate last_coordinate){
    if (list_of_direction == NULL){
        return ERROR_DIRECTION_TABLE;
    }

    if (map_of_height == NULL){
        return ERROR_MAP;
    }

    if (queue_is_empty(list_of_direction)){
        if (coordinate_compare(last_coordinate,coordinate_new(0,0))){
            return SHAPE_IS_MAYBE_PAVABLE;
        }
        else{
            return SHAPE_IS_DICONECTED;
        }
    }

    direction new_direction = queue_peek(list_of_direction);
    queue_dequeue(list_of_direction);
    coordinate new_coordinate = next_coordinate(last_coordinate,new_direction);

    if (coordinate_compare(new_coordinate,coordinate_new(0,0)) && queue_is_empty(list_of_direction)){
        if (calculate_height(last_coordinate, hash_search(map_of_height ,old_coordinate),new_direction) == 0 ){
            return SHAPE_IS_MAYBE_PAVABLE;
        }else{
            return SHAPE_IS_NOT_PAVABLE;
        }
    }

    if (hash_search(map_of_height ,new_coordinate) != INT_MAX){
        return SHAPE_IS_DICONECTED;
    }

    hash_add(map_of_height,new_coordinate,calculate_height(last_coordinate, hash_search(map_of_height ,old_coordinate),new_direction));

    return fill_map_edge_from_direction_list_recur(list_of_direction, map_of_height, new_coordinate);
}
>>>>>>> 0b00a17cce69ac2328d7b636a9c115d42bb43cc9

int Xmin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->x < min) {
            min = hash->p_cell[i]->key->x;
        }
    }
    return min;
}

int Xmax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->x > max) {
            max = hash->p_cell[i]->key->x;
        }
    }
    return max;
}

int Ymin(hash_s *hash) {
    int min = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->y < min) {
            min = hash->p_cell[i]->key->y;
        }
    }
    return min;
}

int Ymax(hash_s *hash) {
    int max = 0;
    for (uint i = 0; i < hash->size; i++) {
        if (hash->p_cell[i]->key->y > max) {
            max = hash->p_cell[i]->key->y;
        }
    }
    return max;
}

/**   Auxiliary function for fill_map_edge_from_direction_list   **/

coordinate_s next_coordinate(coordinate_s *c, direction d) {
    if (c == NULL) {
        fprintf(stderr, "invalid pointer adresse");
        exit(EXIT_FAILURE);
    }
    coordinate_s *next_c = coordinate_new(c->x, c->y);
    if (d == NORTH) {
        next_c->y++;
    }
    if (d == SOUTH) {
        next_c->y--;
    }
    if (d == EST) {
        next_c->x++;
    }
    if (d == WEST) {
        next_c->x--;
    }
    return *next_c;
}

int calculate_height(coordinate_s *old_coordinate, int old_height, direction direction) {
    if (old_coordinate->x % 2 == old_coordinate->y % 2) {
        if (direction == EST || direction == WEST) {
            old_height--;
        }
        if (direction == NORTH || direction == SOUTH) {
            old_height++;
        }
    } else {
        if (direction == EST || direction == WEST) {
            old_height++;
        }
        if (direction == NORTH || direction == SOUTH) {
            old_height--;
        }
    }
    return old_height;
}
