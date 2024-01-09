#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @file refmem.h
 * @authors Liam Anderberg, Tuva Björnberg, Hektor Einarsson, Martin Ek, Tove Frænell, Theo Karlsson
 * @date 9/1 2024
 * @brief Memory management which allocates and deallocates memory, using reference counters.
*/
typedef void obj;
typedef void(*function1_t)(obj *);

/// @brief Allocates a memory block of a given byte size to create an object
/// @param bytes the number of bytes of the allocated memory block
/// @param destructor a destructor function associated with the object
/// @return the object created
obj *allocate(size_t bytes, function1_t destructor);

/// @brief Destroys an object, and frees the memory allocated for it if its reference count is zero
/// @param obj_ptr the object to destroy
void deallocate(obj *obj_ptr);

/// @brief Increases the reference count of an object by 1
/// @param obj_ptr the object whose reference count is to be incremented
void retain(obj *obj_ptr);

/// @brief Decreases the reference count of an object by 1
/// @param obj_ptr the object whose reference count is to be decremented
void release(obj *obj_ptr);

/// @brief Returns the reference count of a given object
/// @param obj_ptr the object
/// @return the reference count of the object
unsigned short rc(obj *obj_ptr);

/// @brief Allocates a given amount of memory blocks of a given byte size to create an object with (potentially) multiple elements
/// @param elements the number of blocks allocated for the object
/// @param elem_size the number of bytes per memory block
/// @param destructor a destructor function associated with the object
/// @return the object created
obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor);

/// @brief makes a copy of a string
/// @param str the string to be copied
/// @return the copy of the given string
char *duplicate_string(char *str);

/// @brief Sets an upper limit of the number of frees allowed to be done consecutively,
/// @param limit the given limit of consecutive frees
void set_cascade_limit(size_t limit);

/// @brief Destroys an object, and frees the memory allocated for it if its reference count is zero
/// @param the object to destroy
size_t get_cascade_limit();

/// @brief Deallocates all pointers left in the queue
void cleanup();

/// @brief Removes all allocated memory from the program
void shutdown();