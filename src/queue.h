#pragma once
#include <stdbool.h>
#include "refmem.h" 

typedef struct Node 
{
    obj *data;
    struct Node* next;
} Node;

typedef struct 
{
    Node* front;
    Node* rear;
} Queue;

/// @brief Creates a new empty queue.
/// @return A pointer to the newly created Queue.
Queue* create_queue();

/// @brief Checks if a queue is empty.
/// @param queue A pointer to the Queue.
/// @return true if the queue is empty, false otherwise.
bool is_empty(Queue* queue);

/// @brief Enqueues a data element into the queue.
/// @param queue A pointer to the Queue.
/// @param data A pointer to the data element to be enqueued.
void enqueue(Queue* queue, obj *data);

/// @brief Dequeues a data element from the queue.
/// @param queue A pointer to the Queue.
/// @return A pointer to the dequeued data element.
obj *dequeue(Queue* queue);

/// @brief Destroys the queue, freeing all allocated memory.
/// @param queue A pointer to the Queue.
void destroy_queue(Queue* queue);
