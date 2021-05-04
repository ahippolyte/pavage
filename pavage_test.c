#include "pavage.h"

#include <string.h>

#include "hash_table.h"
#include "heap.h"
#include "point.h"

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

/*---------------- HASH_hash ---------------*/

/**     test_hash_new    **/

bool test_hash_new() {
    hash_s *hash = hash_new(5);
    if (hash == NULL) {
        return false;
    }
    hash_delete(hash);
    return true;
}

/**     test_hash_print    **/

bool test_hash_print() {
    hash_s *hash = hash_new(2);
    if (hash == NULL) {
        fprintf(stderr, "Failed to create a hash table!");
        return false;
    }
    point_s *key_1 = point_new(10, 6);
    int height_1 = -5;
    hash_add(hash, key_1, height_1);

    point_s *key_2 = point_new(2, 7);
    int height_2 = 4;
    hash_add(hash, key_2, height_2);

    hash_print(hash);

    point_delete(key_1);
    point_delete(key_2);
    hash_delete(hash);
    return true;
}

/**     test_hash_add    **/

bool test_hash_add() {
    hash_s *hash = hash_new(1);
    point_s *point = point_new(1, 0);
    hash_add(hash, point, 1);
    if (hash->index == 1) {
        if (hash->p_cell[hash->size - 1]->key->x == 1 && hash->p_cell[hash->size - 1]->key->y == 0) {
            point_delete(point);
            hash_delete(hash);
            return true;
        }
        point_delete(point);
        hash_delete(hash);
        return false;
    }
    point_delete(point);
    hash_delete(hash);
    return false;
}

/**     test_hash_search    **/

bool test_hash_search() {
    hash_s *hash = hash_new(1);
    point_s *point = point_new(1, 0);
    hash_add(hash, point, 1);
    if (hash_search(hash, point) == 1) {
        // point_delete(point);
        point_delete(point);
        hash_delete(hash);
        return true;
    }
    point_delete(point);
    hash_delete(hash);
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

    if (!queue_is_empty(queue_1) && queue_is_empty(queue_2)) {
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
    if (queue_peek(queue) == 1) {
        queue_delete(queue);
        return true;
    }
    queue_delete(queue);
    return false;
}

/*--------------- HEAP --------------*/

bool test_heap_new() {
    heap_s *heap = heap_new(5);
    if (heap == NULL) {
        return false;
    }
    heap_delete(heap);
    return true;
}

bool test_heap_print() {
    heap_s *heap = heap_new(5);
    if (heap == NULL) {
        return false;
    }
    heap_print(heap);

    printf("Insert -> %d\n", 0);
    heap_add(heap, 0);
    heap_print(heap);
    printf("Insert -> %d\n", 2);
    heap_add(heap, 2);
    heap_print(heap);
    printf("Insert -> %d\n", -2);
    heap_add(heap, -2);
    heap_print(heap);
    printf("Insert -> %d\n", -3);
    heap_add(heap, -3);
    heap_print(heap);
    printf("Insert -> %d\n", 1);
    heap_add(heap, 1);
    heap_print(heap);

    heap_delete(heap);
    return true;
}

bool test_heap_empty() {
    heap_s *heap_1 = heap_new(2);
    heap_s *heap_2 = heap_new(2);
    heap_add(heap_1, 1);

    bool assert = heap_empty(heap_2) && !heap_empty(heap_1);
    heap_delete(heap_1);
    heap_delete(heap_2);
    return assert;
}

bool test_heap_add() {
    heap_s *heap = heap_new(5);

    heap_add(heap, 2);
    heap_add(heap, 1);
    bool top1 = (heap_top(heap) == 1);
    heap_add(heap, 4);
    heap_add(heap, 3);
    heap_add(heap, 0);
    bool top2 = (heap_top(heap) == 0);

    heap_delete(heap);
    return (top1 && top2);
}

bool test_heap_top() {
    heap_s *heap = heap_new(3);
    heap_add(heap, 4);
    heap_add(heap, 5);
    heap_add(heap, 3);
    bool assert = (heap_top(heap) == 3);
    heap_delete(heap);
    return (assert);
}

bool test_heap_pop() {
    heap_s *heap = heap_new(5);

    heap_add(heap, 2);
    heap_add(heap, 1);
    heap_add(heap, 4);
    heap_add(heap, 3);
    heap_add(heap, 0);

    bool pop1 = (heap_pop(heap) == 0);
    heap_pop(heap);
    heap_pop(heap);
    bool pop2 = (heap_pop(heap) == 3);

    heap_delete(heap);

    return pop1 && pop2;
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
    else if (strcmp("heap_new", argv[1]) == 0)
        test = test_heap_new();
    else if (strcmp("heap_print", argv[1]) == 0)
        test = test_heap_print();
    else if (strcmp("heap_empty", argv[1]) == 0)
        test = test_heap_empty();
    else if (strcmp("heap_add", argv[1]) == 0)
        test = test_heap_add();
    else if (strcmp("heap_top", argv[1]) == 0)
        test = test_heap_top();
    else if (strcmp("heap_pop", argv[1]) == 0)
        test = test_heap_pop();
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