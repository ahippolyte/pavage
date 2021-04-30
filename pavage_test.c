#include "pavage.h"

#include <string.h>

#include "point.h"
#include "hash_table.h"

/*---------------- point ---------------*/

/**     test_point_new    **/

bool test_point_new() {
    point_s *point = point_new(1, 1);
    if (point == NULL) {
        return false;
    }
    if (point->x != 1 || point->y != 1) {
        point_delete(point);
        return false;
    }
    point_delete(point);
    return true;
}

/**     test_point_compare    **/

bool test_point_is_equal() {
    point_s *point_1 = point_new(1, 1);
    point_s *point_2 = point_new(1, 1);
    point_s *point_3 = point_new(1, 2);

    if (point_is_equal(point_1, point_2) == false) {
        point_delete(point_1);
        point_delete(point_2);
        point_delete(point_3);
        return false;
    }

    if (point_is_equal(point_1, point_3) == true) {
        point_delete(point_1);
        point_delete(point_2);
        point_delete(point_3);
        return false;
    }

    point_delete(point_1);
    point_delete(point_2);
    point_delete(point_3);
    return true;
}

/*---------------- HASH_TABLE ---------------*/

/**     test_hash_new    **/

bool test_hash_new() {
    hash_s *table = hash_new();
    if (table == NULL) {
        return false;
    }
    hash_delete(table);
    return true;
}

/**     test_hash_print    **/

bool test_hash_print() {
    hash_s *table = hash_new();
    if (table == NULL) {
        fprintf(stderr, "Failed to create a hash table!");
        return false;
    }
    point_s *key_1 = point_new(10, 6);
    int height_1 = -5;
    hash_add(table, key_1, height_1);

    point_s *key_2 = point_new(2, 7);
    int height_2 = 4;
    hash_add(table, key_2, height_2);

    hash_print(table);

    hash_delete(table);
    return true;
}

/**     test_hash_add    **/

bool test_hash_add() {
    hash_s *table = hash_new();
    point_s *point = point_new(1, 0);
    hash_add(table, point, 1);
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
    point_s *point = point_new(1, 0);
    hash_add(table, point, 1);
    if (hash_search(table, point) == 1) {
        // point_delete(point);
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
        return false;
    }
    printf("0");
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
    if (queue_peek(queue) == 5) {
        queue_delete(queue);
        return true;
    }
    queue_delete(queue);
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

bool test_queue_peek() { 
    queue_s *queue = queue_new(2);
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    if(queue_peek(queue) == 1){
        queue_delete(queue);
        return true;
    }
    queue_delete(queue);
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
    if (strcmp("point_new", argv[1]) == 0)
        test = test_point_new();
    else if (strcmp("point_is_equal", argv[1]) == 0)
        test = test_point_is_equal();
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