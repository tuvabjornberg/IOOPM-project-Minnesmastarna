#pragma once
#include <stdbool.h>

#define int_elem(x) (elem_t) { .integer=(x) }
#define str_elem(x) (elem_t) { .string=(x) }
#define void_elem(x) (elem_t) { .void_ptr=(x) }

/**
 * @file common.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 29/09-2023
 * @brief Provides a set of common utilities and data types
 *
 * It includes a flexible elem_t union to represent various data
 * types and definitions for equality and hash functions.
 *
 * It is assumed that a suitable hash_function (hash_fun) and equality function
 * is implemented to fit the elem_t type (eq_fun).
 */

typedef union elem elem_t;

union elem
{
    int integer;
    unsigned int unsigned_integer;
    bool boolean;
    float float_number;
    char *string;
    void *void_ptr;
};

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

typedef unsigned int(*ioopm_hash_function)(elem_t key);