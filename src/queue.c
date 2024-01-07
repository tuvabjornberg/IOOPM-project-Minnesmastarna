#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "refmem.h"
#include "queue.h"

Queue* create_queue()
{
    Queue* new_queue = (Queue*)calloc(1, sizeof(Queue));

    new_queue->front = new_queue->rear = NULL;

    return new_queue;
}

bool is_empty(Queue* queue)
{
    return ( queue->size == 0 );
}

void enqueue(Queue* queue, obj *data)
{
    Node* new_node = (Node*)calloc(1, sizeof(Node));

    new_node->data = data;
    new_node->next = NULL;

    if (is_empty(queue))
    {
        queue->front = queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++;
}

obj *dequeue(Queue* queue)
{
    if (is_empty(queue))
    {
        fprintf(stderr, "Error: Cannot dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->front;
    obj *data = temp->data;

    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = NULL;
    }
    else
    {
        queue->front = temp->next;
    }

    free(temp);
    queue->size--;
    return data;
}

void destroy_queue(Queue* queue)
{
    if (queue != NULL)
    {
        while (!is_empty(queue))
        {
            dequeue(queue);
        }
    }

    free(queue);
}
