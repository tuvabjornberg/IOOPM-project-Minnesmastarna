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

struct iter
{
    link_t *current;
    list_t *list;
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

void linked_list_prepend(list_t *list, elem_t value)
{
    link_t *new_link = link_create(value, list->first);

    if (new_link != NULL)
    {
        list->first = new_link;

        if (list->last == NULL)
        {
            // if empty list
            list->last = new_link;
        }

        list->size++;
    }
}

void linked_list_insert(list_t *list, int index, elem_t value)
{
    link_t *current = list->first;
    int counter = 0;
    size_t ll_size = linked_list_size(list);

    if (index < 0 || index > ll_size)
    {
        return;
    }
    else if (index == 0)
    {
        linked_list_prepend(list, value);
    }
    else if (index == ll_size)
    {
        linked_list_append(list, value);
    }
    else
    {
        while (index > 0 && index < ll_size - 1 && counter < index)
        {
            if (counter == index - 1)
            {
                link_t *new_link = link_create(value, NULL);
                link_t *tmp = current->next;
                current->next = new_link;
                new_link->next = tmp;
                list->size++;
            }
            counter++;
            current = current->next;
        }
    }
}

elem_t linked_list_remove(list_t *list, int index)
{
    link_t *current = list->first;
    int counter = 0;
    size_t ll_size = linked_list_size(list);
    elem_t value = {.void_ptr = NULL};

    if (list != NULL)
    {
        if (index < 0 || index >= ll_size)
        {
            return (elem_t){.void_ptr = NULL};
        }
        // first index
        else if (index == 0)
        {
            value = list->first->value;
            link_t *tmp = list->first->next;
            free(list->first);
            list->first = tmp;
            list->size--;
        }
        else
        {
            while (index > 0 && index < ll_size && counter < index)
            {
                // middle and last index
                if (counter == index - 1)
                {
                    value = current->next->value;
                    link_t *tmp = current->next->next;
                    free(current->next);
                    current->next = tmp;
                    list->size--;
                }

                counter++;
                current = current->next;
            }
        }
    }
    return value;
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


elem_t linked_list_get(list_t *list, int index)
{
    link_t *current = list->first;
    int counter = 0;
    // if correct index input
    if (index >= 0 && index < linked_list_size(list))
    {
        while (counter != index)
        {
            current = current->next;
            counter++;
        }

        return current->value;
    }
    else
    {
        return (elem_t){.void_ptr = NULL};
    }
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

size_t linked_list_size(list_t *list)
{
    return list->size;
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

bool linked_list_all(list_t *list, int_predicate prop, void *extra)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        if (!prop(current->value, extra))
        {
            return false;
        }

        current = current->next;
    }

    return true;
}

bool linked_list_any(list_t *list, int_predicate prop, void *extra)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        if (prop(current->value, extra))
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

void linked_list_apply_to_all(list_t *list, apply_int_function fun, void *extra)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        fun(&current->value, extra);
        current = current->next;
    }
}

list_iterator_t *list_iterator(list_t *list)
{
    list_iterator_t *iter = calloc(1, sizeof(list_iterator_t));

    iter->list = list;
    iter->current = list->first;

    return iter;
}

bool iterator_has_next(list_iterator_t *iter)
{
    if (iter->current != NULL)
    {
        return iter->current->next != NULL;
    }
    else
    {
        return false;
    }
}

elem_t iterator_next(list_iterator_t *iter)
{
    if (!iterator_has_next(iter))
    {

        return (elem_t){.void_ptr = NULL};
    }

    iter->current = iter->current->next;
    return iter->current->value;
}

void iterator_reset(list_iterator_t *iter)
{
    if (iter->current != NULL)
    {
        iter->current = iter->list->first;
    }
    else
    {
        iter->list->first = NULL;
    }
}

elem_t iterator_current(list_iterator_t *iter)
{
    if (iter->current != NULL)
    {
        return iter->current->value;
    }
    else
    {
        return (elem_t){.void_ptr = NULL};
    }
}
void iterator_destroy(list_iterator_t *iter)
{
    free(iter);
}