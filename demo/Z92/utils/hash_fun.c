#include <stdbool.h>
#include <string.h>
#include "hash_fun.h"

bool ioopm_int_eq(elem_t e1, elem_t e2)
{
    return (e1.integer == e2.integer);
}

bool ioopm_string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.string, e2.string) == 0);
}

unsigned ioopm_hash_fun_key_int(elem_t key)
{
  return key.integer;
}

unsigned ioopm_hash_fun_sum_key_string(elem_t key)
{
    char *str = key.string;
    unsigned result = 0;
    do
    {
        result += *str;
    }
    while (*++str != '\0');
    return result; 
}