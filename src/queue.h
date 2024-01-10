#pragma once
#include <stdbool.h>
#include "refmem.h"

/**
 * @file queue.h
 * @authors Liam Anderberg
 * @date 8/12-2023
 * @brief Defines a queue data structure with associated operations.
*/

typedef struct node
{
    obj **data;
    struct node* next;
} node;

typedef struct
{
    node* front;
    node* rear;
    int size;
} queue;

/// @brief Creates a new empty queue.
/// @return A pointer to the newly created queue.
queue* create_queue();

/// @brief Checks if a queue is empty.
/// @param queue A pointer to the queue.
/// @return true if the queue is empty, false otherwise.
bool is_empty(queue* queue);

/// @brief Enqueues a data element into the queue.
/// @param queue A pointer to the queue.
/// @param data A pointer to the data element to be enqueued.
void enqueue(queue* queue, obj *data);

/// @brief Dequeues a data element from the queue.
/// @param queue A pointer to the queue.
/// @return A pointer to the dequeued data element.
obj *dequeue(queue* queue);

/// @brief Destroys the queue, freeing all allocated memory.
/// @param queue A pointer to the queue.
void destroy_queue(queue* queue);
