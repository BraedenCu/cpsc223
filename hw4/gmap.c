/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 2nd
 * Purpose: implementation of the gmap abstract data structure
 *
 */

#include "gmap.h"

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**

You must implement the gmap ADT according to the specification in gmap.h, which can then be used to store the players' distributions as you read them from standard input for retrieval later when you read the matchups. You may not modify gmap.h at all. The gmap ADT defines a map from generic keys to generic values, with the functions used for hashing, copying, comparing, and freeing the keys passed to the map upon creation.

The gmap functions must run in the following time bounds, where nn is the number of key/value pairs in the map:

gmap_create: O(1)O(1)
gmap_size: O(1)O(1) (worst-case)
gmap_contains_key: expected O(1)O(1), worst-case O(n)O(n)
gmap_get: expected O(1)O(1), worst-case O(n)O(n)
gmap_put: expected O(1)O(1), worst-case O(n)O(n)
gmap_remove: expected O(1)O(1), worst-case O(n)O(n)
gmap_for_each: O(n)O(n) (assuming f runs in O(1)O(1) time)
gmap_keys: O(n)O(n)
gmap_destroy: O(n)O(n)

*/

char *gmap_error = "error";

/**
 * A (key, value) pair stored in a map.
 */
typedef struct
{
    void *key;
    void *value;
} entry;

/**
 * Meta-data for the map.
 *
 * @member table a pointer to the array of entries in the map
 * @member capacity the max number of entries that can be stored in the array
 * @member size the number of entries in the map
 * @member hash the hash function used by the map
 * @member compare the function used to compare keys in the map
 * @member copy the function used to create new copies of keys in the map
 * @member free the function used to destroy keys in the map
 */
struct _gmap
{
    entry *table;
    size_t capacity;
    size_t size;
    size_t (*hash)(const void *);
    int (*compare)(const void *, const void *);
    void *(*copy)(const void *);
    void (*free)(void *);
};

#define GMAP_INITIAL_CAPACITY 100


// copied from gmap_array
gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *))
{
    if (h == NULL || cp == NULL || comp == NULL || f == NULL)
    {
        // one of the required functions was missing
        return NULL;
    }

    gmap *result = malloc(sizeof(gmap));
    if (result != NULL)
    {
        // remember the functions used to manipulate the keys
        result->copy = cp;
        result->compare = comp;
        result->hash = h;
        result->free = f;

        // initialize the table
        result->table = malloc(sizeof(entry) * GMAP_INITIAL_CAPACITY);
        result->capacity = (result->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
        result->size = 0;
    }
    return result;
}

// copied from gmap_array
size_t gmap_size(const gmap *m) 
{
    if (m == NULL)
    {
        return 0;
    }

    return m->size;
}
// TODO
void *gmap_put(gmap *m, const void *key, void *value)
{

}
// TODO
void *gmap_remove(gmap *m, const void *key)
{

}
// TODO
bool gmap_contains_key(const gmap *m, const void *key)
{

}
// TODO
void *gmap_get(gmap *m, const void *key)
{

}
// TODO
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{

}
// TODO
const void **gmap_keys(gmap *m)
{

}
// TODO
void gmap_destroy(gmap *m)
{

}


