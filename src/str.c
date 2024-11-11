#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "log.h"
#include "hashset.h"

/**
 * A string interning implementation using a hashset.
 *
 * See also: Hashset implementation in `hashset.c`.
 */

static struct Hashset pool;

/**
 * Initialize the interning pool.
 */
void str_init(void)
{
    hashset_init(&pool);
}

/**
 * Frees the pool and all the values.
 */
void str_free(void)
{
    for (unsigned int i = 0; i < pool.length; i++)
    {
        char *entry = pool.items[i];

        if (entry != NULL)
        {
            free(entry);
        }
    }

    hashset_free(&pool);
}

/**
 * Interns a string slice and returns a pointer to it.
 *
 * @param ptr Start of the string.
 * @param length Length of the string.
 */
char *str_intern(char *ptr, unsigned int length)
{
    trace("Interning %.*s", length, ptr);

    char *buf = malloc(length + 1);

    if (buf == NULL)
    {
        exit(1);
    }

    memcpy(buf, ptr, length);
    buf[length] = '\0';

    char *entry = hashset_insert(&pool, buf);

    if (entry != buf)
    {
        free(buf);
    }

    return entry;
}
