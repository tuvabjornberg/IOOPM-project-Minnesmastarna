#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "refmem.h"
#include "queue.h"

Queue* create_queue() {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    if (newQueue == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the queue.\n");
        exit(EXIT_FAILURE);
    }
    newQueue->front = newQueue->rear = NULL;
    return newQueue;
}

bool is_empty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, obj *data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (is_empty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

obj *dequeue(Queue* queue) {
    if (is_empty(queue)) {
        fprintf(stderr, "Error: Cannot dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->front;
    obj *data = temp->data;

    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL;
    } else {
        queue->front = temp->next;
    }

    free(temp);
    return data;
}

void destroy_queue(Queue* queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}