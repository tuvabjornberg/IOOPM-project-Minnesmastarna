#include "shop_cart.h"
#include "../utils/hash_fun.h"
#include "merch_storage.h"
#include <string.h>
#include <stdbool.h>

ioopm_carts_t *ioopm_cart_storage_create()
{
    ioopm_carts_t *new_carts = calloc(1, sizeof(ioopm_carts_t)); 
    new_carts->carts = ioopm_hash_table_create(ioopm_hash_fun_key_int, ioopm_int_eq); 
    new_carts->total_carts = 0;

    return new_carts;
}

void ioopm_cart_create(ioopm_carts_t *storage_carts)
{
    ioopm_hash_table_t *new_cart = ioopm_hash_table_create(ioopm_hash_fun_sum_key_string, ioopm_string_eq); 
    int id = storage_carts->total_carts; 
    ioopm_hash_table_insert(storage_carts->carts, int_elem(id), void_elem(new_cart)); 
}

ioopm_hash_table_t *ioopm_items_in_cart_get(ioopm_carts_t *storage_carts, int id)
{
    option_t *lookup_cart = ioopm_hash_table_lookup(storage_carts->carts, int_elem(id)); 
    ioopm_hash_table_t *cart_items = lookup_cart->value.void_ptr; 
    free(lookup_cart); 

    return cart_items; 
}

bool ioopm_has_merch_in_cart(ioopm_hash_table_t *cart_items, char *name)
{
    return ioopm_hash_table_has_key(cart_items, str_elem(name));
}

bool ioopm_carts_are_empty(ioopm_carts_t *storage_carts)
{
    if (ioopm_hash_table_is_empty(storage_carts->carts)) return true; 
    else return false; 
}

int ioopm_item_in_cart_amount(ioopm_carts_t *storage_carts, int id, char *merch_name)
{
    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id); 
    
    int current_amount = 0; 

    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name));

    if (item_in_cart->success)
    {
        current_amount = item_in_cart->value.integer;
    } 
    free(item_in_cart); 
    
    return current_amount; 
}

void ioopm_cart_add(ioopm_carts_t *storage_carts, int id, char *merch_name, int amount)
{ 
    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id); 
    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name)); 

    if (item_in_cart->success)
    {
        int existing_amount = item_in_cart->value.integer;
        existing_amount += amount;
        ioopm_hash_table_insert(cart_items, str_elem(merch_name), int_elem(existing_amount)); 
    }
    else
    {  
        ioopm_hash_table_insert(cart_items, str_elem(merch_name), int_elem(amount)); 
    }
    free(item_in_cart); 
}

void ioopm_cart_remove(ioopm_hash_table_t *cart_items, char *merch_name, int amount)
{
    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name));
    
    if (item_in_cart->success)
    {
        int existing_amount = item_in_cart->value.integer;
        if (existing_amount > amount)
        {
            existing_amount -= amount;
            ioopm_hash_table_insert(cart_items, str_elem(merch_name), int_elem(existing_amount));
        }
        else
        {
            ioopm_hash_table_remove(cart_items, str_elem(merch_name));
        }
    }
    free(item_in_cart); 
}

int ioopm_cost_calculate(ioopm_store_t *store, ioopm_carts_t *storage_carts, int id)
{
    int total_cost = 0;
    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id);

    ioopm_list_t *keys = ioopm_hash_table_keys(cart_items);
    for (int i = 0; i < ioopm_linked_list_size(keys); ++i)
    {
        elem_t key = ioopm_linked_list_get(keys, i);
        option_t *value = ioopm_hash_table_lookup(cart_items, key);
        
        if (value->success)
        {
	        total_cost += value->value.integer * ioopm_price_get(ioopm_merch_get(store, key.string));
        }  
        free(value);
    }
    ioopm_linked_list_destroy(keys);
    
    return total_cost;
}

static void stock_update(elem_t name, elem_t *amount, void *store)
{
  ioopm_merch_t *merch = ioopm_merch_get(store, name.string);
  merch->reserved_stock -= amount->integer;
  merch->stock_size -= amount->integer;

  ioopm_list_t *stock = merch->stock;

  for (int i = ioopm_linked_list_size(stock) - 1; i >= 0; i--)
  {
    location_t *shelf = ioopm_linked_list_get(stock, i).void_ptr;
    
    if (amount->integer > shelf->quantity) 
    {
      amount->integer -= shelf->quantity;

      free(shelf->shelf);
      free(shelf);
      ioopm_linked_list_remove(stock, i);
    } 
    else 
    {
      shelf->quantity -= amount->integer;
      return;
    }
  }
}

void ioopm_cart_checkout(ioopm_store_t *store, ioopm_carts_t *storage_carts, int id)
{
  ioopm_hash_table_t *cart = ioopm_items_in_cart_get(storage_carts, id);
  ioopm_hash_table_apply_to_all(cart, stock_update, store);

  ioopm_hash_table_destroy(cart); 
  ioopm_hash_table_remove(storage_carts->carts, int_elem(id));   
}

static void items_in_cart_destroy(elem_t key, elem_t *value, void *arg)
{
    ioopm_hash_table_destroy((ioopm_hash_table_t *) value->void_ptr); 
}

void ioopm_cart_destroy(ioopm_carts_t *storage_carts, int id)
{
    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id); 
    
    ioopm_hash_table_destroy(cart_items); 
    ioopm_hash_table_remove(storage_carts->carts, int_elem(id)); 
}

void ioopm_cart_storage_destroy(ioopm_carts_t *storage_carts)
{
    ioopm_hash_table_apply_to_all(storage_carts->carts, items_in_cart_destroy, NULL); 
    ioopm_hash_table_destroy(storage_carts->carts); 
    free(storage_carts); 
}
