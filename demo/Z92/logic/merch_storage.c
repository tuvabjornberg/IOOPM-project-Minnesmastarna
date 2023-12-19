#include "merch_storage.h"
#include "../utils/hash_fun.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ioopm_store_t *ioopm_store_create()
{
    ioopm_store_t *new_store = calloc(1, sizeof(ioopm_store_t));
    new_store->merch_names = calloc(STORAGE_INITIAL_CAPACITY , sizeof(char*));
    new_store->merch_details = ioopm_hash_table_create(ioopm_hash_fun_sum_key_string, ioopm_string_eq);
    new_store->merch_count = 0;
    new_store->capacity = STORAGE_INITIAL_CAPACITY ;
    return new_store;
}

ioopm_merch_t *ioopm_merch_create(char *name, char *description, int price, ioopm_list_t *stock, int stock_size)
{
    ioopm_merch_t *new_merch = calloc(1, sizeof(ioopm_merch_t));
    new_merch->name = strdup(name);
    free(name); 
    new_merch->description = strdup(description);
    free(description); 
    new_merch->price = price;
    new_merch->stock = stock; 
    new_merch->stock_size = stock_size;
    new_merch->reserved_stock = 0;

    return new_merch;
}

// Gets the index of the name in the names array. 
// If the name doesn't exist, it returns the index where it should be inserted.
static int names_index_of(ioopm_store_t *store, char *name) 
{
    if (store->merch_count == 0) return 0;

    char **start = store->merch_names;
    char **end = store->merch_names + store->merch_count;
    char **mid;

    while (start < end) 
    {
        mid = start + (end - start) / 2;

        int comparison = strcmp(name, *mid);
        if (comparison == 0) return mid - store->merch_names; 
        if (comparison > 0) 
        {
            start = mid + 1;
        } 
        else 
        {
            end = mid;
        }
    }

    return start - store->merch_names;
}

// Inserts name in the names array at the given index. 
// Doubles memory allocation of the array if overflow.
static void names_insert(ioopm_store_t *store, int index, char *name)
{
    int last = store->merch_count;
    if (last >= store->capacity)
    {
        store->capacity *= 2;
        store->merch_names = realloc(store->merch_names, store->capacity * sizeof(char*));
    }

    for (int i = last; i > index; i--) 
    {
        store->merch_names[i] = store->merch_names[i - 1];
    }

    store->merch_names[index] = name;
}


static void names_remove(ioopm_store_t *store, int index) 
{
    int last = store->merch_count - 1;

    for (int i = index; i < last; i++) 
    {
        store->merch_names[i] = store->merch_names[i + 1];
    }
    store->merch_names[last] = NULL;
}

void ioopm_store_add(ioopm_store_t *store, ioopm_merch_t *merch)
{
  ioopm_hash_table_insert(store->merch_details, str_elem(merch->name), (elem_t){.void_ptr = merch});
  int index = store->merch_count == 0 ? 0 : names_index_of(store, merch->name);

  names_insert(store, index, merch->name);
  store->merch_count++;
}

static location_t *location_create(char *shelf, int amount)
{
    location_t *location = calloc(1, sizeof(location_t)); 
    location->shelf = strdup(shelf);
    free(shelf);  
    location->quantity = amount; 

    return location; 
}

static size_t shelves_size(ioopm_merch_t *merch)
{
    return ioopm_linked_list_size(merch->stock); 
}

static char *shelf_get(location_t *location)
{   
    return location->shelf;  
}

ioopm_merch_t *ioopm_merch_get(ioopm_store_t *store, char *name)
{
  option_t *lookup_result = ioopm_hash_table_lookup(store->merch_details, str_elem(name));

  if (lookup_result->success)
    {
      ioopm_merch_t *merch_found = lookup_result->value.void_ptr;
      free(lookup_result);
      return merch_found;          
    }
  else
    {
      free(lookup_result);
      return NULL;          
    }
}

static char *merch_name_get(ioopm_merch_t *merch)
{
    return merch->name; 
}

static char *description_get(ioopm_merch_t *merch)
{
    return merch->description; 
}

int ioopm_price_get(ioopm_merch_t *merch)
{
    return merch->price; 
}

static int quantity_get(location_t *location)
{
    return location->quantity;  
}

