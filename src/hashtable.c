#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hashtable.h"
#include "log.h"

/**
 * A hashtable implementation that uses the FNV-1a hashing algorithm,
 * with open addressing and linear probing.
 *
 * The API is similar to object-oriented programming; all "methods"
 * for a hashtable take a pointer to a `Hashtable` struct.
 *
 * The implementation is largely taken from Crafting Interpreters [1],
 * minus the ability to delete entries or relying on a string interner.
 *
 * [1] (https://craftinginterpreters.com/hash-tables.html)
 */

#define INITIAL_SIZE 32
#define TABLE_MAX_LOAD 0.75

/**
 * Initialize a hashtable with some initial capacity (defined by `INITIAL_SIZE`).
 *
 * The implementation uses `calloc()` as the table uses NULL'ed `keys` for unused entries.
 *
 * @param table A pointer to the hashtable.
 */
void htable_init(struct Hashtable *table)
{
    table->length = 0;
    table->capacity = INITIAL_SIZE;

    table->items = calloc(INITIAL_SIZE, sizeof(struct Entry));
}

/**
 * Frees the memory used by the hashtable.
 *
 * This does NOT free the strings in use as keys and values.
 */
void htable_free(struct Hashtable *table)
{
    free(table->items);
}

/**
 * FNV-1a hashing functions slightly modified to work on null-terminated strings.
 */
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

/**
 * Common helper function to find where an entry "should be".
 *
 * It returns either an empty slot where the entry should go,
 * or a pointer to the entry if it already exists.
 *
 * `htable_insert()` uses this to create / override a new entry,
 * and `htable_get()` uses this to search for an entry.
 */
static struct Entry *htable_find_entry(struct Hashtable *table, char *key)
{
    uint32_t idx = htable_hash(key) % table->capacity;

    while (true)
    {
        struct Entry *entry = &table->items[idx];

        if ((entry->key == NULL) || (strcmp(entry->key, key) == 0))
        {
            return entry;
        }

        idx = (idx + 1) % table->capacity;
    }
}

/**
 * Grows the table when it hits the max load permitted by `TABLE_MAX_LOAD`.
 *
 * It allocates a new region, and iterates over all valid entries
 * in the old table and copies them to the newly calculated positions.
 */
static void htable_grow(struct Hashtable *table)
{
    trace("(%p) Growing hashtable from %d to %d.", table, table->capacity, table->capacity * 2);

    size_t old_capacity = table->capacity;
    struct Entry *old_items = table->items;

    table->capacity *= 2;
    table->items = calloc(table->capacity, sizeof(struct Entry));

    if (table->items == NULL)
    {
        exit(1);
    }

    for (size_t i = 0; i < old_capacity; i++)
    {
        struct Entry *entry = &old_items[i];

        if (entry->key == NULL)
        {
            continue;
        }

        struct Entry *dest = htable_find_entry(table, entry->key);

        dest->key = entry->key;
        dest->value = entry->value;
    }

    free(old_items);
}

/**
 * Set or update an entry in the table.
 *
 * @param table A pointer to the hashtable.
 * @param key A null-terminated key to set.
 * @param value A null-terminated value.
 *
 * @returns Whether the entry was created (true) or updated (false).
 */
bool htable_insert(struct Hashtable *table, char *key, char *value)
{
    trace("(%p) Set \"%s\" to \"%s\".", table, key, value);

    if ((table->length + 1) > (table->capacity * TABLE_MAX_LOAD))
    {
        htable_grow(table);
    }

    struct Entry *entry = htable_find_entry(table, key);
    bool is_new_key = entry->key == NULL;

    if (is_new_key)
    {
        table->length++;
    }

    entry->key = key;
    entry->value = value;

    return is_new_key;
}

/**
 * Try searching the table for the specified key.
 *
 * @param table A pointer to the hashtable.
 * @param key A null-terminated key to search for.
 *
 * @returns The corresponding value, or `NULL` if no entry was found.
 */
char *htable_get(struct Hashtable *table, char *key)
{
    if (table->length == 0)
    {
        return NULL;
    }

    struct Entry *entry = htable_find_entry(table, key);

    trace("(%p) Get \"%s\" = \"%s\".", table, key, entry->value);
    return entry->value;
}
