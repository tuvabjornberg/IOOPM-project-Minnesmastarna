#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/queue.h" 
#include "../src/refmem.h"

// **** TEST DESTRUCTORS ****
void string_destructor(obj *o) {
    char *string = o;
    printf("%s SUCCESS", string);
}

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_default_destructor(void) {
    struct my_struct {
        obj *internal_obj;
    };

    struct my_struct *test_obj = allocate(sizeof(struct my_struct), NULL);
    test_obj->internal_obj = allocate(sizeof(int), NULL);
    retain(test_obj->internal_obj);

    default_destructor(test_obj);
    CU_ASSERT_EQUAL(rc(test_obj->internal_obj), 0);

    deallocate(test_obj->internal_obj);
}

void test_string_destructor() {
    char *my_string = allocate(sizeof(char*), string_destructor);
    my_string = "testingtesting123";
    deallocate(my_string);    
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite my_test_suite = CU_add_suite("Tests for queue.c", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "Test default destructor", test_default_destructor) == NULL ||
        CU_add_test(my_test_suite, "Test for string destructor", test_string_destructor) == NULL)
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
