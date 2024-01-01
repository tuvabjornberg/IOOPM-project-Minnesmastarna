#include <CUnit/Basic.h>
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"
#include "../data_structures/common.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../../../src/refmem.h"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

static bool bool_eq_fun(elem_t a, elem_t b) 
{
    return b.integer == a.integer; 
}

static void append_ints_to_list(ioopm_list_t *list, elem_t *values, int length)
{
    for (int i = 0; i < length; ++i) 
    {
        ioopm_linked_list_append(list, values[i]);
        CU_ASSERT_TRUE(ioopm_linked_list_get(list, i).integer == values[i].integer);
    }
}

void test_create_destroy()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    CU_ASSERT_PTR_NOT_NULL(list);
    release(list);
    shutdown();
}

void test_append()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;
    append_ints_to_list(list, values, length);

    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4);

    elem_t false_contain = {.integer = 5}; 
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, false_contain));

    release(list);
    shutdown();
}

void test_prepend()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    elem_t false_contain = {.integer = 5}; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_prepend(list, values[i]);
        CU_ASSERT_TRUE(ioopm_linked_list_contains(list, values[i]));
    }
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4);
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, false_contain));

    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).integer, 2);
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 1).integer == 3);

    release(list);
    shutdown();
}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;
    elem_t value_insert = {.integer = 5};

    // insert invalid index
    ioopm_linked_list_insert(list, 2, value_insert);
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, value_insert));
    CU_ASSERT_PTR_NULL(ioopm_linked_list_get(list, 2).void_ptr); 

    append_ints_to_list(list, values, length);

    // insert item in the middle
    ioopm_linked_list_insert(list, 2, value_insert);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 5);
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, value_insert));
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).integer, 5);

    // insert first in list
    ioopm_linked_list_insert(list, 0, value_insert);
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2).integer == 2);
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).integer, 5);

    // insert last in list
    ioopm_linked_list_insert(list, 6, value_insert);
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 6).integer == 5);
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 5).integer, 4);

    release(list);
    shutdown();
}

void test_remove()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    // remove from invalid index
    elem_t return_value = ioopm_linked_list_remove(list, 3);
    CU_ASSERT_PTR_NULL(return_value.void_ptr); 

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}, {.integer = 5}, 
                        {.integer = 6}, {.integer = 7}, {.integer = 8}};
    int length = 8;

    append_ints_to_list(list, values, length);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 8);

    // remove first item
    return_value = ioopm_linked_list_remove(list, 0);
    int size = ioopm_linked_list_size(list);
    CU_ASSERT_EQUAL(return_value.integer, 1);
    CU_ASSERT_EQUAL(size, 7);
    for (int i = 0; i < size - 1; i++)
    {
        CU_ASSERT_EQUAL(ioopm_linked_list_get(list, i).integer, i + 2);
    }

    // remove last item
    return_value = ioopm_linked_list_remove(list, 6);
    size = ioopm_linked_list_size(list);
    CU_ASSERT_EQUAL(return_value.integer, 8);
    CU_ASSERT_EQUAL(size, 6);
    for (int i = 0; i < size - 1; i++)
    {
        CU_ASSERT_EQUAL(ioopm_linked_list_get(list, i).integer, i + 2);
    }

    // remove middle item
    return_value = ioopm_linked_list_remove(list, 2);
    size = ioopm_linked_list_size(list);
    CU_ASSERT_EQUAL(return_value.integer, 4);
    CU_ASSERT_EQUAL(size, 5);
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2).integer == 5);
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 4).integer, 7);

    release(list);
    shutdown();
}

void test_get()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    CU_ASSERT_PTR_NULL(ioopm_linked_list_get(list, 2).void_ptr); 

    elem_t values[] = {{.integer = 9}, {.integer = 8}, {.integer = 7}, {.integer = 6}};
    elem_t value_insert = {.integer = 5}; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]);
    }

    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).integer, 7);

    ioopm_linked_list_insert(list, 2, value_insert);
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2).integer == 5);

    release(list);
    shutdown();
}

void test_contains()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;
    elem_t false_value = {.integer = 5};

    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, false_value));

    append_ints_to_list(list, values, length);

    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, values[2]));
    CU_ASSERT_EQUAL(ioopm_linked_list_contains(list, values[2]), true)
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, false_value));

    release(list);
    shutdown();
}

void test_size()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), NULL)

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;

    append_ints_to_list(list, values, length);

    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4)

    // append
    ioopm_int_ll_append(list, 5);
    CU_ASSERT_TRUE(ioopm_linked_list_size(list) == 5);

    // prepend
    ioopm_int_ll_prepend(list, 5);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 6);

    // insert
    ioopm_int_ll_insert(list, 3, 5); 
    CU_ASSERT_TRUE(ioopm_linked_list_size(list) == 7);

    release(list);
    shutdown();
}

void test_is_empty()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));

    ioopm_int_ll_append(list, 1); 
    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

    release(list);
    shutdown();
}

void test_clear()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;

    append_ints_to_list(list, values, length);

    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

    ioopm_linked_list_clear(list);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));

    release(list);
    shutdown();
}

