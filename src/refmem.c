#include "refmem.h"

#define COUNTERSIZE sizeof(int)
//#define getCounter(obj_ptr) ((obj *)(((int *)obj_ptr) - 1))

// TODO: gör om till macro
obj *getCounter(obj *obj_ptr){
    return ((int *)obj_ptr) - 1;
}

obj *allocate(size_t bytes, function1_t destructor) {
    int *allocation = calloc(1, (COUNTERSIZE + bytes));
    (*allocation) = 0;
    return &(allocation[1]);
}

void deallocate(obj *obj_ptr) {
    int *counterPointer = getCounter(obj_ptr);
    free(counterPointer);
}

void retain(obj *obj_ptr){
    int *counterPointer = getCounter(obj_ptr);
    (*counterPointer)++;
}

void release(obj *obj_ptr){
    int *counterPointer = getCounter(obj_ptr);
    (*counterPointer)--;

    if((*counterPointer) <= 0) {
        deallocate(obj_ptr);
    }
}

size_t rc(obj *obj_ptr) {
    int *counterPointer = getCounter(obj_ptr);
    return *counterPointer;
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor) {
    int *allocation = calloc(1, (COUNTERSIZE + (elements * elem_size)));
    (*allocation) = 0;
    return &(allocation[1]);
}

