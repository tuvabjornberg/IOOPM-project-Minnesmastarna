#include "../data_structures/hash_table.h"
#include <CUnit/Basic.h>
#include "../data_structures/linked_list.h"
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

static unsigned hash_fun_key_int(elem_t key)
{
  return key.integer;
}

static bool bool_eq_fun(elem_t a, elem_t b)
{
    return b.integer == a.integer;
}

static void insert_set_elements(ioopm_hash_table_t *ht, elem_t *arr_keys, elem_t *arr_values, int length)
{
    for (int i = 0; i < length; ++i)
    {
        ioopm_hash_table_insert(ht, arr_keys[i], arr_values[i]);
    }
}

void test_create_destroy()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);
    CU_ASSERT_PTR_NOT_NULL(ht);

    release(ht);
    shutdown();
}

void test_insert_once()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);
    elem_t invalid_key = {.integer = -1};

    elem_t key[] = {{.integer = 1}, {.integer = 18}};
    elem_t value[] = {str_elem("value1"), str_elem("value2")};

    insert_set_elements(ht, key, value, 2);

    // Test existing key1
    option_t *lookup_result = ioopm_hash_table_lookup(ht, key[0]);

    CU_ASSERT_TRUE(Successful((*lookup_result)));
    CU_ASSERT_STRING_EQUAL("value1", lookup_result->value.string);
    release(lookup_result);

    // Test existing key2
    lookup_result = ioopm_hash_table_lookup(ht, key[1]);
    CU_ASSERT_TRUE(Successful((*lookup_result)));
    CU_ASSERT_STRING_EQUAL("value2", lookup_result->value.string);
    release(lookup_result);

    //Insert new value to existing key
    ioopm_hash_table_insert(ht, key[0], (elem_t) {.string = "updated_value"});
    lookup_result = ioopm_hash_table_lookup(ht, key[0]);
    CU_ASSERT_STRING_EQUAL("updated_value", lookup_result->value.string);
    release(lookup_result);

    // Test invalid_key
    lookup_result = ioopm_hash_table_lookup(ht, invalid_key);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    release(ht);
    shutdown();
}

void test_lookup_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    for (elem_t i = {.integer = 0}; i.integer < No_Buckets; ++i.integer)
    {
        option_t *lookup_result = ioopm_hash_table_lookup(ht, i);
        CU_ASSERT_FALSE(lookup_result->success);
        release(lookup_result);
    }

    elem_t invalid_lookup = {.integer = -1};
    option_t *lookup_result = ioopm_hash_table_lookup(ht, invalid_lookup);
    CU_ASSERT_FALSE(lookup_result->success);
    release(lookup_result);

    release(ht);
    shutdown();
}

//TODO: Big memleak :(
void test_remove_entry()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 18}, {.integer = 35}, {.integer = 52}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}, {.string = "value4"}};

    insert_set_elements(ht, key, value, 4);

    // Remove inserted item (middle)
    elem_t value_removed = ioopm_hash_table_remove(ht, key[1]);
    option_t *lookup_result = ioopm_hash_table_lookup(ht, key[1]);
    CU_ASSERT_STRING_EQUAL("value2", value_removed.string);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    // Remove inserted item (last)
    value_removed = ioopm_hash_table_remove(ht, key[3]);
    lookup_result = ioopm_hash_table_lookup(ht, key[3]);
    CU_ASSERT_STRING_EQUAL("value4", value_removed.string);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    // Remove inserted item (first)
    value_removed = ioopm_hash_table_remove(ht, key[0]);
    lookup_result = ioopm_hash_table_lookup(ht, key[0]);
    CU_ASSERT_STRING_EQUAL("value1", value_removed.string);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    // Remove for not inserted item
    value_removed = ioopm_hash_table_remove(ht, key[0]);
    lookup_result = ioopm_hash_table_lookup(ht, key[0]);
    CU_ASSERT_PTR_NULL(value_removed.void_ptr);

    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    release(ht);
    shutdown();
}

