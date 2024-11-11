#ifndef HASHSET_H
#define HASHSET_H

struct Hashset
{
    char **items;

    unsigned int length;
    unsigned int capacity;
};

void hashset_init(struct Hashset *set);
void hashset_free(struct Hashset *set);

char *hashset_insert(struct Hashset *set, char *value);

#endif
