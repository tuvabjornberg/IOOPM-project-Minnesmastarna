#include <stdlib.h>
#include "list.h"
#include "common.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct link link_t;

struct link
{
    elem_t value;
    struct link *next;
};
struct list
{
    link_t *first;
    link_t *last;
    size_t size;
    eq_function eq_fun;
};

list_t *linked_list_create(eq_function eq_fun)
{
    list_t *list = calloc(1, sizeof(struct list));
    list->eq_fun = eq_fun;
    list->size = 0;
    return list;
}

void linked_list_destroy(list_t *list)
{
    if (list != NULL) {
        if (!linked_list_is_empty(list))
        {
            linked_list_clear(list);
        }
    }
    free(list);
}

static link_t *link_create(elem_t value, link_t *next)
{
    link_t *new_link = calloc(1, sizeof(link_t));
    new_link->value = value;
    new_link->next = next;
    return new_link;
}

void linked_list_append(list_t *list, elem_t value)
{
    link_t *new_link = link_create(value, NULL);

    if (new_link != NULL)
    {
        if (list->last == NULL)
        {
            // if empty list
            list->first = new_link;
        }
        else
        {
            // if non-empty list
            list->last->next = new_link;
        }

        list->last = new_link;
        list->size++;
    }
}

void linked_list_remove_object(list_t *list, obj *obj_ptr)
{
    //elem_t value = {.void_ptr = NULL};
    if (list == NULL || obj_ptr == NULL)
    {
        return; // value;
    }

    link_t *current = list->first;
    link_t *prev = NULL;

    while (current != NULL)
    {
        if (current->value.void_ptr == obj_ptr)
        {
            //value = current->value;
            if (prev == NULL)
            {
                list->first = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current);
            list->size--;
            return; // value;
        }

        prev = current;
        current = current->next;
    }

    return; // value;
}


bool linked_list_contains(list_t *list, elem_t element)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        if (list->eq_fun(current->value, element))
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool linked_list_is_empty(list_t *list)
{
    return list->size == 0;
}

void linked_list_clear(list_t *list)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        link_t *next = current->next;
        free(current);
        current = next;
        list->size--;
    }
}
