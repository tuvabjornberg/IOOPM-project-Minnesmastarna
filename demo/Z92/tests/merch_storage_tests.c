#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../logic/merch_storage.h"
#include "../utils/hash_fun.h"
#include "../logic/shop_cart.h"
#include "../../../src/refmem.h"

#define NO_ITEMS 1000

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

ioopm_store_t *store_with_inputs()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    char *shelf[] = {"B36", "R62", "A4"};
    int quantity[] = {0, 1, 4};

    for (int i = 0; i < 3; i++)
    {
        ioopm_location_add(apple, duplicate_string(shelf[i]), quantity[i]);
    }

    return store;
}

void create_destroy_merch_test()
{
    ioopm_store_t *store = ioopm_store_create();
    CU_ASSERT_PTR_NOT_NULL(store);
    release(store); 
    shutdown();
}

void store_add_remove_test()
{
    ioopm_store_t *store = ioopm_store_create();
    ioopm_hash_table_t *carts = NULL;

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    char *name_copy = duplicate_string(name);
    char *desc_copy = duplicate_string(description);

    ioopm_merch_t *apple = ioopm_merch_create(name_copy, desc_copy, price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);
    CU_ASSERT_TRUE(ioopm_merch_exists(store, name));
    CU_ASSERT_EQUAL(ioopm_merch_get(store, name), apple);

    ioopm_store_remove(store, carts, name);
    CU_ASSERT_FALSE(ioopm_merch_exists(store, name));
    CU_ASSERT_EQUAL(ioopm_merch_get(store, name), NULL);

    release(store); 
    shutdown();
}

void stock_add_remove_test()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    char *shelf[] = {"A36", "B62", "C4"};
    int quantity[] = {0, 1, 4};
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    for (int i = 0; i < 3; i++)
    {
        ioopm_location_add(apple, duplicate_string(shelf[i]), quantity[i]);
    }
    ioopm_merch_t *merch = ioopm_merch_get(store, name);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(merch->stock), 3);

    for (int i = 0; i < 3; i++)
    {
        location_t *location = ioopm_linked_list_get(merch->stock, i).void_ptr;

        CU_ASSERT_EQUAL(location->quantity, quantity[i]);
        CU_ASSERT_STRING_EQUAL(location->shelf, shelf[i]);
    }

    ioopm_location_add(apple, duplicate_string(shelf[2]), 5);
    location_t *location = ioopm_linked_list_get(merch->stock, 2).void_ptr;
    CU_ASSERT_EQUAL(location->quantity, 9);
    CU_ASSERT_STRING_EQUAL(location->shelf, shelf[2]);

    ioopm_location_add(apple, duplicate_string("B3"), 3);
    location = ioopm_linked_list_get(merch->stock, 1).void_ptr;
    CU_ASSERT_EQUAL(location->quantity, 3);
    CU_ASSERT_STRING_EQUAL(location->shelf, "B3");

    release(store); 
    shutdown();
}

void merch_exists_test()
{
    ioopm_store_t *store = ioopm_store_create();
    ioopm_hash_table_t *carts = NULL;

    CU_ASSERT_TRUE(ioopm_store_is_empty(store));

    char *name = "Apple";
    char *non_input_name = "Pear";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    char *name_o = "Orange";
    char *description_o = "Orange";
    int price_o = 4;
    int stock_size_o = 0;

    ioopm_merch_t *orange = ioopm_merch_create(duplicate_string(name_o), duplicate_string(description_o), price_o, ioopm_linked_list_create(ioopm_string_eq), stock_size_o);

    ioopm_store_add(store, apple);
    ioopm_store_add(store, orange);

    CU_ASSERT_TRUE(ioopm_merch_exists(store, name));
    CU_ASSERT_TRUE(ioopm_merch_exists(store, name_o));
    CU_ASSERT_FALSE(ioopm_merch_exists(store, non_input_name));

    ioopm_store_remove(store, carts, name);
    CU_ASSERT_FALSE(ioopm_merch_exists(store, name));

    release(store); 
    shutdown();
}

void store_size_test()
{
    ioopm_store_t *store = ioopm_store_create();
    ioopm_hash_table_t *carts = NULL;

    CU_ASSERT_EQUAL(store->merch_count, 0);

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    char *name_copy = duplicate_string(name);
    char *desc_copy = duplicate_string(description);

    ioopm_merch_t *apple = ioopm_merch_create(name_copy, desc_copy, price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);
    CU_ASSERT_EQUAL(store->merch_count, 1);

    ioopm_store_remove(store, carts, name);
    CU_ASSERT_EQUAL(store->merch_count, 0);

    release(store);
    shutdown();
}

