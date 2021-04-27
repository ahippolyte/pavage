#include "queue.h"

queue_s* queue_new(uint size) {
    queue_s* queue = (queue_s*)malloc(sizeof(queue_s));
    if (queue == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    queue->items = (int*)malloc(size * sizeof(int));
    if (queue->items == NULL) {
        fprintf(stderr, "Allocation failed!");
        exit(EXIT_FAILURE);
    }

    queue->size = size;
    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void queue_print(queue_s* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    printf(" _________________\n");
    printf("|_____ QUEUE _____|\n\n");
    printf("Size: %u\n", queue->size);
    printf("________________________\n\n");
    for (uint i = queue->front; i < queue->rear + 1; i++) {
        printf("ELEMENT %u\n", i);
        printf("Value: ");
        printf("%d ", queue->items[i]);
        printf("---------\n");
    }
    printf(" _______________________ \n");
    printf("|_________ END _________|\n");
    return;
}

void queue_enqueue(queue_s* queue, int item) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if (queue->rear == queue->size - 1)
        printf("Queue is full!\n");
    else {
        if (queue->front == -1) queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = item;
    }
}

void queue_dequeue(queue_s* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if (queue->front == -1)
        printf("Queue is empty!\n");
    else {
        queue->front++;
        if (queue->front > queue->rear) queue->front = queue->rear = -1;
    }
}

bool queue_is_empty(queue_s* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if (queue->rear == -1 && queue->front == -1) {
        return true;
    }
    return false;
}

int queue_peek(queue_s* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    if (queue_is_empty(queue)) {
        printf("Can't peek into an empty queue!");
        exit(EXIT_FAILURE);
    }

    return queue->items[queue->rear];
}

void queue_delete(queue_s* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Invalid pointer reference!");
        exit(EXIT_FAILURE);
    }

    free(queue->items);
    free(queue);
}