void test_size_hash_table()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);
    CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));

    elem_t key[] = {{.integer = 1}, {.integer = 2}, {.integer = 18}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 3);

    CU_ASSERT_EQUAL(3, ioopm_hash_table_size(ht));

    ioopm_hash_table_clear(ht);
    CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));

    release(ht);
    shutdown();
}

void test_is_empty_hash_table()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

    ioopm_int_str_ht_insert(ht, 1, "value1");
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

    ioopm_hash_table_clear(ht);
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

    release(ht);
    shutdown();
}

void test_clear_hash_table()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 2}, {.integer = 18}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 3);

    ioopm_hash_table_clear(ht);
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

    option_t *lookup_result = ioopm_hash_table_lookup(ht, key[2]);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    release(lookup_result);

    CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));

    release(ht);
    shutdown();
}

void test_table_keys()
{
    elem_t keys_to_test[] = {{.integer = 3}, {.integer = 10}, {.integer = 42}, {.integer = 0}, {.integer = 99}};
    bool found[5] = {false};
    elem_t not_important_str = {.string = "not important"};

    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    for (int i = 0; i < 5; i++)
    {
        ioopm_hash_table_insert(ht, keys_to_test[i], not_important_str);
    }

    ioopm_list_t *keys_from_ht = ioopm_hash_table_keys(ht);

    // iterate over the reuslting array
    for (int i = 0; i < 5; i++)
    {
        // for each key, find the  index of the key in keys and set that index to true in found.
        for (int j = 0; j < 5; j++)
        {
            if (keys_to_test[j].integer == ioopm_linked_list_get(keys_from_ht, i).integer)
            {
                found[i] = true;
            }

        }

        if (!found[i])
        {
            CU_FAIL("Found a key that was never inserted!");
        }
    }

    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_TRUE(found[i]);
    }

    release(keys_from_ht);
    release(ht);
    shutdown();
}

void test_table_values()
{
    elem_t keys_to_test[] = {{.integer = 3}, {.integer = 10}, {.integer = 42}, {.integer = 0}, {.integer = 99}};
    elem_t values_to_test[] = {{.string = "three"}, {.string = "ten"}, {.string = "fortytwo"},
                                {.string = "zero"}, {.string = "ninetynine"}};
    bool found[5] = {false};

    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    insert_set_elements(ht, keys_to_test, values_to_test, 5);

    ioopm_list_t *keys_from_ht = ioopm_hash_table_keys(ht);
    ioopm_list_t *values_from_ht = ioopm_hash_table_values(ht);

    // iterate over the reuslting array
    for (int i = 0; i < 5; i++)
    {
        bool key_found = false;
        bool value_found = false;

        for (int j = 0; j < 5; j++)
        {
            // for each key and value at the same index, separated for debugging
            if (keys_to_test[j].integer == ioopm_linked_list_get(keys_from_ht, i).integer)
            {
                key_found = true;

                if (values_to_test[j].string == ioopm_linked_list_get(values_from_ht, i).string)
                {
                    value_found = true;
                }
            }
        }

        if (!key_found)
        {
            CU_FAIL("Found a key that was never inserted!");
        }
        else if (!value_found)
        {
            CU_FAIL("Value mismatch for key");
        }
        else
        {
            found[i] = true;
        }
    }
    release(values_from_ht);
        release(keys_from_ht);

    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_TRUE(found[i]);
    }

    release(ht);
    shutdown();
}

void test_ht_has_key()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 2}, {.integer = 18}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 2);

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key[1]));
    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key[2]));

    release(ht);
    shutdown();
}

void test_ht_has_value()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 18}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 2);

    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, value[1]));
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, value[2]));

    release(ht);
    shutdown();
}

static bool key_equiv(elem_t key, elem_t value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key.integer == other_key;
}

void test_ht_has_any()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 18}, {.integer = 27}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 3);

    elem_t false_key = {.integer = 17};


    CU_ASSERT_TRUE(ioopm_hash_table_any(ht, key_equiv, &key[1]));
    CU_ASSERT_FALSE(ioopm_hash_table_any(ht, key_equiv, &false_key));

    release(ht);
    shutdown();
}

