#pragma once
#include <stdbool.h>
#include "linked_list.h"

/**
 * @file iterator.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 29/09-2023, edited by Martin Ek and Tuva Björnberg 1/1-2024
 * @brief The iterator (`iter_t`) allows traversing a linked list.
 *
 * The iterator allows accessing elements in a linked list sequentially. The program
 * includes functions to create and destroy an iterator, and can perform various
 * operations on the linked list (implemented in this project).
 *
 * It is assumed that the user ensures proper memory management when using
 * the iterator, including freeing the memory allocated for it.
 *
 * In certain edge-cases functions will return void pointer to NULL if either imput-value is invalid or
 * have reach a NULL element. Which functions with this behavior is mentioned below.
 */

/// @brief Create an iterator for a given list
/// @param list the list to be iterated over
/// @return an iteration positioned at the start of list
ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return the next element or a void pointer to NULL if list has no next element
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator. It is assumed that ioopm_iterator_has_next has been called before
/// using this function to ensure that there is a next element.
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element if list has elements or a void pointer to NULL is list has no current element
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);