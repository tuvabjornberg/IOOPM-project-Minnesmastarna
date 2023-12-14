#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/refmem.h"
#include "../src/queue.h"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_allocate_deallocate()
{
    obj* obj = allocate(sizeof(int), NULL);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(rc(obj), 0);
    deallocate(obj);
}

void test_retain()
{
    obj* obj1 = allocate(sizeof(int), NULL);

    retain(obj1);
    CU_ASSERT_EQUAL(rc(obj1), 1);

    for (int i = 0; i < 100; i++) {
        retain(obj1);
    }
    CU_ASSERT_EQUAL(rc(obj1), 101);

    deallocate(obj1);
}

void test_release()
{
    obj* obj1 = allocate(sizeof(int), NULL);

    retain(obj1);
    retain(obj1);
    CU_ASSERT_EQUAL(rc(obj1), 2);

    release(obj1);
    CU_ASSERT_EQUAL(rc(obj1), 1);

    for (int i = 0; i < 100; i++) {
        retain(obj1);
    }
    CU_ASSERT_EQUAL(rc(obj1), 101);

    for (int i = 0; i < 100; i++) {
        release(obj1);
    }
    CU_ASSERT_EQUAL(rc(obj1), 1);

    deallocate(obj1);
}

void test_allocate_deallocate_array()
{
    obj* obj_arr1 = allocate_array(5, sizeof(int), NULL);
    CU_ASSERT_EQUAL(rc(obj_arr1), 0);
    deallocate(obj_arr1);

    obj* obj_arr2 = allocate_array(0, sizeof(int), NULL);
    CU_ASSERT_EQUAL(rc(obj_arr2), 0);
    deallocate(obj_arr2);
}

void test_retain_array()
{
    obj* obj_arr = allocate_array(5, sizeof(int), NULL);

    retain(obj_arr);
    CU_ASSERT_EQUAL(rc(obj_arr), 1);

    for (int i = 0; i < 100; i++) {
        retain(obj_arr);
    }
    CU_ASSERT_EQUAL(rc(obj_arr), 101);

    deallocate(obj_arr);
}

void test_release_array()
{
    obj* obj_arr = allocate_array(5, sizeof(int), NULL);

    retain(obj_arr);
    retain(obj_arr);
    CU_ASSERT_EQUAL(rc(obj_arr), 2);

    release(obj_arr);
    CU_ASSERT_EQUAL(rc(obj_arr), 1);

    for (int i = 0; i < 100; i++) {
        retain(obj_arr);
    }
    CU_ASSERT_EQUAL(rc(obj_arr), 101);

    for (int i = 0; i < 100; i++) {
        release(obj_arr);
    }
    CU_ASSERT_EQUAL(rc(obj_arr), 1);

    deallocate(obj_arr);
}

void set_get_cascade_limit()
{
    CU_ASSERT_EQUAL(get_cascade_limit(), 5);

    size_t new_cascade_limit = 10;
    set_cascade_limit(new_cascade_limit);

    CU_ASSERT_EQUAL(get_cascade_limit(), new_cascade_limit);
}

void integration_cleanup_test()
{
    cleanup();

    obj* obj1 = allocate(sizeof(int), NULL);
    obj* obj2 = allocate(sizeof(int), NULL);

    retain(obj1);
    retain(obj2);

    release(obj1);
    release(obj2);

    obj* obj3 = allocate(sizeof(int), NULL);
    release(obj3);
    obj* obj4 = allocate(sizeof(int), NULL);
    release(obj4);

    cleanup();

    shutdown();

    puts("Integration test complete");
}

void test_rc_overflow()
{
    obj* obj = allocate(sizeof(int), NULL);
    for (int i = 0; i <= 65540; i++) { // 65540 > 65535, which leads to reference count overflow
        retain(obj);
    }
    CU_ASSERT_PTR_NULL(obj); // Reference count overflow should lead to the object being destroyed
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for refmem.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "a simple allocate/deallocate test", test_allocate_deallocate) == NULL ||
        CU_add_test(my_test_suite, "a simple retain test", test_retain) == NULL ||
        CU_add_test(my_test_suite, "a simple release test", test_release) == NULL ||
        CU_add_test(my_test_suite, "a simple allocate/deallocate array test", test_allocate_deallocate_array) == NULL ||
        CU_add_test(my_test_suite, "retain test for array", test_retain_array) == NULL ||
        CU_add_test(my_test_suite, "release test for array", test_release_array) == NULL ||
        CU_add_test(my_test_suite, "set and get cascade limit", set_get_cascade_limit) == NULL ||
        CU_add_test(my_test_suite, "cleanup test", integration_cleanup_test) == NULL ||
        CU_add_test(my_test_suite, "reference count overflow test", test_rc_overflow) == NULL
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
