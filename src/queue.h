#pragma once
#include <stdbool.h>

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

Queue* create_queue();

bool is_empty(Queue* queue);

void enqueue(Queue* queue, obj *data);

obj *dequeue(Queue* queue);

void destroy_queue(Queue* queue);