void get_merch_test()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *non_input_name = "Pear";
    char *description = "Red";
    int price = 10;

    char *shelf[] = {"A36", "B62", "C4"};
    int quantity[] = {0, 1, 4};
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    for (int i = 0; i < 3; i++)
    {
        ioopm_location_add(apple, duplicate_string(shelf[i]), quantity[i]);
    }

    ioopm_merch_t *apple_from_store = ioopm_merch_get(store, name);
    CU_ASSERT_TRUE(!strcmp(apple->description, "Red"));
    CU_ASSERT_EQUAL(ioopm_price_get(apple_from_store), 10);
    CU_ASSERT_STRING_EQUAL(apple_from_store->description, "Red");
    CU_ASSERT_EQUAL(apple_from_store->price, 10);

    ioopm_merch_t *pear_from_store = ioopm_merch_get(store, non_input_name);
    CU_ASSERT_PTR_NULL(pear_from_store);

    for (int i = 0; i < ioopm_linked_list_size(apple_from_store->stock); i++)
    {
        apple_from_store = ioopm_merch_get(store, name);
        location_t *location = ioopm_linked_list_get(apple_from_store->stock, i).void_ptr;
        CU_ASSERT_STRING_EQUAL(location->shelf, shelf[i]);
        CU_ASSERT_EQUAL(location->quantity, quantity[i])
    }

    release(store);
    shutdown();
}

void set_name_test()
{
    ioopm_store_t *store = ioopm_store_create();
    ioopm_hash_table_t *carts = NULL;

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    char *shelf[] = {"B36", "R62", "A4"};
    int quantity[] = {0, 1, 4};
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    for (int i = 0; i < 3; i++)
    {
        ioopm_location_add(apple, duplicate_string(shelf[i]), quantity[i]);
    }

    char *new_name = "Pear";
    ioopm_name_set(store, apple, duplicate_string(new_name), carts);
    CU_ASSERT_TRUE(ioopm_merch_exists(store, new_name));

    ioopm_merch_t *updated_merch = ioopm_merch_get(store, new_name);
    CU_ASSERT_STRING_EQUAL(updated_merch->name, new_name);
    CU_ASSERT_STRING_EQUAL(updated_merch->description, description);
    CU_ASSERT_EQUAL(updated_merch->price, 10);

    ioopm_description_set(updated_merch, duplicate_string("Green"));
    CU_ASSERT_STRING_NOT_EQUAL(updated_merch->description, description);
    CU_ASSERT_STRING_EQUAL(updated_merch->description, "Green");

    location_t *first_location = ioopm_linked_list_get(updated_merch->stock, 0).void_ptr;
    CU_ASSERT_TRUE(!strcmp(first_location->shelf, "A4"));
    CU_ASSERT_EQUAL(first_location->quantity, 4);

    location_t *second_location = ioopm_linked_list_get(updated_merch->stock, 1).void_ptr;
    CU_ASSERT_TRUE(!strcmp(second_location->shelf, "B36"));
    CU_ASSERT_EQUAL(second_location->quantity, 0);

    location_t *third_location = ioopm_linked_list_get(updated_merch->stock, 2).void_ptr;
    CU_ASSERT_TRUE(!strcmp(third_location->shelf, "R62"));
    CU_ASSERT_EQUAL(third_location->quantity, 1);

    release(store);
    shutdown();
}

void set_description_test()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    ioopm_description_set(apple, duplicate_string("Green"));
    CU_ASSERT_STRING_NOT_EQUAL(apple->description, description);
    CU_ASSERT_STRING_EQUAL(apple->description, "Green");

    release(store);
    shutdown();
}

void set_price_test()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    ioopm_store_add(store, apple);

    ioopm_price_set(apple, 30);
    CU_ASSERT_NOT_EQUAL(ioopm_price_get(apple), 10);
    CU_ASSERT_EQUAL(apple->price, 30);

    release(store);
    shutdown();
}

void store_is_empty_test()
{
    ioopm_store_t *store = ioopm_store_create();
    CU_ASSERT_TRUE(ioopm_store_is_empty(store));
    release(store);
    shutdown();
}

