#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "hashset.h"
#include "log.h"

/**
 * A hashset implementation that uses the FNV-1a hashing algorithm,
 * with open addressing and linear probing.
 *
 * The API is similar to object-oriented programming; all "methods"
 * for a hashset take a pointer to a `Hashset` struct.
 *
 * The implementation is largely taken from Crafting Interpreters [1].
 *
 * See also: hashtable implementation in `hashtable.c`.
 *
 * [1] (https://craftinginterpreters.com/hash-tables.html)
 */

#define INITIAL_SIZE 32
#define TABLE_MAX_LOAD 0.75

/**
 * Initialize a hashset with some initial capacity (defined by `INITIAL_SIZE`).
 *
 * The implementation uses `calloc()` as the table uses NULL for unused entries.
 *
 * @param set A pointer to the hashset.
 */
void hashset_init(struct Hashset *set)
{
    set->length = 0;
    set->capacity = INITIAL_SIZE;

    set->items = calloc(INITIAL_SIZE, sizeof(char *));
}

/**
 * Frees the memory used by the hashset.
 *
 * This does NOT free the stored values.
 */
void hashset_free(struct Hashset *set)
{
    free(set->items);
}

/**
 * FNV-1a hashing function.
 */
static uint32_t hashset_hash(char *ptr)
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
 * Helper function to find where an entry "should be".
 *
 * It returns either an empty slot where the entry should go,
 * or a pointer to the entry if it already exists.
 */
static char **hashset_find_entry(struct Hashset *set, char *value)
{
    uint32_t idx = hashset_hash(value) % set->capacity;

    while (true)
    {
        char **entry = &set->items[idx];

        if ((*entry == NULL) || (strcmp(*entry, value) == 0))
        {
            return entry;
        }

        idx = (idx + 1) % set->capacity;
    }
}

/**
 * Grows the set when it hits the max load permitted by `TABLE_MAX_LOAD`.
 *
 * It allocates a new region, and iterates over all valid entries
 * in the old set and copies them to the newly calculated positions.
 */
static void hashset_grow(struct Hashset *set)
{
    trace("(%p) Growing hashset from %d to %d.", set, set->capacity, set->capacity * 2);

    size_t old_capacity = set->capacity;
    char **old_items = set->items;

    set->capacity *= 2;
    set->items = calloc(set->capacity, sizeof(char *));

    if (set->items == NULL)
    {
        panic("Out of memory.");
    }

    for (size_t i = 0; i < old_capacity; i++)
    {
        char **entry = &old_items[i];

        if (*entry == NULL)
        {
            continue;
        }

        char **dest = hashset_find_entry(set, *entry);
        *dest = *entry;
    }

    free(old_items);
}

/**
 * Inserts an entry into the set if it isn't already there.
 *
 * @param set A pointer to the hashset.
 * @param value A null-terminated value.
 *
 * @returns Pointer to the entry.
 */
char *hashset_insert(struct Hashset *set, char *value)
{
    trace("(%p) Inserting \"%s\".", set, value);

    if ((set->length + 1) > (set->capacity * TABLE_MAX_LOAD))
    {
        hashset_grow(set);
    }

    char **entry = hashset_find_entry(set, value);

    if (*entry == NULL)
    {
        trace("Inserting as new entry.");

        *entry = value;
        set->length++;
    }

    return *entry;
}
