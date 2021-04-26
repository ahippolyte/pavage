#include <string.h>

#include "coordinate.h"
#include "hash_table.h"
#include "pavage.h"

/*---------------- COORDINATE ---------------*/

/**     test_coordinate_new    **/

bool test_coordinate_new() {
    coordinate_s *coordinate = coordinate_new(1, 1);
    if(coordinate == NULL){
        return false;
    }
    if (coordinate->x != 1 || coordinate->y != 1) {
        coordinate_delete(coordinate);
        return false;
    }
    coordinate_delete(coordinate);
    return true;
}

/**     test_coordinate_compare    **/

bool test_coordinate_is_equal() {
    coordinate_s *coordinate_1 = coordinate_new(1, 1);
    coordinate_s *coordinate_2 = coordinate_new(1, 1);
    coordinate_s *coordinate_3 = coordinate_new(1, 2);
    printf("0");

    if (test_coordinate_is_equal(coordinate_1, coordinate_2) == false) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
        coordinate_delete(coordinate_3);
        return false;
    }

    printf("1");

    if (test_coordinate_is_equal(coordinate_1, coordinate_3) == true) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
        coordinate_delete(coordinate_3);
        return false;
    }

    printf("2");
    coordinate_delete(coordinate_1);
    coordinate_delete(coordinate_2);
    coordinate_delete(coordinate_3);
    return true;
}

bool test_coordinate_delete() {
    coordinate_s *coordinate_1 = coordinate_new(1, 1);
    coordinate_delete(coordinate_1);
    if(coordinate_1 == NULL){
        return true;
    }
    return false;
}

/*---------------- HASH_TABLE ---------------*/

/**     test_hash_new    **/

bool test_hash_new() {
    hash_s * table = hash_new();
    if(table == NULL){
        return false;
    }
    return true; 
}

/**     test_hash_print    **/

bool test_hash_print() {
    hash_s *table = hash_new();
    if (table == NULL) {
        fprintf(stderr, "Failed to create a hash table!");
        return false;
    }
    coordinate_s *key_1 = coordinate_new(10, 6);
    int height_1 = -5;
    hash_add(table, key_1, height_1);

    coordinate_s *key_2 = coordinate_new(2, 7);
    int height_2 = 4;
    hash_add(table, key_2, height_2);

    hash_print(table);

    return true;
}

/**     test_hash_add    **/

bool test_hash_add() {
    hash_s * table = hash_new();
    coordinate_s * coordinate = coordinate_new(1,0);
    hash_add(table, coordinate, 1); 
    if(table->size == 1){
        if(table->p_cell[table->size-1]->key->x == 1 && table->p_cell[table->size-1]->key->y == 1){
            hash_delete(table);
            return true;
        }
        hash_delete(table);
        return false;
    }
    hash_delete(table);
    return false;
}

/**     test_hash_search    **/

bool test_hash_search() {
    hash_s * table = hash_new();
    coordinate_s * coordinate = coordinate_new(1,0);
    hash_add(table, coordinate, 1);
    if(hash_search(table, coordinate) == 1){
        //coordinate_delete(coordinate);
        hash_delete(table);
        return true;
    }
    return false;
}

/**     test_hash_delete   **/

bool test_hash_delete() { 
    hash_s * table = hash_new();
    hash_delete(table);
    if(table == NULL){
        return true;
    }
    return false;
}

/*-------------- fonction usage --------------*/

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <nom du test>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*-------------- fonction main --------------*/

int main(int argc, char *argv[]) {
    if (argc == 1) usage(argc, argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);

    bool test = false;
    if (strcmp("coordinate_new", argv[1]) == 0)
        test = test_coordinate_new();
    else if (strcmp("coordinate_is_equal", argv[1]) == 0)
        test = test_coordinate_is_equal();
    else if (strcmp("coordinate_delete", argv[1]) == 0)
        test = test_coordinate_delete();
    else if (strcmp("hash_new", argv[1]) == 0)
        test = test_hash_new();
    else if (strcmp("hash_print", argv[1]) == 0)
        test = test_hash_print();
    else if (strcmp("hash_add", argv[1]) == 0)
        test = test_hash_add();
    else if (strcmp("hash_search", argv[1]) == 0)
        test = test_hash_search();
    else if (strcmp("hash_delete", argv[1]) == 0)
        test = test_hash_delete();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Tests results
    if (test) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}