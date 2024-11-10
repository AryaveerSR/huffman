#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hashtable.h"
#include "log.h"

#define INITIAL_SIZE 32
#define TABLE_MAX_LOAD 0.75

void htable_init(Hashtable *table)
{
    table->length = 0;
    table->capacity = INITIAL_SIZE;

    table->items = calloc(INITIAL_SIZE, sizeof(Entry));
}

void htable_free(Hashtable *table)
{
    free(table->items);
}

static uint32_t htable_hash(char *ptr)
{
    uint32_t hash = 2166136261u;

    for (char *c = ptr; *c != '\0'; c++)
    {
        hash ^= (uint32_t)*c;
        hash *= 16777619;
    }

    return hash;
}

static Entry *htable_find_entry(Hashtable *table, char *key)
{
    uint32_t idx = htable_hash(key) % table->capacity;

    while (true)
    {
        Entry *entry = &table->items[idx];

        if ((entry->key == NULL) || (strcmp(entry->key, key) == 0))
        {
            return entry;
        }

        idx = (idx + 1) % table->capacity;
    }
}

static void htable_grow(Hashtable *table)
{
    trace("(%p) Growing hashtable from %d to %d.", table, table->capacity, table->capacity * 2);

    size_t old_capacity = table->capacity;
    Entry *old_items = table->items;

    table->capacity *= 2;
    table->items = calloc(table->capacity, sizeof(Entry));

    if (table->items == NULL)
    {
        exit(1);
    }

    for (size_t i = 0; i < old_capacity; i++)
    {
        Entry *entry = &old_items[i];

        if (entry->key == NULL)
        {
            continue;
        }

        Entry *dest = htable_find_entry(table, entry->key);

        dest->key = entry->key;
        dest->value = entry->value;
    }

    free(old_items);
}

bool htable_set(Hashtable *table, char *key, char *value)
{
    trace("(%p) Set \"%s\" to \"%s\".", table, key, value);

    if ((table->length + 1) > (table->capacity * TABLE_MAX_LOAD))
    {
        htable_grow(table);
    }

    Entry *entry = htable_find_entry(table, key);
    bool is_new_key = entry->key == NULL;

    if (is_new_key)
    {
        table->length++;
    }

    entry->key = key;
    entry->value = value;

    return is_new_key;
}

char *htable_get(Hashtable *table, char *key)
{
    if (table->length == 0)
    {
        return NULL;
    }

    Entry *entry = htable_find_entry(table, key);

    trace("(%p) Get \"%s\" = \"%s\".", table, key, entry->value);
    return entry->value;
}
