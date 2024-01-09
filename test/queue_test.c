#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/queue.h"
#include "../src/refmem.h"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}


void create_destroy_test()
{
    Queue *q = create_queue();
    CU_ASSERT_PTR_NOT_NULL(q);
    destroy_queue(q);
}

void enqueue_test()
{
    Queue *q = create_queue();
    CU_ASSERT_TRUE(is_empty(q));

    obj* obj = NULL;
    enqueue(q, obj);
    CU_ASSERT_FALSE(is_empty(q));

    enqueue(q, obj);
    CU_ASSERT_FALSE(is_empty(q));

    destroy_queue(q);
}

void dequeue_test()
{
    Queue *q = create_queue();

    obj* obj = NULL;
    enqueue(q, obj);

    CU_ASSERT_FALSE(is_empty(q));
    CU_ASSERT_PTR_NULL(dequeue(q));
    CU_ASSERT_TRUE(is_empty(q));

    destroy_queue(q);
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
        (CU_add_test(my_test_suite, "a simpe create destroy test", create_destroy_test) == NULL ||
        CU_add_test(my_test_suite, "enqueue", enqueue_test) == NULL ||
        CU_add_test(my_test_suite, "dequeue test", dequeue_test) == NULL
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