static bool mod_equiv(elem_t key, elem_t value_ignored, void *x)
{
    // cast arg to int* and dereference it
    return key.integer % *((int *)x) == 1;
}

static bool starts_with_char(elem_t key, elem_t value, void *arg) {
    // cast arg to char and dereference it
    return value.string[0] == *((char *)arg);
}

void test_ht_has_all()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    elem_t key[] = {{.integer = 1}, {.integer = 18}, {.integer = 35}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 3);

    int mod = 17;
    elem_t false_value = {.string = "no"};

    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, mod_equiv, &mod));
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, mod_equiv, &false_value)); //false_value will be converted to int (ascii)

    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, starts_with_char, "v"))

    release(ht);
    shutdown();
}

static void add_version_value(elem_t key_ignored, elem_t *value, void *arg)
{
    char *version = (char *)arg;
    char *original_value = value->string;

    // allocate memory for the new value, since new value has more characters than the original
    char *new_value = allocate_array(strlen(version) + 1, strlen(original_value) * 8, NULL); // +1 for null-terminator

    strcpy(new_value, version);
    strcat(new_value, original_value);

    value->string = new_value;
}

void test_ht_apply_to_all()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);
    char *version = "version 2: ";
    char *expected_values[3] =  {"version 2: value1", "version 2: value2", "version 2: value3"};
    bool found[3] = {false};

    elem_t key[] = {{.integer = 1}, {.integer = 18}, {.integer = 27}};
    elem_t value[] = {{.string = "value1"}, {.string = "value2"}, {.string = "value3"}};
    insert_set_elements(ht, key, value, 3);

    ioopm_hash_table_apply_to_all(ht, add_version_value, version);

    ioopm_list_t *array_of_applied = ioopm_hash_table_values(ht);

    for (int i = 0; i < 3; i++)
    {
        bool value_updated = false;
        char *value_after_apply = ioopm_linked_list_get(array_of_applied, i).string;
        retain(value_after_apply);

        if (!strcmp(value_after_apply, expected_values[i]))
        {
            value_updated = true;
        }

        if (!value_updated)
        {
            CU_FAIL("Value not updated");
        }
        else
        {
            found[i] = true;
        }
        release(value_after_apply);
    }

    for (int i = 0; i < 3; i++)
    {
        CU_ASSERT_TRUE(found[i]);
    }

    release(array_of_applied);
    release(ht);
    shutdown();
}

void boundary_test()
{   
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun_key_int, bool_eq_fun);

    for (int i = 0; i < 1000; i++)
    {
        ioopm_hash_table_insert(ht, int_elem(i), str_elem(duplicate_string("value1")));
    }

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1000); 

    for (int i = 0; i < 1000; i++)
    {
        ioopm_hash_table_remove(ht, int_elem(i));
    }

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0); 

    release(ht);
    shutdown();
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for hash_table.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "A simple create and destroy test", test_create_destroy) == NULL ||
         CU_add_test(my_test_suite, "A simple insert and lookup test", test_insert_once) == NULL ||
         CU_add_test(my_test_suite, "Empty lookup", test_lookup_empty) == NULL  ||
         CU_add_test(my_test_suite, "Remove a single element", test_remove_entry) == NULL ||
         CU_add_test(my_test_suite, "Test size of a hash_table", test_size_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Test for an empty hash table", test_is_empty_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Clearing a hash_table", test_clear_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Test on a generated array of keys", test_table_keys) == NULL ||
         CU_add_test(my_test_suite, "Test on a generated array of values", test_table_values) == NULL ||
         CU_add_test(my_test_suite, "If hash table has key", test_ht_has_key) == NULL ||
         CU_add_test(my_test_suite, "If hash table has value", test_ht_has_value) == NULL ||
         CU_add_test(my_test_suite, "Predicate function that satisfies any antry", test_ht_has_any) == NULL ||
         CU_add_test(my_test_suite, "Predicate function that satisfies all entries", test_ht_has_all) == NULL ||
         CU_add_test(my_test_suite, "Apply function on all entries", test_ht_apply_to_all) == NULL ||
         CU_add_test(my_test_suite, "Boundary test", boundary_test) == NULL
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
