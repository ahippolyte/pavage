#include "pavage.h"

#include <string.h>

#include "coordinate.h"
#include "hash_table.h"

/*---------------- COORDINATE ---------------*/

/**     test_coordinate_new    **/

bool test_coordinate_new() {
    coordinate_s *coordinate = coordinate_new(1, 1);
    if (coordinate == NULL) {
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

    if (coordinate_is_equal(coordinate_1, coordinate_2) == false) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
        coordinate_delete(coordinate_3);
        return false;
    }

    if (coordinate_is_equal(coordinate_1, coordinate_3) == true) {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
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

bool test_hash_new() {
    hash_s *table = hash_new();
    if (table == NULL) {
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
    hash_s *table = hash_new();
    coordinate_s *coordinate = coordinate_new(1, 0);
    hash_add(table, coordinate, 1);
    if (table->size == 1) {
        if (table->p_cell[table->size - 1]->key->x == 1 && table->p_cell[table->size - 1]->key->y == 0) {
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
    hash_s *table = hash_new();
    coordinate_s *coordinate = coordinate_new(1, 0);
    hash_add(table, coordinate, 1);
    if (hash_search(table, coordinate) == 1) {
        // coordinate_delete(coordinate);
        hash_delete(table);
        return true;
    }
    return false;
}

/*--------------- QUEUE --------------*/

bool test_queue_new() {
    queue_s *queue = queue_new(5);
    if (queue == NULL) {
        queue_delete(queue);
        return false;
    }
    queue_delete(queue);
    return true;
}

bool test_queue_print() {
    queue_s *queue = queue_new(5);
    if (queue == NULL) {
        queue_delete(queue);
        return false;
    }
    queue_enqueue(queue, 7);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 4);
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 6);
    queue_print(queue);
    queue_dequeue(queue);
    queue_print(queue);

    queue_delete(queue);
    return true;
}

bool test_queue_enqueue() {
    queue_s *queue = queue_new(2);
    queue_enqueue(queue, 5);
    queue_enqueue(queue, 3);
    if (queue_peek(queue) == 3) {
        return true;
    }
    return false;
}

bool test_queue_dequeue() {
    queue_s *queue = queue_new(2);
    queue_enqueue(queue, 5);
    queue_enqueue(queue, 3);
    queue_dequeue(queue);
    if (queue_peek(queue) == 3) {
        queue_delete(queue);
        return true;
    }
    queue_delete(queue);
    return false;
}

bool test_queue_is_empty() { 
    queue_s *queue_1 = queue_new(2);
    queue_s *queue_2 = queue_new(2);
    queue_enqueue(queue_1, 1);

    if(!queue_is_empty(queue_1) && queue_is_empty(queue_2)){
        queue_delete(queue_1);
        queue_delete(queue_2);
        return true;
    }
    queue_delete(queue_1);
    queue_delete(queue_2);
    return false;
    
}

bool test_queue_peek() { return true; }

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
    else if (strcmp("hash_new", argv[1]) == 0)
        test = test_hash_new();
    else if (strcmp("hash_print", argv[1]) == 0)
        test = test_hash_print();
    else if (strcmp("hash_add", argv[1]) == 0)
        test = test_hash_add();
    else if (strcmp("hash_search", argv[1]) == 0)
        test = test_hash_search();
    else if (strcmp("queue_new", argv[1]) == 0)
        test = test_queue_new();
    else if (strcmp("queue_print", argv[1]) == 0)
        test = test_queue_print();
    else if (strcmp("queue_enqueue", argv[1]) == 0)
        test = test_queue_enqueue();
    else if (strcmp("queue_dequeue", argv[1]) == 0)
        test = test_queue_dequeue();
    else if (strcmp("queue_is_empty", argv[1]) == 0)
        test = test_queue_is_empty();
    else if (strcmp("queue_peek", argv[1]) == 0)
        test = test_queue_peek();
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