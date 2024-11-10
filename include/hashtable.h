#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

struct Entry
{
    char *key;
    char *value;
};

struct Hashtable
{
    struct Entry *items;

    unsigned int length;
    unsigned int capacity;
};

void htable_init(struct Hashtable *table);
void htable_free(struct Hashtable *table);

bool htable_set(struct Hashtable *table, char *key, char *value);
char *htable_get(struct Hashtable *table, char *key);

#endif
