#pragma once

#include <stdbool.h>
#include "common.h"
#include <stdlib.h> 
#include "linked_list.h"

#define No_Buckets 17 //set only for debugging purposes

#define Successful(o) (o.success == true)
#define Unsuccessful(o) (o.success == false)

#define ioopm_int_str_ht_insert(ht, i, s) ioopm_hash_table_insert(ht, int_elem(i), str_elem(s))

/**
 * @file hash_table.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 29/09-2023, edited by Tuva Björnberg 13/12-2023
 * @brief Simple hash table that maps integer keys to string values.
 *
 * The hash table is implemented using dynamically allocated buckets
 * and separate chaining to handle collisions. The program includes functions 
 * to create and destroy a hash table, insert and lookup key-value pairs, remove 
 * entries, retrieve the size, check if empty, and more. 
 * 
 * The hash table assumes a suitable hash_function (hash_fun) and equality function 
 * to fit the ioopm_eq_function in common.h 
 * 
 * It is assumed that the user ensures proper memory management when using the hash 
 * table, including freeing the memory allocated for keys and values.
 * 
 * In certain edge-cases functions will return void pointer to NULL if either imput-value is invalid or 
 * have reach a NULL element. Which functions with this behavior is mentioned below. 
 */

typedef bool(ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

struct option
{
  bool success;
  elem_t value;
};

/// @brief retrieves the hashtables current capacity
/// @param ht hash table operated upon
/// @return a capacity size
size_t ioopm_get_ht_capacity(ioopm_hash_table_t *ht); 

/// @brief create a new hash table, with a hash-function
/// @param hash_fun a hash function
/// @param eq_fun an equal function
/// @return a new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun);

/// @brief delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return a heap allocated option with an truth-value and a value
option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value of the removed entry from ht with key or a void pointer to NULL if key has no entry
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param ht hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a linked list, in appended order
/// @param ht hash table operated upon
/// @return a linked list of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return a linked list of values for hash table h
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param ht hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);