#include "refmem.h"
#include "queue.h"
#include "hash_table.h"

#define COUNTERSIZE sizeof(int)
//#define getCounter(obj_ptr) ((obj *)(((int *)obj_ptr) - 1))

#define MAX_ALLOCATED_OBJECTS 1000
//obj *allocated_objects[MAX_ALLOCATED_OBJECTS];
//function1_t allocated_objects_destructor[MAX_ALLOCATED_OBJECTS];
//size_t allocated_objects_size[MAX_ALLOCATED_OBJECTS];
static ioopm_hash_table_t *object_destructors = NULL;
static ioopm_hash_table_t *object_sizes = NULL;
size_t num_allocated_objects = 0;

static size_t cascade_limit = 5;
static Queue *to_be_freed = NULL;

static int allocate_hash(elem_t key) {
    return key.integer % 17;
}

static bool compare_func(elem_t a, elem_t b) {
    return  a.void_ptr == b.void_ptr;
}

// TODO: gör om till macro
obj *getCounter(obj *obj_ptr) 
{
    return ((int *)obj_ptr) - 1;
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
    if(object_destructors == NULL) 
    {
        object_destructors = ioopm_hash_table_create(allocate_hash, compare_func);
    }

    if(object_sizes == NULL) 
    {
        object_sizes = ioopm_hash_table_create(allocate_hash, compare_func);
    }   

    int *allocation = calloc(1, (COUNTERSIZE + bytes));
    (*allocation) = 0;

    ioopm_hash_table_insert(object_destructors, int_elem(&(allocation[1])), void_elem(destructor));
    ioopm_hash_table_insert(object_sizes, int_elem(&(allocation[1])), int_elem(bytes));
    
    free_from_queue();

    return &(allocation[1]);
}

void deallocate(obj *obj_ptr) 
{
    option_t *destructor_lookup = ioopm_hash_table_lookup(object_destructors, int_elem(obj_ptr));

    if(destructor_lookup->success) 
    {
        if(destructor_lookup->value.void_ptr != NULL) 
        {
            function1_t destructor = destructor_lookup->value.void_ptr;
            destructor(obj_ptr);
        } 
        else 
        {
            default_destructor(obj_ptr);
        }
    } 
    else 
    {
        printf("ERROR: pointer %d not in destructor hash table", (int)obj_ptr);
    }

    int *counterPointer = getCounter(obj_ptr);
    free(counterPointer);
}

void retain(obj *obj_ptr) 
{
    int *counterPointer = getCounter(obj_ptr);
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
    int *counterPointer = getCounter(obj_ptr);
    (*counterPointer)--;

    if ((*counterPointer) <= 0) 
    {
        add_to_free_queue(obj_ptr);
    }
}

size_t rc(obj *obj_ptr) 
{
    int *counterPointer = getCounter(obj_ptr);
    return *counterPointer;
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor) 
{
    if(object_destructors == NULL) 
    {
        object_destructors = ioopm_hash_table_create(allocate_hash, compare_func);
    }
    if(object_sizes == NULL) 
    {
        object_sizes = ioopm_hash_table_create(allocate_hash, compare_func);
    }   

    int *allocation = calloc(1, (COUNTERSIZE + (elements * elem_size)));
    (*allocation) = 0;

    ioopm_hash_table_insert(object_destructors, int_elem(&allocation[1]), void_elem(destructor));
    ioopm_hash_table_insert(object_sizes, int_elem(&allocation[1]), int_elem(elements * elem_size));

    free_from_queue();


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

bool is_allocated_pointer(obj *obj_ptr) 
{
    option_t *look_Up = ioopm_hash_table_lookup(object_sizes, int_elem(obj_ptr));
    return look_Up->success;
}

void object_scanner(obj *obj_ptr, size_t obj_size) 
{
    for (size_t i = 0; i < obj_size; i++)
    {
        void **possible_pointer = (void **)((char *)obj_ptr + i); //TODO: kontrollera offset
        if (is_allocated_pointer(*possible_pointer)) 
        {
            release(*possible_pointer);
        }
    }
}

void default_destructor(obj *obj_ptr) 
{
    option_t *look_Up = ioopm_hash_table_lookup(object_sizes, int_elem(obj_ptr));
    size_t obj_size = look_Up->value.unsigned_integer;
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
            deallocate(dequeue(to_be_freed));
        }
    }
}

void shutdown() 
{
    free(to_be_freed); 
    ioopm_hash_table_destroy(object_destructors);
    ioopm_hash_table_destroy(object_sizes);
}
