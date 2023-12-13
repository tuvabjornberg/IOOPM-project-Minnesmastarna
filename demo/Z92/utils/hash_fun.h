#pragma once
#include "../data_structures/common.h"

/**
 * @file hash_fun.h
 * @author Tuva Björnberg & Marcus Ray Sanderson
 * @date 20/10-2023
 * @brief General equal- and hashing-functions supporting ints and char* (strings). 
 *
*/

/// @brief compares two ints 
/// @param e1 the first element
/// @param e2 the second element
/// @return a truth-value if the two elements are equal
bool ioopm_int_eq(elem_t e1, elem_t e2); 

/// @brief compares two strings (char *)
/// @param e1 the first element
/// @param e2 the second element
/// @return a truth-value if the two elements are equal
bool ioopm_string_eq(elem_t e1, elem_t e2);

/// @brief a hashing function for int keys
/// @param key the key to operate on
/// @return the int value of the key
unsigned ioopm_hash_fun_key_int(elem_t key); 

/// @brief a hashing function adding each character from a string
/// @param key the key to operate on
/// @return the sum of all charactes of the key
unsigned ioopm_hash_fun_sum_key_string(elem_t key);