#include <sys/queue.h>
#include "refmem.h"
#include "queue.h"

#define COUNTERSIZE sizeof(int)
//#define getCounter(obj_ptr) ((obj *)(((int *)obj_ptr) - 1))

static size_t cascade_limit = 5;
static Queue *to_be_freed = NULL;

// TODO: gör om till macro
obj *getCounter(obj *obj_ptr)
{
    return ((unsigned short *)obj_ptr) - 1;
}

static void free_from_queue()
{
    for (size_t i = 0; i < cascade_limit; i++)
    {
        if (to_be_freed == NULL)
        {
            break;
        }
        else if (is_empty(to_be_freed))
        {
            break;
        }
        else
        {
            deallocate(dequeue(to_be_freed));
        }
    }
}

obj *allocate(size_t bytes, function1_t destructor)
{
    int *allocation = calloc(1, (COUNTERSIZE + bytes));
    (*allocation) = 0;

    free_from_queue();

    return &(allocation[1]);
}

void deallocate(obj *obj_ptr)
{
    unsigned short *counterPointer = getCounter(obj_ptr);
    free(counterPointer);
}

void retain(obj *obj_ptr)
{
    unsigned short *counterPointer = getCounter(obj_ptr);
    if (*counterPointer == 65535) // Reference count max size
    {
        counterPointer = 0;
        deallocate(obj_ptr);
    }
    (*counterPointer)++;
}

static void add_to_free_queue(obj *obj_to_free)
{
    if (to_be_freed == NULL)
    {
        to_be_freed = create_queue();
    }
    enqueue(to_be_freed, obj_to_free);
}

void release(obj *obj_ptr)
{
    unsigned short *counterPointer = getCounter(obj_ptr);
    (*counterPointer)--;

    if ((*counterPointer) <= 0)
    {
        add_to_free_queue(obj_ptr);
    }
}

unsigned short rc(obj *obj_ptr)
{
    unsigned short *counterPointer = getCounter(obj_ptr);
    return *counterPointer;
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor)
{
    int *allocation = calloc(1, (COUNTERSIZE + (elements * elem_size)));
    (*allocation) = 0;
    return &(allocation[1]);
}

void set_cascade_limit(size_t new)
{
    cascade_limit = new;
}

size_t get_cascade_limit()
{
    return cascade_limit;
}

void cleanup()
{
    if (to_be_freed == NULL)
    {
        return;
    }
    else
    {
        while (!is_empty(to_be_freed))
        {
            deallocate(dequeue(to_be_freed));
        }
    }
}

void shutdown()
{
    free(to_be_freed);
}
