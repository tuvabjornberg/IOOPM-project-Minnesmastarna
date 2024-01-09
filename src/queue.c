#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "refmem.h"
#include "queue.h"

queue* create_queue()
{
    queue* new_queue = (queue*)calloc(1, sizeof(queue));

    new_queue->front = new_queue->rear = NULL;

    return new_queue;
}

bool is_empty(queue* queue)
{
    return ( queue->size == 0 );
}

void enqueue(queue* queue, obj *data)
{
    node* new_node = (node*)calloc(1, sizeof(node));

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

obj *dequeue(queue* queue)
{
    if (is_empty(queue))
    {
        fprintf(stderr, "Error: Cannot dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    node* temp = queue->front;
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

void destroy_queue(queue* queue)
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
