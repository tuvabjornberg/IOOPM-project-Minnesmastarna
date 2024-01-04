#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "../utils/hash_fun.h"
#include "../logic/shop_cart.h"
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../../../src/refmem.h"

#define PRINT_AT_A_TIME 20

static char *merch_does_exist_check(ioopm_store_t *store, bool should_exist)
{
    char *input_name = ioopm_ask_question_string("\nWrite the name of the merch: ");

    while (ioopm_merch_exists(store, input_name) != should_exist)
    {
        char *new_alt = ioopm_ask_question_string(
            should_exist
                ? "\nThe merch doesn't exist, do you want to write another one (y/n)? "
                : "\nThe merch already exists, do you want to write another one (y/n)? ");

        if (toupper(*new_alt) == 'Y' && strlen(new_alt) == 1)
        {
            release(input_name);
            input_name = ioopm_ask_question_string("\nWrite the name of the merch: ");
        }
        else
        {
            release(new_alt);
            release(input_name);
            return NULL;
        }
        release(new_alt);
    }
    retain(input_name); 
    return input_name;
}

static int merch_quantity_check(ioopm_store_t *store, char *merch_name, int current_amount)
{
    ioopm_merch_t *merch = ioopm_merch_get(store, merch_name); 
    if (current_amount == merch->stock_size) 
    {
        puts("There are no more items in stock to add to cart"); 
        return -1; 
    }

    printf("Amount available: %d", merch->stock_size - merch->reserved_stock); 
    int input_amount = ioopm_ask_question_int("\n\nEnter the amount of the merch to add to cart: "); 

    while (input_amount < 1)
    {
        input_amount = ioopm_ask_question_int("\nEnter at least 1: "); 
    }

    while (input_amount > merch->stock_size - merch->reserved_stock)
    {
        char *new_alt = ioopm_ask_question_string("\nThe store doesn't carry that many items, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y'  && strlen(new_alt) == 1)
        {
            input_amount = ioopm_ask_question_int("\nWrite the amount to add to cart: "); 
        }
        else
        {
            release(new_alt);
            return -1;
        }
        release(new_alt); 
    }
    return input_amount; 
}

static int cart_exists_check(ioopm_carts_t *storage_carts)
{
    int input_id = ioopm_ask_question_int("\nWrite the ID of the cart: ") - 1; 

    while (!ioopm_hash_table_has_key(storage_carts->carts, int_elem(input_id)))
    {
        char *new_alt = ioopm_ask_question_string("\nThe cart doesn't exist, do you want to write another one (y/n)? "); 

        if (toupper(*new_alt) == 'Y' && strlen(new_alt) == 1)
        {
            input_id = ioopm_ask_question_int("\nWrite the ID of the cart: ") - 1; 
        }
        else
        {
            release(new_alt);
            return -1;
        }
        release(new_alt); 
    }
    return input_id; 
}

static char *merch_in_cart_check(ioopm_hash_table_t *cart_items)
{
    char *input_name = ioopm_ask_question_string("\nWrite the merch to remove items from: ");     
    while (!ioopm_has_merch_in_cart(cart_items, input_name)) 
    {
        char *new_alt = ioopm_ask_question_string("\nYour cart doesn't have that merch, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y'  && strlen(new_alt) == 1)
        {
            release(input_name); 
            input_name = ioopm_ask_question_string("\nWrite the merch to remove items from: "); 
        }
        else
        {
            release(new_alt);
            release(input_name); 
            return NULL; 
        }
        release(new_alt);  
    }
    retain(input_name); 
    return input_name; 
}

static int cart_quantity_check(ioopm_carts_t *storage_carts, int input_id, char *input_name)
{    
    int merch_cart_amount = ioopm_item_in_cart_amount(storage_carts, input_id, input_name); 

    printf("The current quantity of %s in this cart is %d\n", input_name, merch_cart_amount);

    int input_quantity = ioopm_ask_question_int("\nEnter the quantity of items to remove: ");

    while (input_quantity > merch_cart_amount || input_quantity < 0)
    {
       char *new_alt = ioopm_ask_question_string("\nYour cart doesn't have that quantity, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y'  && strlen(new_alt) == 1)
        {
            input_quantity = ioopm_ask_question_int("\nWrite the amount to remove from cart: "); 
        }
        else
        {
            release(new_alt);
            return -1;
        }
        release(new_alt);  
    }
    return input_quantity; 
}

static char *shelf_exists_check(ioopm_store_t *store, ioopm_merch_t *merch)
{
    char *input_shelf = ioopm_ask_question_shelf("\n\nEnter a shelf to add stock to: ");

    if (ioopm_store_shelf_exists(store, merch, input_shelf))
    {
        char *new_alt = ioopm_ask_question_string("\nThere is already a merch on this shelf, do you want to write another one (y/n)? "); 

        if (toupper(*new_alt) == 'Y'  && strlen(new_alt) == 1)
        {
            release(input_shelf); 
            input_shelf = ioopm_ask_question_string("\nEnter a shelf to add stock to: "); 
        }
        else
        {
            release(input_shelf); 
            release(new_alt);
            return NULL;
        }
        release(new_alt); 
    }
    retain(input_shelf); 
    return input_shelf; 
}

static ioopm_merch_t *merch_input(char *name)
{
    char *description = ioopm_ask_question_string("\nWrite a description of the merch: "); 
    int price = ioopm_ask_question_int("\nWrite the price of the merch: ");
    int stock_size = 0; 

    ioopm_merch_t *new_merch = ioopm_merch_create(name, description, price, ioopm_linked_list_create(ioopm_string_eq), stock_size); 

    return new_merch; 
}

void merch_add(ioopm_store_t *store)
{    
    char *input_name = merch_does_exist_check(store, false);
    if (input_name == NULL) return;

    ioopm_merch_t *input = merch_input(input_name); 

    ioopm_store_add(store, input); 
}

void merch_list(ioopm_store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to list"); 
        return; 
    }

    int printed_items = 0;
    int total_items = store->merch_count;
    int rotations = 1;

    do
    {
        for (; printed_items < total_items && printed_items < PRINT_AT_A_TIME * rotations; printed_items++)
        {
          puts(store->merch_names[printed_items]);
        }

        if (printed_items < total_items)
        {
            char *decision = ioopm_ask_question_string("Press any key to see more items, N/n to return");

	        if (toupper(decision[0]) == 'N' && strlen(decision) == 1)
            {
	            release(decision);
                return;
	        }
            rotations++; 
            release(decision); 
        }  
    } while (printed_items < total_items);  
    
    printf("\nNo more items to display\n");
}

void merch_remove(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_does_exist_check(store, true);
    if (input_name == NULL) return;

    char *conf_remove = ioopm_ask_question_string("\nAre you sure you want to remove this merch? (y/n)"); 
    if (toupper(*conf_remove) == 'Y' && strlen(conf_remove) == 1)
    {
        ioopm_store_remove(store, storage_carts->carts, input_name); 
    }

    release(conf_remove);
    release(input_name); 
}

void merch_edit(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_does_exist_check(store, true);
    if (input_name == NULL) return; 
    
    ioopm_merch_t *merch = ioopm_merch_get(store, input_name); 

    puts("\nNew name: ");
    char *new_name = merch_does_exist_check(store, false);
    char *new_description = ioopm_ask_question_string("\nWrite the new decription: "); 
    int new_price = ioopm_ask_question_int("\nWrite the new price: "); 

    char *conf_edit = ioopm_ask_question_string("\nAre you sure you want to edit this merch? (y/n)"); 
    if (!(toupper(*conf_edit) == 'Y') && strlen(conf_edit) == 1)
    { 
        release(input_name); 
        release(conf_edit);	
	    release(new_name);
        release(new_description); 
        return; 
    }
    release(conf_edit); 

    ioopm_description_set(merch, new_description); 
    ioopm_price_set(merch, new_price); 

    printf("\nYou have edited %s to %s\n", input_name, new_name); 

    ioopm_name_set(store, merch, new_name, storage_carts->carts); 
    
    release(input_name); 
}

void stock_list(ioopm_store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_does_exist_check(store, true);
    if (input_name == NULL) return; 

    ioopm_merch_t *merch = ioopm_merch_get(store, input_name); 

    ioopm_stock_print(merch); 

    release(input_name); 
}

void stock_replenish(ioopm_store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_does_exist_check(store, true);
    if (input_name == NULL) return; 

    ioopm_merch_t *merch = ioopm_merch_get(store, input_name); 
    release(input_name); 

    printf("\nYou selected this merch:"); 
    ioopm_merch_print(merch); 

    char *input_shelf = shelf_exists_check(store, merch);
    if (input_shelf == NULL) return;  

    int input_amount = ioopm_ask_question_int("\nEnter an amount to increase the stock: "); 
    while (input_amount < 1)
    {
        input_amount = ioopm_ask_question_int("\nEnter at least 1: "); 
    }

    ioopm_location_add(merch, input_shelf, input_amount); 
}

void cart_create(ioopm_carts_t *storage_carts)
{
    ioopm_cart_create(storage_carts); 
    storage_carts->total_carts++; 

    printf("\nYou have created a cart with the ID: %d", storage_carts->total_carts); 
}   

void cart_destroy(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *conf_remove = ioopm_ask_question_string("\nAre you sure you want to remove this cart? (y/n)"); 
    if (!(toupper(*conf_remove) == 'Y') && strlen(conf_remove) == 1)
    {
        release(conf_remove);  
        return; 
    }
    release(conf_remove);

    printf("You have removed cart: %d", input_id + 1);
    ioopm_cart_destroy(storage_carts, input_id); 
}

void cart_add(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *input_name = merch_does_exist_check(store, true); 
    if (input_name == NULL) return; 

    int merch_cart_amount = ioopm_item_in_cart_amount(storage_carts, input_id, input_name); 
    int input_quantity = merch_quantity_check(store, input_name, merch_cart_amount); 
    if (input_quantity == -1) 
    {
        release(input_name); 
        return; 
    }

    ioopm_merch_t *merch = ioopm_merch_get(store, input_name);
    merch->reserved_stock += input_quantity; 

    ioopm_cart_add(storage_carts, input_id, merch->name, input_quantity); 

    printf("\nYou have added %d of %s to cart: %d\n", input_quantity, input_name, input_id + 1); 
    release(input_name); 
}

void cart_remove(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, input_id); 

    char *input_name = merch_in_cart_check(cart_items); 
    if (input_name == NULL) return;

    int input_quantity = cart_quantity_check(storage_carts, input_id, input_name); 
    if (input_quantity == -1) 
    {
        release(input_name); 
        return; 
    }

    ioopm_merch_t *merch = ioopm_merch_get(store, input_name);
    merch->reserved_stock -= input_quantity;

    ioopm_cart_remove(cart_items, input_name, input_quantity); 

    printf("Removed %d %s from cart %d.\n", input_quantity, input_name, input_id + 1);
    release(input_name); 
}

void cart_cost_calculate(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts))
    {
        puts("\nThere are no carts, please add one first");
        return;
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return;

    int total_cost = ioopm_cost_calculate(store, storage_carts, input_id);
    printf("The total cost of cart %d is %d SEK.\n", input_id + 1, total_cost);
}

