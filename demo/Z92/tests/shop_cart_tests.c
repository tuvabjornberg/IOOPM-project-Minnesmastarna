#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../logic/shop_cart.h"
#include "../utils/hash_fun.h"
#include "../../../src/refmem.h"

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

void create_destroy_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create(); 
    CU_ASSERT_PTR_NOT_NULL(storage_carts); 
    CU_ASSERT_TRUE(ioopm_carts_are_empty(storage_carts)); 
    release(storage_carts); 
    shutdown();
}

void add_to_cart_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create();
    ioopm_store_t *store = store_with_inputs();
    ioopm_cart_create(storage_carts);
    storage_carts->total_carts++;

    int id = 0;
    char *name = "Apple";
    char *merch_name = ioopm_merch_get(store, name)->name;
    int amount = 2;

    CU_ASSERT_EQUAL(ioopm_item_in_cart_amount(storage_carts, id, merch_name), 0);

    ioopm_cart_add(storage_carts, id, merch_name, amount); 
    CU_ASSERT_EQUAL(ioopm_item_in_cart_amount(storage_carts, id, merch_name), 2); 
    ioopm_cart_add(storage_carts, id, merch_name, amount); 
    CU_ASSERT_EQUAL(ioopm_item_in_cart_amount(storage_carts, id, merch_name), 4);  
    
    release(storage_carts); 
    release(store); 
    shutdown();
}

void remove_from_cart_test()
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

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id);

    ioopm_cart_remove(cart_items, merch_name, 1);
    CU_ASSERT_EQUAL(ioopm_item_in_cart_amount(storage_carts, id, merch_name), 1);

    ioopm_cart_remove(cart_items, merch_name, 1);
    CU_ASSERT_EQUAL(ioopm_item_in_cart_amount(storage_carts, id, merch_name), 0);

    release(storage_carts); 
    release(store);
    shutdown();
}

void remove_cart_test()
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

    CU_ASSERT_PTR_NOT_NULL(storage_carts->carts);
    ioopm_cart_destroy(storage_carts, 0);

    release(storage_carts); 
    release(store);
    shutdown();
}

void empty_cart_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create();
    CU_ASSERT_TRUE(ioopm_carts_are_empty(storage_carts));

    ioopm_cart_create(storage_carts);
    CU_ASSERT_FALSE(ioopm_carts_are_empty(storage_carts));

    release(storage_carts); 
    shutdown();
}

void has_merch_in_cart_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create();
    ioopm_store_t *store = store_with_inputs();
    ioopm_cart_create(storage_carts);
    storage_carts->total_carts++;

    int id = 0;
    char *name = "Apple";
    char *merch_name = ioopm_merch_get(store, name)->name;
    int amount = 2;

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id);
    CU_ASSERT_FALSE(ioopm_has_merch_in_cart(cart_items, merch_name));

    ioopm_cart_add(storage_carts, id, merch_name, amount);

    cart_items = ioopm_items_in_cart_get(storage_carts, id);
    CU_ASSERT_TRUE(ioopm_has_merch_in_cart(cart_items, merch_name));

    release(storage_carts);
    release(store); 
    shutdown();
}

void cost_calculate_test()
{
    ioopm_carts_t *storage_carts = ioopm_cart_storage_create();
    ioopm_store_t *store = store_with_inputs();
    ioopm_cart_create(storage_carts);
    storage_carts->total_carts++;

    int id = 0;
    char *name = "Apple";
    char *merch_name = ioopm_merch_get(store, name)->name;
    int amount = 2;

    CU_ASSERT_EQUAL(ioopm_cost_calculate(store, storage_carts, id), 0);

    ioopm_cart_add(storage_carts, id, merch_name, amount);

    CU_ASSERT_EQUAL(ioopm_cost_calculate(store, storage_carts, id), 20);

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id);
    ioopm_cart_remove(cart_items, merch_name, 1);
    CU_ASSERT_EQUAL(ioopm_cost_calculate(store, storage_carts, id), 10);

    release(storage_carts); 
    release(store); 
    shutdown();
}

void checkout_cart_test()
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

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, id);
    CU_ASSERT_TRUE(ioopm_has_merch_in_cart(cart_items, merch_name));

    ioopm_cart_checkout(store, storage_carts, 0);
    cart_items = ioopm_items_in_cart_get(storage_carts, id);
    CU_ASSERT_PTR_NULL(cart_items);
    CU_ASSERT_EQUAL(ioopm_merch_get(store, merch_name)->stock_size, 3);

    release(storage_carts); 
    release(store); 
    shutdown();
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for shop_cart.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "Create and destroy storage carts test", create_destroy_test) == NULL ||
         CU_add_test(my_test_suite, "Create and add to cart test", add_to_cart_test) == NULL ||
         CU_add_test(my_test_suite, "Remove from cart test", remove_from_cart_test) == NULL ||
         CU_add_test(my_test_suite, "Empty carts in store test", empty_cart_test) == NULL ||
         CU_add_test(my_test_suite, "Has merch in cart test", has_merch_in_cart_test) == NULL ||
         CU_add_test(my_test_suite, "Calculate total in cart", cost_calculate_test) == NULL ||
         CU_add_test(my_test_suite, "Checkout cart test", checkout_cart_test) == NULL ||
         CU_add_test(my_test_suite, "Test for removing a cart with items", remove_cart_test) == NULL
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
