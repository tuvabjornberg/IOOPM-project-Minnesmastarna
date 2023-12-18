#include <stdlib.h>
#include "linked_list.h"
#include "iterator.h"
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
    ioopm_eq_function eq_fun; 
};

struct iter
{
    link_t *current;
    ioopm_list_t *list;
};

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eq_fun)
{
    ioopm_list_t *list = calloc(1, sizeof(struct list)); //TODO: allocate_array
    list->eq_fun = eq_fun; 
    list->size = 0; 
    return list; 
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    if (!ioopm_linked_list_is_empty(list))
    {
        ioopm_linked_list_clear(list);
    }
    free(list); //TODO: deallocate
}

static link_t *link_create(elem_t value, link_t *next)
{
    link_t *new_link = calloc(1, sizeof(link_t)); //TODO: allocate_array
    new_link->value = value;
    new_link->next = next;
    return new_link;
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
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

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
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

void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value)
{
    link_t *current = list->first;
    int counter = 0;
    size_t linked_list_size = ioopm_linked_list_size(list);

    if (index < 0 || index > linked_list_size)
    {
        return;
    }
    else if (index == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else if (index == linked_list_size)
    {
        ioopm_linked_list_append(list, value);
    }
    else
    {
        while (index > 0 && index < linked_list_size - 1 && counter < index)
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

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    link_t *current = list->first;
    int counter = 0;
    size_t linked_list_size = ioopm_linked_list_size(list);
    elem_t value = {.void_ptr = NULL};

    if (list != NULL)
    {
        if (index < 0 || index >= linked_list_size)
        {
            return (elem_t){.void_ptr = NULL};
        }
        // first index
        else if (index == 0)
        {
            value = list->first->value;
            link_t *tmp = list->first->next;
            free(list->first); //TODO: deallocate
            list->first = tmp;
            list->size--;
        }
        else
        {
            while (index > 0 && index < linked_list_size && counter < index)
            {
                // middle and last index
                if (counter == index - 1)
                {
                    value = current->next->value;
                    link_t *tmp = current->next->next;
                    free(current->next); //TODO: deallocate
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

elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    link_t *current = list->first;
    int counter = 0;
    // if correct index input
    if (index >= 0 && index < ioopm_linked_list_size(list)) 
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

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
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

size_t ioopm_linked_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    return list->size == 0;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        link_t *next = current->next;
        free(current); //TODO: deallocate
        current = next;
        list->size--;
    }
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
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

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
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

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    link_t *current = list->first;

    while (current != NULL)
    {
        fun(&current->value, extra);
        current = current->next;
    }
}

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));//TODO: allocate_array

    iter->list = list;
    iter->current = list->first;

    return iter;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
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

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    if (!ioopm_iterator_has_next(iter))
    {
        
        return (elem_t){.void_ptr = NULL};
    }

    iter->current = iter->current->next;
    return iter->current->value;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
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

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
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
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);//TODO: deallocate
}