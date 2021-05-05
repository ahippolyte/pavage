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

    printf("Insert -> %d,%d\n", 1,0);
    point_s* point = point_new(1,0);
    cell_s* cell = cell_new(point, 1);
    heap_add(heap, cell);

    heap_print(heap);

    heap_delete(heap);
    return true;
}

bool test_heap_empty() {
    heap_s *heap_1 = heap_new(2);
    heap_s *heap_2 = heap_new(2);
    point_s* point = point_new(1,0);
    heap_add(heap_1, cell_new(point,2));

    bool assert = heap_empty(heap_2) && !heap_empty(heap_1);
    heap_delete(heap_1);
    heap_delete(heap_2);
    return assert;
}

bool test_heap_add() {
    heap_s *heap = heap_new(5);

    point_s *point1 = point_new(0, 1);
    cell_s *cell1 = cell_new(point1, 1);
    heap_add(heap, cell1);

    point_s *point2 = point_new(1, 0);
    cell_s *cell2 = cell_new(point2, -1);
    heap_add(heap, cell2);

    bool top1 = cell_is_equal(heap_top(heap), cell2);

    heap_delete(heap);
    return (top1);
}

bool test_heap_top() {
    heap_s *heap = heap_new(3);

    point_s *point1 = point_new(0, 1);
    cell_s *cell1 = cell_new(point1, 1);
    heap_add(heap, cell1);

    point_s *point2 = point_new(1, 0);
    cell_s *cell2 = cell_new(point2, -1);
    heap_add(heap, cell2);

    point_s *point3 = point_new(1, 1);
    cell_s *cell3 = cell_new(point3, 0);
    heap_add(heap, cell3);

    bool assert = cell_is_equal(heap_top(heap), cell2);
    heap_delete(heap);
    return (assert);
}

bool test_heap_pop() {
    heap_s *heap = heap_new(3);

    point_s *point1 = point_new(0, 1);
    cell_s *cell1 = cell_new(point1, 1);
    heap_add(heap, cell1);

    point_s *point2 = point_new(1, 0);
    cell_s *cell2 = cell_new(point2, -1);
    heap_add(heap, cell2);

    point_s *point3 = point_new(1, 1);
    cell_s *cell3 = cell_new(point3, 0);
    heap_add(heap, cell3);

    cell_s* pop1 = heap_pop(heap);
    cell_s* pop2 = heap_pop(heap);
    if(cell_is_equal(pop1, cell2) && cell_is_equal(pop2, cell3)){
        heap_delete(heap);
        return true;
    }

    heap_delete(heap);
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