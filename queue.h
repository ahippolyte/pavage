#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

/**
 * @brief Different direction used to define an edge of a map
 **/
typedef enum {
    NORTH = 0,
    EST = 1,
    SOUTH = 2,
    WEST = 3,
} direction;

#define SIZE 5

typedef struct queue {
    int* items;
    uint size;
    int front, rear;
} queue_s;

queue_s* queue_new();
void queue_print(queue_s* queue);
void queue_enqueue(queue_s* queue, int item);
void queue_dequeue(queue_s* queue);
bool queue_is_empty(queue_s* queue);
int queue_peek(queue_s* queue);
void queue_delete(queue_s* queue);