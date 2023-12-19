#include "refmem.h"
#include "queue.h"
#include "hash_table.h"
#include <stdint.h>
#include <stdio.h>

#define COUNTERSIZE sizeof(unsigned short)
#define DESTRUCTOR_PTR_SIZE sizeof(function1_t*)
#define SIZE_BITS_SIZE sizeof(unsigned short)

#define MAX_ALLOCATED_OBJECTS 1000

static size_t cascade_limit = 5;
static Queue *to_be_freed = NULL;
ioopm_list_t *allocated_pointers = NULL;

typedef struct {
    unsigned short counter;
    unsigned short size;
    function1_t destructor;
} meta_data_t;

meta_data_t *get_meta_data(obj *obj_ptr) 
{
    return ((meta_data_t *)obj_ptr - 1);
}

function1_t get_destructor(obj *obj_ptr) 
{
    meta_data_t *meta_data = get_meta_data(obj_ptr);
    return &(meta_data->destructor);
}

unsigned short get_size(obj *obj_ptr) 
{
    meta_data_t *meta_data = get_meta_data(obj_ptr);
    return meta_data->size;
}

unsigned short get_counter(obj *obj_ptr) 
{
    meta_data_t *meta_data = get_meta_data(obj_ptr);
    return meta_data->counter;
}

static bool compare_func(elem_t a, elem_t b) 
{
    return a.void_ptr == b.void_ptr;
}

void set_queue_to_null() 
{
    to_be_freed = NULL; 
}

void set_list_to_null() 
{
    allocated_pointers = NULL; 
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
            obj *to_free_ptr = dequeue(to_be_freed);
            deallocate(to_free_ptr);
        }
    }
}

obj *allocate(size_t bytes, function1_t destructor) 
{
    if (allocated_pointers == NULL) 
    {
        allocated_pointers = ioopm_linked_list_create(compare_func);
    }
    
    void *allocation = calloc(1, (sizeof(meta_data_t) + bytes));
    
    meta_data_t* meta_data = (meta_data_t*)allocation;  
    meta_data->counter = 0;
    meta_data->size = bytes;
    meta_data->destructor = destructor;

    ioopm_linked_list_append(allocated_pointers, void_elem((&meta_data[1])));
    free_from_queue();

    return (obj *)(&meta_data[1]);
}


void deallocate(obj *obj_ptr)
{
    meta_data_t *meta_data = get_meta_data(obj_ptr);

    if (meta_data->destructor == NULL) 
    {
       default_destructor(obj_ptr);
    } 
    else 
    {
        meta_data->destructor(obj_ptr);
    }

    void *elem = get_meta_data(obj_ptr);
    
    //TODO: Needs to be adjusted to remove object without knowing index (removes takes index, not object now)
    //ioopm_linked_list_remove(allocated_pointers, obj_ptr);
    free(elem);
}

void retain(obj *obj_ptr)
{
   meta_data_t *meta_data = get_meta_data(obj_ptr);

    if (meta_data->counter == 65535) 
    {
        deallocate(obj_ptr);
    } 
    else 
    {
        meta_data->counter++;
    }
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
    if (obj_ptr != NULL) 
    {
        meta_data_t *meta_data = get_meta_data(obj_ptr);

        meta_data->counter--;

        if ((meta_data->counter) <= 0) 
        {
            add_to_free_queue(obj_ptr);
        }   
    }
}

unsigned short rc(obj *obj_ptr)
{
    meta_data_t *meta_data = get_meta_data(obj_ptr);
    return meta_data->counter;
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor)
{
    if (allocated_pointers == NULL) 
    {
        allocated_pointers = ioopm_linked_list_create(compare_func);
    } 

    void *allocation = calloc(1, (sizeof(meta_data_t) + (elements * elem_size)));

    meta_data_t* meta_data = (meta_data_t*)allocation;  
    meta_data->counter = 0;
    meta_data->size = elements * elem_size;
    meta_data->destructor = destructor;

    ioopm_linked_list_append(allocated_pointers, void_elem((&meta_data[1])));
    free_from_queue();

    return (obj *)(&meta_data[1]);
}

void set_cascade_limit(size_t new)
{
    cascade_limit = new;
}

size_t get_cascade_limit()
{
    return cascade_limit;
}

bool is_allocated_pointer(obj *obj_ptr) 
{
    return ioopm_linked_list_contains(allocated_pointers, void_elem(obj_ptr));
}

void object_scanner(obj *obj_ptr, size_t obj_size) 
{
    for (size_t i = 0; i < obj_size; i += sizeof(void*))
    {
        void **possible_pointer = (void **)((char *)obj_ptr + i);
        if (is_allocated_pointer(*possible_pointer)) 
        {
            release(*possible_pointer);
        }
    }
}

void default_destructor(obj *obj_ptr) 
{
    size_t obj_size = get_size(obj_ptr);
    object_scanner(obj_ptr, obj_size);
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
            obj *to_free_ptr = dequeue(to_be_freed);
            deallocate(to_free_ptr);
        }
    }
}

void shutdown()
{
    cleanup();
    destroy_queue(to_be_freed); 
    ioopm_linked_list_destroy(allocated_pointers);  
    to_be_freed = NULL;
}