static ioopm_list_t *stock_get(ioopm_merch_t *merch)
{
    return merch->stock;  
}

static location_t *location_get(ioopm_merch_t *merch, char *shelf)
{
    ioopm_list_t *stock = merch->stock; 
    size_t loc_size = shelves_size(merch); 

    ioopm_list_iterator_t *iter = ioopm_list_iterator(stock);

    location_t *location = ioopm_iterator_current(iter).void_ptr;
    
    for (int i = 0; i < loc_size; i++)
    {
        if (!strcmp(shelf_get(location), shelf))
        {
            ioopm_iterator_destroy(iter); 
            return location; 
        }
        location = ioopm_iterator_next(iter).void_ptr;
    }
    ioopm_iterator_destroy(iter); 

    return (location_t *) NULL; 
}

static bool shelf_exists(ioopm_merch_t *merch, char *shelf)
{
    location_t *location = location_get(merch, shelf); 
    if (location == NULL)
    {
        return false; 
    }
    else 
    {
        return true; 
    }
}

static int stock_size_get(ioopm_merch_t *merch)
{
    return merch->stock_size; 
}

static void location_insert(ioopm_merch_t *merch, location_t *location)
{
    ioopm_list_t *stock = merch->stock;

    if (ioopm_linked_list_is_empty(stock) || strcmp(location->shelf, shelf_get(ioopm_linked_list_get(stock, 0).void_ptr)) < 0)
    {
        ioopm_linked_list_prepend(stock, void_elem(location));
    }
    else
    {
        size_t index = 0;

        while (index < ioopm_linked_list_size(stock) - 1)
        {
            location_t *current_location = (location_t *)ioopm_linked_list_get(stock, index).void_ptr;
            location_t *next_location = (location_t *)ioopm_linked_list_get(stock, index + 1).void_ptr;

            if (strcmp(location->shelf, current_location->shelf) >= 0 && strcmp(location->shelf, next_location->shelf) < 0)
            {
                ioopm_linked_list_insert(stock, index + 1, void_elem(location));
                return;
            }

            index++;
        }
        ioopm_linked_list_append(stock, void_elem(location));
    }
}

void ioopm_location_add(ioopm_merch_t *merch, char *shelf, int amount)
{
    if (shelf_exists(merch, shelf))
    {
        location_t *location = location_get(merch, shelf);
        location->quantity = quantity_get(location) + amount;
        merch->stock_size = stock_size_get(merch) + amount; 
        free(shelf);  
    }
    else
    {
        location_t *location = location_create(shelf, amount); 
        location_insert(merch, location); 
        merch->stock_size = stock_size_get(merch) + amount; 
    }
}

bool ioopm_merch_exists(ioopm_store_t *store, char *name) 
{
    char **start = store->merch_names;
    char **end = store->merch_names + store->merch_count-1;
    char **center;

    while (start <= end) 
    {
        center = start + (end - start) / 2;

        int comparison = strcmp(name, *center);
        if (comparison == 0) return true; 
        if (comparison > 0) 
        {
            start = center + 1;
        } 
        else 
        {
            end = center - 1;
        }
    }
    return false; 
}

static bool shelf_other_merch_exists(elem_t value, void *shelf)
{
    return !strcmp(shelf_get(value.void_ptr), shelf); 
}

static bool merch_search(elem_t name, elem_t merch, void *shelf)
{
    return ioopm_linked_list_any(stock_get(merch.void_ptr), shelf_other_merch_exists, shelf); 
}

bool ioopm_store_shelf_exists(ioopm_store_t *store, ioopm_merch_t *merch, char *shelf)
{
    if (shelf_exists(merch, shelf)) return false; 

    return ioopm_hash_table_any(store->merch_details, merch_search, shelf);
}

bool ioopm_store_is_empty(ioopm_store_t *store)
{
    return store->merch_count == 0;  
}

static void cart_apply_to_all(ioopm_hash_table_t *ht, ioopm_cart_apply_function apply_fun, void *arg1, void *arg2)
{
    for (int i = 0; i < ioopm_get_ht_capacity(ht); i++) 
    {
        entry_t *current = (&ht->buckets[i])->next;
  
        while (current != NULL) 
        {
            apply_fun(current->key, &current->value, arg1, arg2); 
            current = current->next;
        }
    }
}

