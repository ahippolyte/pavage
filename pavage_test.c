#include <string.h>

#include "coordinate.h"
#include "hash_table.h"
#include "tools.h"

/*---------------- COORDINATE ---------------*/

/**     test_coordinate_new    **/

bool test_coordinate_new() {
    coordinate_s *coordinate = coordinate_new(1, 1);
    if (coordinate->x != 1 || coordinate->y != 1) {
        coordinate_delete(coordinate);
        return false;
    }
    coordinate_delete(coordinate);
    return true;
}

/**     test_coordinate_compare    **/

bool test_coordinate_compare() {
    coordinate_s *coordinate_1 = coordinate_new(1, 1);
    coordinate_s *coordinate_2 = coordinate_new(1, 1);
    coordinate_s *coordinate_3 = coordinate_new(1, 2);

    if (coordinate_compare(coordinate_1, coordinate_2) != true) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
        return false;
    }

    if (coordinate_compare(coordinate_1, coordinate_3) != false) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_3);
        return false;
    }
    coordinate_delete(coordinate_1);
    coordinate_delete(coordinate_2);
    coordinate_delete(coordinate_3);
    return true;
}

/*---------------- HASH_TABLE ---------------*/

/**     test_hash_new    **/

bool test_hash_new() { return true; }

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

bool test_hash_add() { return true; }

/**     test_hash_search    **/

bool test_hash_search() { return true; }

/**     test_hash_delete   **/

bool test_hash_delete() { return true; }

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
    else if (strcmp("coordinate_compare", argv[1]) == 0)
        test = test_coordinate_compare();
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