static bool mod_equiv(elem_t num, void *mod)
{
    return num.integer % *(int *)mod == 0;
}

void test_all()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 2}, {.integer = 4}, {.integer = 8}, {.integer = 12}};
    int length = 4;
    int mod_test = 2;

    append_ints_to_list(list, values, length);

    CU_ASSERT_TRUE(ioopm_linked_list_all(list, mod_equiv, &mod_test));
    ioopm_int_ll_insert(list, 2, 5); 
    CU_ASSERT_FALSE(ioopm_linked_list_all(list, mod_equiv, &mod_test));

    release(list);
    shutdown();
}

static void add_value_to_int(elem_t *num, void *add)
{
    num->integer = num->integer + *(int *)add;
}

void test_any()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 5}};
    int length = 4;
    int mod_test = 2;

    append_ints_to_list(list, values, length);

    CU_ASSERT_TRUE(ioopm_linked_list_any(list, mod_equiv, &mod_test));

    ioopm_linked_list_remove(list, 1);
    CU_ASSERT_FALSE(ioopm_linked_list_any(list, mod_equiv, &mod_test));

    release(list);
    shutdown();
}

void test_apply_to_all()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;

    append_ints_to_list(list, values, length);

    int add_value = 10;
    ioopm_linked_list_apply_to_all(list, add_value_to_int, &add_value);

    int expected_values[4] = {11, 12, 13, 14};

    for (int i = 0; i < 4; i++)
    {
        CU_ASSERT_EQUAL(expected_values[i], ioopm_linked_list_get(list, i).integer);
    }

    release(list);
    shutdown();
}

void test_iterator_has_next() 
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));
    release(iter); 

    ioopm_int_ll_append(list, 1); 
    iter = ioopm_list_iterator(list);

    CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));
    release(iter); 

    ioopm_int_ll_append(list, 1); 
    ioopm_int_ll_append(list, 2); 
    iter = ioopm_list_iterator(list);

    CU_ASSERT_TRUE(ioopm_iterator_has_next(iter));

    release(iter); 
    release(list);
    shutdown();
}

void test_iterator_next()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_PTR_NULL(ioopm_iterator_next(iter).void_ptr); 
    release(iter);

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};

    ioopm_linked_list_append(list, values[0]);

    for (int i = 1; i < 4; i++)
    {
        ioopm_linked_list_prepend(list, values[i]);
        iter = ioopm_list_iterator(list);
        CU_ASSERT_EQUAL(ioopm_iterator_next(iter).integer, i);
        release(iter);
    }
 
    release(list);
    shutdown();
}

void test_iterator_reset()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_PTR_NULL(ioopm_iterator_current(iter).void_ptr); 
    ioopm_iterator_reset(iter);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 0);
    release(iter); 

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};
    int length = 4;

    append_ints_to_list(list, values, length);

    iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter);
    ioopm_iterator_next(iter);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 3);

    ioopm_iterator_reset(iter);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 1);

    release(iter); 
    release(list);
    shutdown();
}

void test_iterator_current()
{
    ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_PTR_NULL(ioopm_iterator_current(iter).void_ptr); 
    release(iter); 

    elem_t values[] = {{.integer = 1}, {.integer = 2}, {.integer = 3}, {.integer = 4}};

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_prepend(list, values[i]);
        iter = ioopm_list_iterator(list);
        CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, i + 1);
        release(iter); 
    }

    iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 3);

    ioopm_iterator_reset(iter);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 4);

    release(iter); 
    release(list);
    shutdown();
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for linked_list.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "A simple create and destroy test", test_create_destroy) == NULL ||
         CU_add_test(my_test_suite, "Append element to linked list", test_append) == NULL ||
         CU_add_test(my_test_suite, "Prepend element to linked list", test_prepend) == NULL ||
         CU_add_test(my_test_suite, "Insert test", test_insert) == NULL ||
         CU_add_test(my_test_suite, "A simple contain element test", test_contains) == NULL ||
         CU_add_test(my_test_suite, "Test for linked list size", test_size) == NULL ||
         CU_add_test(my_test_suite, "Test if list is empty", test_is_empty) == NULL ||
         CU_add_test(my_test_suite, "Get value correctly", test_get) == NULL ||
         CU_add_test(my_test_suite, "Test for removing elements", test_remove) == NULL ||
         CU_add_test(my_test_suite, "Test for clearing list", test_clear) == NULL ||
         CU_add_test(my_test_suite, "Test for all in list", test_all) == NULL ||
         CU_add_test(my_test_suite, "Test for any in list", test_any) == NULL ||
         CU_add_test(my_test_suite, "Test for apply to all in list", test_apply_to_all) == NULL ||
         CU_add_test(my_test_suite, "If iterator has more elements to go over", test_iterator_has_next) == NULL ||
         CU_add_test(my_test_suite, "The next element for iterator to go over", test_iterator_next) == NULL ||
         CU_add_test(my_test_suite, "Reposition iterator to start of list", test_iterator_reset) == NULL ||
         CU_add_test(my_test_suite, "Current element iterator goes over", test_iterator_current) == NULL))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
