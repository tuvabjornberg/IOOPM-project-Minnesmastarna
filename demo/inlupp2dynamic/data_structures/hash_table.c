#include "hash_table.h"
#include "common.h"
#include "linked_list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};

#define INITIAL_CAPACITY_HASHTABLE 17
#define BUCKET_THRESHOLD 1

/// the types from above
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

struct entry {
  elem_t key;    // holds the key
  elem_t value;  // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table 
{
  entry_t *buckets;
  size_t size;
  size_t ht_capacity;
  ioopm_hash_function hash_fun;
  ioopm_eq_function eq_fun;
};

static unsigned get_bucket_index(ioopm_hash_table_t *ht, ioopm_hash_function hash_fun, elem_t key) 
{
  return ht->hash_fun(key) % ht->ht_capacity;
}

size_t ioopm_get_ht_capacity(ioopm_hash_table_t *ht) 
{
  return ht->ht_capacity; 
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun) 
{
  ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
  ht->buckets = calloc(1, sizeof(entry_t) * INITIAL_CAPACITY_HASHTABLE);
  ht->hash_fun = hash_fun;
  ht->eq_fun = eq_fun;
  ht->size = 0;
  ht->ht_capacity = INITIAL_CAPACITY_HASHTABLE;
  
  return ht;
}

static void entry_destroy(entry_t *entry) 
{
  while (entry != NULL) 
  {
    entry_t *next = entry->next;
    free(entry);
    entry = next;
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  ioopm_hash_table_clear(ht);
  free(ht->buckets);
  free(ht);
}

// Creates a new entry with a given key, value and next pointer
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next) 
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
}

static entry_t *find_previous_entry_for_key(entry_t *bucket, elem_t key, ioopm_eq_function eq_fun) 
{
  entry_t *prev = bucket;
  
  assert(bucket != NULL);
  entry_t *current = bucket->next;

  while (current != NULL) 
  {
    if (eq_fun(current->key, key)) 
    {
      return prev;
    }
    prev = current;
    current = current->next;
  }

  return prev;
}

static void resize(ioopm_hash_table_t *ht, size_t new_ht_capacity) 
{
  entry_t *new_buckets = calloc(1, sizeof(entry_t) * new_ht_capacity);

  for (size_t i = 0; i < ht->ht_capacity; ++i) 
  {
    entry_t *current = ht->buckets[i].next;

    while (current != NULL) 
    {
      size_t new_index = ht->hash_fun(current->key) % new_ht_capacity;
      entry_t *new_entry = entry_create(current->key, current->value, new_buckets[new_index].next);
      
      entry_t *old_next = current->next; 
      free(current); 
      
      new_buckets[new_index].next = new_entry;
      current = old_next; 
    }
  }

  free(ht->buckets);
  ht->buckets = new_buckets;
  ht->ht_capacity = new_ht_capacity;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value) 
{
  if ((double)ht->size / ht->ht_capacity > BUCKET_THRESHOLD) 
  {
    size_t new_ht_capacity = ht->ht_capacity * 2;
    resize(ht, new_ht_capacity);
  }

  unsigned bucket_index = get_bucket_index(ht, ht->hash_fun, key);

  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket_index], key, ht->eq_fun);
  entry_t *next = entry->next;

  if (next == NULL) 
  {
    entry->next = entry_create(key, value, next);
    ht->size++;

  } 
  else 
  {
    next->value = value;
  }
}

option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key) 
{
  unsigned bucket_index = get_bucket_index(ht, ht->hash_fun, key);

  option_t *lookup_result = calloc(1, sizeof(option_t));
  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key, ht->eq_fun);
  entry_t *current = prev->next;

  if (current != NULL) 
  {
    *lookup_result = Success(current->value);
  } 
  else 
  {
    *lookup_result = Failure();
  }

  return lookup_result;
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
 {
  unsigned bucket_index = get_bucket_index(ht, ht->hash_fun, key);

  option_t *lookup_result = ioopm_hash_table_lookup(ht, key);

  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key, ht->eq_fun);
  entry_t *current = prev->next;
  elem_t removed_value;

  if (lookup_result->success) 
  {
    removed_value = current->value;

    if (current->next == NULL) 
    {
      // for last entries
      prev->next = NULL;
      free(current);
    } 
    else 
    {
      // for first and middle entries
      prev->next = current->next;
      free(current);
    }
  } 
  else 
  {
    // error handeling
    removed_value.void_ptr = NULL;
  }

  free(lookup_result);
  ht->size--; 
  return removed_value;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) 
{
  int counter = 0;

  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *cursor = &ht->buckets[i];

    while (cursor->next != NULL) 
    {
      counter++;
      cursor = cursor->next;
    }
  }
  return counter;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *cursor = &ht->buckets[i];

    if (cursor->next != NULL) 
    {
      return false;
    }
  }
  return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_destroy((&ht->buckets[i])->next);
    ht->buckets[i].next = NULL; // reset all dangling pointers
  }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht) 
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->eq_fun);

  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      ioopm_linked_list_append(list, current->key);
      current = current->next;
    }
  }
  return list;
}

// functions the same as hash_table_keys, only difference is the name
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht) 
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->eq_fun);

  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      ioopm_linked_list_append(list, current->value);
      current = current->next;
    }
  }
  return list;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key) 
{
  option_t *lookup_result = ioopm_hash_table_lookup(ht, key);

  if (lookup_result->success) 
  {
    free(lookup_result);
    return true;
  } 
  else 
  {
    free(lookup_result);
    return false;
  }
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      char *duplicate = strdup(current->value.string);

      // test using both the identical string and the equivalent string
      if (!strcmp(current->value.string, value.string) && !strcmp(duplicate, value.string) && current->value.string == value.string) 
      {
        free(duplicate);
        return true;
      }

      free(duplicate);
      current = current->next;
    }
  }
  return false;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      if (pred(current->key, current->value, arg)) 
      {
        return true;
      }
      current = current->next;
    }
  }
  return false;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      if (!pred(current->key, current->value, arg)) 
      {
        return false;
      }
      current = current->next;
    }
  }
  return true;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg) 
{
  for (int i = 0; i < ht->ht_capacity; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      apply_fun(current->key, &current->value, arg); // address of value to apply function
      current = current->next;
    }
  }
}

