#pragma once
#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"

#define INITIAL_CAPACITY 10

/**
 * @file merch_storage.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief A simple implementation of a storage system for merchendise. 
 * 
 * The code supports creating and managing merch, adding them to the store, editing 
 * and removing items as well as destroying the store all together. 
 * 
 * The body of the store is the ioopm_store_t type with a hashtable element where a 
 * merch's name maps to its information. 
 *  
 * The hash table assumes a suitable hash_function (hash_fun) and equality function 
 * to fit the ioopm_eq_function in common.h.
 * 
 * Error handling, such as invalid inputs (NULL etc.), is mostly done in the frontend (ui.c). 
 * Since this is a coherent project across several modules, the functions in this module wont 
 * handle most edge cases and invalid inputs. All functions expect valid and existing inputs
 * following the relevant structs. 
 * 
 * It is assumed that the user ensures proper memory management after creating and adding 
 * items to the store, as these structures involve dynamic memory allocation.
 */

typedef void(*ioopm_cart_apply_function)(elem_t key, elem_t *value, void *arg1, void *arg2);
typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;

typedef struct {
  char *name;
  char *description;
  int price;
  ioopm_list_t *stock;
  int stock_size;
  int reserved_stock;
} ioopm_merch_t;

typedef struct {
  char *shelf;
  int quantity;
} location_t;

typedef struct {
  char **merch_names;
  ioopm_hash_table_t *merch_details;
  int merch_count;
  int capacity;
} ioopm_store_t;

struct entry
{
  elem_t key;      
  elem_t value;   
  entry_t *next; 
};

struct hash_table 
{
  entry_t *buckets;
  size_t size;
  size_t ht_capacity;
  ioopm_hash_function hash_fun;
  ioopm_eq_function eq_fun;
};

/// @brief creates a new store
/// @return a new empty store
ioopm_store_t *ioopm_store_create();

/// @brief creates a merch
/// @param name the name of the merch
/// @param description a description of the merch
/// @param price the price of the merch
/// @param stock a list of storage locations
/// @param stock_size the amount of merch on all locations
/// @return a merch
ioopm_merch_t *ioopm_merch_create(char *name, char *description, int price, ioopm_list_t *stock, int stock_size);

/// @brief adds a merch to the store
/// @param store the store to add merch into
/// @param merch the merch to add into the store expects a valid existing merch
void ioopm_store_add(ioopm_store_t *store, ioopm_merch_t *merch); 

/// @brief adds or replenishes a shelf with items of the merch
/// @param merch the merch to add a shelf to, expects a valid existing merch
/// @param shelf the shelf to add or replenish
/// @param amount a number of items to put on the shelf
void ioopm_location_add(ioopm_merch_t *merch, char *shelf, int amount); 

/// @brief searches the store if a merch exists
/// @param store the store to search, expects a valid existing store
/// @param name the name of the merch to find
/// @return a truth value of if the merch is found
bool ioopm_merch_exists(ioopm_store_t *store, char *name); 

/// @brief will check if the shelf is already in use by a merch
/// @param store the store to check
/// @param shelf the shelf to find or not find
/// @return false if no merch uses the shelf or if current merch uses shelf, true if in useby other merch
bool ioopm_store_shelf_exists(ioopm_store_t *store, ioopm_merch_t *merch, char *shelf);

/// @brief checks if store is emty
/// @param store the store operated upon
/// @return true if the merch count is 0, else false
bool ioopm_store_is_empty(ioopm_store_t *store); 

/// @brief retrieves a merch from the store
/// @param store the store to search
/// @param name the name of the merch to find
/// @return the merch sought
ioopm_merch_t *ioopm_merch_get(ioopm_store_t *store, char *name); 

/// @brief retrievs the price of a merch, expects a valid existing merch with a price
/// @param merch the merch operated upon
/// @return the price of the merch
int ioopm_price_get(ioopm_merch_t *merch); 

/// @brief edits the name of a merch by copying and removing the old merch and inserting a new into the store
/// @param store the store to insert the new merch
/// @param old_merch the old merch to copy and remove, expects a valid existing merch
/// @param new_name the new name to add to the new merch
/// @param carts the carts to search for the old merch and replace with the new
void ioopm_name_set(ioopm_store_t *store, ioopm_merch_t *old_merch, char *new_name, ioopm_hash_table_t *carts); 

/// @brief edits the description of a merch
/// @param merch the merch to update, expects a valid existing merch
/// @param new_description the new description to replace
void ioopm_description_set(ioopm_merch_t *merch, char *new_description); 

/// @brief edits the price of a merch
/// @param merch the merch to update, expects a valid existing merch 
/// @param new_price the new price to replace
void ioopm_price_set(ioopm_merch_t *merch, int new_price); 

/// @brief prints a merch to the command line
/// @param merch to print, expects a valid existing merch
void ioopm_merch_print(ioopm_merch_t *merch); 

/// @brief prints the shelves and stock of a merch
/// @param merch print its stock, expects a valid existing merch
void ioopm_stock_print(ioopm_merch_t *merch); 

/// @brief removes a merch from the store and the carts it's in, as well as free its memory
/// @param store the store to remove from
/// @param carts the carts to remove from
/// @param name the name of the merch to remove
void ioopm_store_remove(ioopm_store_t *store, ioopm_hash_table_t *carts, char *name);

/// @brief deletes a store and free its memory
/// @param store the store to remove
void ioopm_store_destroy(ioopm_store_t *store); 
