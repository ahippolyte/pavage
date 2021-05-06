#include "pavage.h"

#include <string.h>

#include "heap.h"
#include "point.h"

/*---------------- POINT ---------------*/

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

/*---------------- CELL ---------------*/

bool test_cell_new(){
    cell_s* cell = cell_new(1.5, 0, 2);
    if(cell == NULL){
        cell_delete(cell);
        return false;
    }
    cell_delete(cell);
    return true;
}

bool test_cell_is_equal(){
    cell_s* cell1 = cell_new(1, 0, 2);
    cell_s* cell2 = cell_new(1, 1, 2);
    cell_s* cell3 = cell_new(1, 0, 3);
    cell_s* cell4 = cell_new(1, 0, 2);

    if(cell1 == NULL || cell2 == NULL || cell3 == NULL || cell4 == NULL){
        cell_delete(cell1);
        cell_delete(cell2);
        cell_delete(cell3);
        cell_delete(cell4);
        return false;
    }

    if(!cell_is_equal(cell1,cell2) && !cell_is_equal(cell1,cell2) && !cell_is_equal(cell1,cell3) && cell_is_equal(cell1,cell4)){
        cell_delete(cell1);
        cell_delete(cell2);
        cell_delete(cell3);
        cell_delete(cell4);
        return true;
    }

    cell_delete(cell1);
    cell_delete(cell2);
    cell_delete(cell3);
    cell_delete(cell4);
    return false;
}

/*---------------- HASH ---------------*/

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

    point_s *point1 = point_new(1, 0);
    hash_add(hash, point1, 1);

    point_s *point2 = point_new(0, 1);
    hash_add(hash, point2, 0);

    hash_print(hash);


    point_delete(point1);
    point_delete(point2);
    hash_delete(hash);
    return true;
}

/**     test_hash_add    **/

bool test_hash_add() {
    hash_s *hash = hash_new(1);

    point_s *point = point_new(1, 0);
    hash_add(hash, point, 1);

    if (hash->p_cell[hash->index - 1]->point->x == 1 && hash->p_cell[hash->index - 1]->point->y == 0 && hash->p_cell[hash->index - 1]->height == 1) {
        point_delete(point);
        hash_delete(hash);
        return true;
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
        point_delete(point);
        hash_delete(hash);
        return true;
    }
    point_delete(point);
    hash_delete(hash);
    return false;
}

/*--------------- HEAP --------------*/

bool test_heap_new() {
    heap_s *heap = heap_new(1);
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

    printf("Heap size: %u\n", heap->size);

    printf("Heap index: %u\n", heap->index);
    cell_s* cell1 = cell_new(2, 0, 1);
    heap_add(heap, cell1);
    printf("Heap index: %u\n", heap->index);
    
    cell_s* cell2 = cell_new(1, 2, 0);
    heap_add(heap, cell2);
    printf("Heap index: %u\n", heap->index);

    cell_s* cell3 = cell_new(0, 0, -1);
    heap_add(heap, cell3);
    printf("Heap index: %u\n", heap->index);
    
    cell_s* cell4 = cell_new(1, 1, 3);
    heap_add(heap, cell4);
    printf("Heap index: %u\n", heap->index);

    cell_s* cell5 = cell_new(1, 0, -3);
    heap_add(heap, cell5);
    printf("Heap index: %u\n", heap->index);

    cell_delete(cell1);
    cell_delete(cell2);
    cell_delete(cell3);
    cell_delete(cell4);
    cell_delete(cell5);
    heap_delete(heap);
    return true;
}

bool test_heap_empty() {
    heap_s *heap_1 = heap_new(2);
    heap_s *heap_2 = heap_new(2);

    cell_s* cell = cell_new(1, 3, 3);
    heap_add(heap_1, cell);

    bool assert = heap_empty(heap_2) && !heap_empty(heap_1);
    cell_delete(cell);
    heap_delete(heap_1);
    heap_delete(heap_2);
    return assert;
}

bool test_heap_add() {
    heap_s *heap = heap_new(5);

    cell_s *cell1 = cell_new(1, 3, 1);
    heap_add(heap, cell1);

    cell_s *cell2 = cell_new(1, 2, 2);
    heap_add(heap, cell2);

    cell_s *cell3 = cell_new(1, 0, 0);
    heap_add(heap, cell3);

    bool top1 = cell_is_equal(heap_top(heap), cell3);

    cell_s *cell4 = cell_new(0, 0, -1);
    heap_add(heap, cell4);

    bool top2 = cell_is_equal(heap_top(heap), cell4);

    cell_delete(cell1);
    cell_delete(cell2);
    cell_delete(cell3);
    cell_delete(cell4);
    heap_delete(heap);
    return (top1 && top2);
}

bool test_heap_top() {
    heap_s *heap = heap_new(5);

    cell_s *cell1 = cell_new(1, 3, 1);
    heap_add(heap, cell1);

    cell_s *cell2 = cell_new(1, 2, 2);
    heap_add(heap, cell2);

    cell_s *cell3 = cell_new(1, 0, 0);
    heap_add(heap, cell3);

    bool top = cell_is_equal(heap_top(heap), cell3);

    cell_delete(cell1);
    cell_delete(cell2);
    cell_delete(cell3);
    heap_delete(heap);
    return (top);
}

bool test_heap_pop() {
    heap_s *heap = heap_new(3);
    printf("Heap size: %u\n", heap->size);
    printf("Heap index: %u\n", heap->index);

    cell_s *cell1 = cell_new(1, 3, 1);
    heap_add(heap, cell1);
    printf("Heap index: %u\n", heap->index);

    cell_s *cell2 = cell_new(1, 2, -1);
    heap_add(heap, cell2);
    printf("Heap index: %u\n", heap->index);

    cell_s *cell3 = cell_new(1, 0, 0);
    heap_add(heap, cell3);
    printf("Heap index: %u\n", heap->index);

    printf("Heap size: %u\n", heap->size);

    heap_print(heap);

    cell_s* pop1 = heap_pop(heap);

    heap_print(heap);
    
    printf("Heap index: %u\n", heap->index);
    bool assert = cell_is_equal(pop1, cell2);

    cell_delete(cell1);
    cell_delete(cell2);
    cell_delete(cell3);
    heap_delete(heap);
    return assert;
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
    else if (strcmp("cell_new", argv[1]) == 0)
        test = test_cell_new();
    else if (strcmp("cell_is_equal", argv[1]) == 0)
        test = test_cell_is_equal();
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