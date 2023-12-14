#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef void obj;
typedef void(*function1_t)(obj *);

void retain(obj *);

void release(obj *);

size_t rc(obj *);

obj *allocate(size_t bytes, function1_t destructor);

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor);

void deallocate(obj *);

void set_cascade_limit(size_t new);

size_t get_cascade_limit();

bool is_allocated_pointer(obj *obj_ptr);

void object_scanner(obj *obj_ptr, size_t obj_size);

void default_destructor(obj *obj_ptr);

void cleanup();

void shutdown();