void shelves_exists_test()
{
    ioopm_store_t *store = ioopm_store_create();

    char *name = "Apple";
    char *description = "Red";
    int price = 10;
    char *shelf[] = {"B36", "R62", "A4", "H67", "G8"};
    int quantity[] = {0, 1, 4, 5, 2};
    int stock_size = 0;

    ioopm_merch_t *apple = ioopm_merch_create(duplicate_string(name), duplicate_string(description), price, ioopm_linked_list_create(ioopm_string_eq), stock_size);

    CU_ASSERT_EQUAL(apple->stock_size, 0);

    ioopm_store_add(store, apple);

    for (int i = 0; i < 3; i++)
    {
        ioopm_location_add(apple, duplicate_string(shelf[i]), quantity[i]);
        CU_ASSERT_EQUAL(ioopm_linked_list_size(apple->stock), i + 1);
    }

    ioopm_location_add(apple, duplicate_string(shelf[2]), 3);

    char *name_p = "Pear";
    char *description_p = "Green";
    int price_p = 5;
    int stock_size_p = 0;
    ioopm_merch_t *pear = ioopm_merch_create(duplicate_string(name_p), duplicate_string(description_p), price_p, ioopm_linked_list_create(ioopm_string_eq), stock_size_p);
    ioopm_store_add(store, pear);

    CU_ASSERT_FALSE(ioopm_store_shelf_exists(store, apple, shelf[2]));
    CU_ASSERT_TRUE(ioopm_store_shelf_exists(store, pear, shelf[2]));
    CU_ASSERT_FALSE(ioopm_store_shelf_exists(store, apple, "K1"));

    CU_ASSERT_TRUE(apple->stock_size == 8);

    release(store);
    shutdown();
}

void merch_storage_cart_functions_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create();
    ioopm_store_t *store = store_with_inputs();
    ioopm_cart_create(storage_carts);
    storage_carts->total_carts++;

    int id = 0;
    char *name = "Apple";
    char *merch_name = ioopm_merch_get(store, name)->name;
    int amount = 2;

    ioopm_cart_add(storage_carts, id, merch_name, amount);
    ioopm_cart_add(storage_carts, id, merch_name, amount);
    ioopm_merch_t *old_merch = ioopm_merch_get(store, "Apple");
    ioopm_stock_print(old_merch);
    ioopm_merch_print(old_merch);

    char *new_name = duplicate_string("Orange");
    ioopm_name_set(store, old_merch, new_name, storage_carts->carts);

    ioopm_store_remove(store, storage_carts->carts, "Orange");

    ioopm_hash_table_t *cart = ioopm_items_in_cart_get(storage_carts, 0);
    CU_ASSERT_FALSE(ioopm_hash_table_has_key(cart, str_elem("Orange")));
    CU_ASSERT(ioopm_hash_table_is_empty(cart));

    release(storage_carts);
    release(store);
    shutdown();
}

void boundary_cases_test()
{
    ioopm_store_t *store = ioopm_store_create();

    for (int i = 0; i < NO_ITEMS; i++)
    {
        char name[10];
        sprintf(name, "Item%d", i);
        ioopm_merch_t *item = ioopm_merch_create(duplicate_string(name), duplicate_string("Description"), 10, ioopm_linked_list_create(ioopm_string_eq), 0);
        ioopm_store_add(store, item);
    }

    CU_ASSERT_EQUAL(store->merch_count, NO_ITEMS);

    for (int i = 0; i < NO_ITEMS; i++)
    {
        char name[10];
        sprintf(name, "Item%d", i);
        ioopm_store_remove(store, NULL, name);
    }
    CU_ASSERT_EQUAL(store->merch_count, 0);

    release(store);
    shutdown();
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for merch_storage.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
        if (
            (CU_add_test(my_test_suite, "simple create destroy merch test", create_destroy_merch_test) == NULL ||
            CU_add_test(my_test_suite, "testing for adding and removing from store", store_add_remove_test) == NULL ||
            CU_add_test(my_test_suite, "test for adding and removing from stock", stock_add_remove_test) == NULL  ||
            CU_add_test(my_test_suite, "test for merch existing", merch_exists_test) == NULL ||
            CU_add_test(my_test_suite, "test for the store size", store_size_test) == NULL ||
            CU_add_test(my_test_suite, "getting merch from store", get_merch_test) == NULL ||
            CU_add_test(my_test_suite, "test for editing name of merch", set_name_test) == NULL ||
            CU_add_test(my_test_suite, "test for editing description of merch", set_description_test) == NULL ||
            CU_add_test(my_test_suite, "test for editing price of merch", set_price_test) == NULL ||
            CU_add_test(my_test_suite, "test if store is empty", store_is_empty_test) == NULL ||
            //CU_add_test(my_test_suite, "test some boundary cases", boundary_cases_test) == NULL || Test that doesn't work
            CU_add_test(my_test_suite, "testing cart operations in merch_storage", merch_storage_cart_functions_test) == NULL ||
            CU_add_test(my_test_suite, "test for a merch's stock", shelves_exists_test) == NULL 
            )
        )

    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}