static void search_carts(elem_t key, elem_t *value, void *old_name, void *new_name)
{
    option_t *lookup_result = ioopm_hash_table_lookup((ioopm_hash_table_t *) value->void_ptr, str_elem(old_name));

    ioopm_hash_table_insert((ioopm_hash_table_t *) value->void_ptr, str_elem(new_name), lookup_result->value); 
    ioopm_hash_table_remove((ioopm_hash_table_t *) value->void_ptr, str_elem(old_name)); 

    free(lookup_result); 
}

void ioopm_name_set(ioopm_store_t *store, ioopm_merch_t *old_merch, char *new_name, ioopm_hash_table_t *carts)
{
    int price = ioopm_price_get(old_merch); 
    char *description = description_get(old_merch); 
    ioopm_list_t *stock = stock_get(old_merch); 

    ioopm_merch_t *new_merch = ioopm_merch_create(new_name, description, price, stock, old_merch->stock_size); 

    ioopm_store_add(store, new_merch); 

    char *old_name = merch_name_get(old_merch);
    
    if (carts != NULL)
    {
        cart_apply_to_all(carts, search_carts, old_name, merch_name_get(new_merch));
    }

    ioopm_hash_table_remove(store->merch_details, str_elem(old_name));
    names_remove(store, names_index_of(store, old_name));
    store->merch_count--;

    free(old_name);
    free(old_merch);
}

void ioopm_description_set(ioopm_merch_t *merch, char *new_description)
{
    char *old_description = description_get(merch); 
    merch->description = strdup(new_description);
    free(old_description); 
    free(new_description); 
}

void ioopm_price_set(ioopm_merch_t *merch, int new_price)
{
    merch->price = new_price; 
}

void ioopm_merch_print(ioopm_merch_t *merch)
{
    printf("\nName: %s", merch_name_get(merch)); 
}

void ioopm_stock_print(ioopm_merch_t *merch)
{
    ioopm_list_t *stock = stock_get(merch); 
    size_t loc_size = shelves_size(merch); 

    for (int i = 0; i < loc_size; i++)
    {
        location_t *location = ioopm_linked_list_get(stock, i).void_ptr; 
        printf("\nShelf: %s, Quantity: %d ", location->shelf, location->quantity); 
    }
    puts("\n"); 
}     

static void stock_destroy(elem_t *value, void *arg)
{
    char *shelf = shelf_get(value->void_ptr); 
    free(shelf); 
    free(value->void_ptr);
}

static void cart_iterator(elem_t id, elem_t *cart_items, void *name)
{
    ioopm_hash_table_remove((ioopm_hash_table_t *) cart_items->void_ptr, str_elem(name)); 
}

void ioopm_store_remove(ioopm_store_t *store, ioopm_hash_table_t *carts, char *name)
{
    ioopm_merch_t *merch = ioopm_merch_get(store, name); 
    ioopm_list_t *stock = stock_get(merch); 

    if (carts != NULL)
    {
        ioopm_hash_table_apply_to_all(carts, cart_iterator, name);
    }

    ioopm_linked_list_apply_to_all(stock, stock_destroy, NULL); 
    ioopm_linked_list_destroy(stock);
    
    names_remove(store, names_index_of(store, name));
    ioopm_hash_table_remove(store->merch_details, str_elem(name));
    
    free(merch->name); 
    free(merch->description); 
    free(merch);

    store->merch_count--;
}

static void merch_destroy(elem_t name, elem_t *value, void *arg)
{
    ioopm_list_t *stock = stock_get(value->void_ptr); 

    ioopm_linked_list_apply_to_all(stock, stock_destroy, NULL); 
    ioopm_linked_list_destroy(stock); 

    char *name_in_merch = merch_name_get(value->void_ptr); 
    char *description = description_get(value->void_ptr); 

    free(name_in_merch); 
    free(description); 
    free(value->void_ptr); 
}

void ioopm_store_destroy(ioopm_store_t *store)
{
    ioopm_hash_table_apply_to_all(store->merch_details, merch_destroy, NULL);
    free(store->merch_names);

    ioopm_hash_table_destroy(store->merch_details);
    free(store);
}
