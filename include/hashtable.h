#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct
{
    char *key;
    char *value;
} Entry;

typedef struct
{
    Entry *items;

    unsigned int length;
    unsigned int capacity;
} Hashtable;

void htable_init(Hashtable *table);
void htable_free(Hashtable *table);

bool htable_set(Hashtable *table, char *key, char *value);
char *htable_get(Hashtable *table, char *key);

#endif
