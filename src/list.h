#pragma once
#include <stdbool.h>
#include "common.h"

#define int_ll_append(list, value) linked_list_append(list, int_elem(value))
#define int_ll_prepend(list, value) linked_list_prepend(list, int_elem(value))
#define int_ll_insert(list, index, value) linked_list_insert(list, index, int_elem(value))

/**
 * @file linked_list.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 29/09-2023, edited by Tuva Björnberg 10/1-2024
 * @brief The program includes functions to create and destroy a linked list, perform various operations.
 *
 * The linked list is implemented using a singly linked structure (`link_t`) with a `list_t`
 * structure holding the first and last links, the size, and an equality function.
 *
 * The linked list assumes a suitable equality function to fit the eq_function in common.h
 *
 * It is also assumed that the user ensures proper memory management when using the
 * linked list, including freeing the memory allocated for elements.
 *
 * In certain edge-cases functions will return void pointer to NULL if either imput-value is invalid or
 * have reach a NULL element. Which functions with this behavior is mentioned below.
 */

typedef struct list list_t;

typedef bool(*int_predicate)(elem_t value, void *extra);
typedef void(*apply_int_function)(elem_t *value, void *extra);

typedef void obj;

/// @brief Creates a new empty list
/// @param fun function to store in the linked list object
/// @return an empty linked list
list_t *linked_list_create(eq_function fun);

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void linked_list_destroy(list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void linked_list_append(list_t *list, elem_t value);

/// @brief Remove an element from a linked list when the specified
/// object has been found.
/// @param list the linked list
/// @param obj_ptr the object to be removed
void linked_list_remove_object(list_t *list, obj *obj_ptr);

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool linked_list_contains(list_t *list, elem_t element);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
bool linked_list_is_empty(list_t *list);

/// @brief Remove all elements from a linked list
/// @param list the linked list
void linked_list_clear(list_t *list);