void cart_checkout(ioopm_store_t *store, ioopm_carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts))
    {
        puts("\nThere are no carts, please add one first");
        return;
    }
    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return;

    ioopm_cart_checkout(store, storage_carts, input_id);
}

void print_menu(void) 
{
    printf("\n[A] Add merchendise\n[L] List merchendise\n[D] Remove merchendise\n[E] Edit merchendise\n"
            "[S] Show stock\n[P] Replenish stock\n[C] Create cart\n[R] Remove cart\n[+] Add to cart\n"
            "[-] Remove item from cart\n[=] Calculate cost of all items in your cart\n[O] Checkout\n[Q] Quit\n"); 
}

void event_loop(ioopm_store_t *store, ioopm_carts_t *storage_carts) 
{
    bool running = true; 
    char *quit_confirmation; 

    do 
    {
        print_menu(); 
        char *menu_choice = ioopm_ask_question_string(" "); 
        if (strlen(menu_choice) == 1) {
            switch (toupper(*menu_choice))
            {
                case 'A': 
                    merch_add(store); 
                    break; 
                case 'L': 
                    merch_list(store); 
                    break; 
                case 'D':
                    merch_remove(store, storage_carts); 
                    break;
                case 'E':
                    merch_edit(store, storage_carts); 
                    break;
                case 'S': 
                    stock_list(store); 
                    break;
                case 'P': 
                    stock_replenish(store); 
                    break;
                case 'C': 
                    cart_create(storage_carts); 
                    break; 
                case 'R':
                    cart_destroy(store, storage_carts); 
                    break; 
                case '+':
                    cart_add(store, storage_carts); 
                    break; 
                case '-': 
	                cart_remove(store, storage_carts); 
                    break; 
                case '=': 
	                cart_cost_calculate(store, storage_carts); 
                    break; 
                case 'O': 
	                cart_checkout(store, storage_carts); 
                    break; 
                case 'Q':
                    quit_confirmation = ioopm_ask_question_string("Press 'Y' if you really want to quit");

                    if (toupper(*quit_confirmation) == 'Y' && strlen(quit_confirmation) == 1)
                    {
                        running = false; 
                        release(storage_carts); 
                        release(store); 
                    } 
                    release(quit_confirmation); 
                    break; 
                default:
                    puts("\nTry again with a valid input"); 
            }
        } 
        else 
        {
            puts("\nTry again with a valid input"); 
        }
        release(menu_choice); 
    } while (running); 
}

int main() { 
    ioopm_store_t *store = ioopm_store_create(); 
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create(); 
    event_loop(store, storage_carts); 
    return 0;
}
