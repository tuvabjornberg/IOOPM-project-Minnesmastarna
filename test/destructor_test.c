#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/refmem.h"

void destructor(obj *obj){

}

void default_destructor(obj *obj){

}



int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_allocate_destructor() {
    obj* obj1 = allocate(sizeof(int), destructor()); 
    obj* obj2 = allocate(sizeof(int), destructor());

    CU_ASSERT_PTR_NOT_NULL(obj1);
    CU_ASSERT_EQUAL(rc(obj1), 0);

    CU_ASSERT_PTR_NOT_NULL(obj2);
    CU_ASSERT_EQUAL(rc(obj2), 0);

    destructor(obj1);
    destructor(obj2);

    deallocate(obj1);
    deallocate(obj2);
}

void test_array_allocate_destructor() {
    obj* obj_arr1 = allocate_array(5, sizeof(int), destructor());
    CU_ASSERT_EQUAL(rc(obj_arr1), 0);
    destructor(obj_arr1); 
    deallocate(obj_arr1);

    obj* obj_arr2 = allocate_array(0, sizeof(int), destructor()); 
    CU_ASSERT_EQUAL(rc(obj_arr2), 0);
    destructor(obj_arr2); 
    deallocate(obj_arr2);
}

void test_default_destructor() {
    obj* obj1 = allocate(sizeof(int), NULL);
    obj* obj_arr = allocate_array(0, sizeof(int), NULL);

    CU_ASSERT_EQUAL(rc(obj1), 0);
    CU_ASSERT_EQUAL(rc(obj_arr), 0);

    default_destructor(obj1);
    default_destructor(obj_arr);

    deallocate(obj1);
    deallocate(obj_arr);
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for destructors", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "a simple allocate destructor test", test_allocate_destructor) == NULL ||
        CU_add_test(my_test_suite, "a simple allocate array destructor test", test_array_allocate_destructor) == NULL ||
        CU_add_test(my_test_suite, "a simple default destructor test", test_default_destructor) == NULL 



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