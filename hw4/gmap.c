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

void gmap_embiggen(gmap *m); // do we need this ???

char *gmap_error = "error";

typedef struct
{
    void *key;
    void *value;
} entry;

typedef struct node {
    entry data;
    struct node *next; // Corrected to explicitly use 'struct node'
} node;

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
    node **table; // array of nodes, each node is a linked list of entry's
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

/**
 * Returns the number of (key, value) pairs in the given map. Behavior
 * is undefined if m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return the size of the map pointed to by m
 */
size_t gmap_size(const gmap *m) 
{
    if (m == NULL)
    {
        return 0;
    }

    return m->size;
}
/**
 * Adds a copy of the given key with value to this map.  If the key is
 * already present then the old value is replaced and returned.  The
 * map copies the key, so the caller retains ownership of the original
 * key and may modify it or destroy it without affecting the map.  The
 * map copies the pointer to the value, but the caller retains
 * ownership of the value. Behavior is undefined if either m or key is
 * NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @param value a pointer to a value
 * @return a pointer to the old value, or NULL, or a pointer to gmap_error
 */
void *gmap_put(gmap *m, const void *key, void *value) 
{
    if (m == NULL || key == NULL) 
    {
        return gmap_error;
    }

    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    // Search for the key in the chain
    while (current != NULL) 
    {
        if (m->compare(current->data.key, key) == 0) 
        {
            // Key found, replace value
            void *old_value = current->data.value;
            current->data.value = value; // Assume value is directly assignable

            return old_value;
        }
        current = current->next;
    }

    // Key not found, insert new node at the beginning of the chain
    node *newNode = malloc(sizeof(node));
    newNode->data.key = m->copy(key);
    newNode->data.value = value;
    newNode->next = m->table[index];
    m->table[index] = newNode;
    m->size++;
    return NULL;
}
    
/**
 * Removes the given key and its associated value from the given map if
 * the key is present.  The return value is NULL and there is no effect
 * on the map if the key is not present.  The copy of the key held by
 * the map is destroyed.  It is the caller's responsibility to free the
 * returned value if necessary. Behavior is undefined if either m or key
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a key, non-NULL
 * @return the value associated with the removed key, or NULL
 */
void *gmap_remove(gmap *m, const void *key) 
{
    if (m == NULL || key == NULL)
    {
        return NULL;
    }

    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];
    node *prev = NULL;

    while (current != NULL) 
    {
        if (m->compare(current->data.key, key) == 0)
        {
            // Key found
            if (prev == NULL) 
            {
                m->table[index] = current->next; // Remove head
            } else {
                prev->next = current->next; // Remove from middle/end
            }
            void *old_value = current->data.value;
            m->free(current->data.key);
            free(current);
            m->size--;
            return old_value;
        }
        prev = current;
        current = current->next;
    }

    return NULL; // Key not found
}


/**
 * Determines if the given key is present in this map. Behavior is undefined
 * if either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return true if a key equal to the one pointed to is present in this map,
 * false otherwise
 */
bool gmap_contains_key(const gmap *m, const void *key) 
{
    if (m == NULL || key == NULL) 
    {
        return false;
    }

    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    while (current != NULL) 
    {
        if (m->compare(current->data.key, key) == 0) 
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

/**
 * Returns the value associated with the given key in this map.
 * If the key is not present in this map then the returned value is
 * NULL.  The pointer returned is the original pointer passed to gmap_put,
 * and it remains the responsibility of whatever called gmap_put to
 * release the value it points to (no ownership transfer results from
 * gmap_get). Behavior is undefined is either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return a pointer to the assocated value, or NULL if they key is not present
 */
void *gmap_get(gmap *m, const void *key) 
{
    if (m == NULL || key == NULL) 
    {
        return NULL;
    }

    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    while (current != NULL) 
    {
        if (m->compare(current->data.key, key) == 0) 
        {
            return current->data.value;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * Calls the given function for each (key, value) pair in this map, passing
 * the extra argument (arg) as well. Behavior is undefined if either m or f
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param f a pointer to a function that takes a key, a value, and an
 * extra piece of information, and does not add or remove keys from the
 * map, non-NULL
 * @param arg a pointer
 */
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg) 
{
    if (m == NULL || f == NULL) 
    {
        return;
    }

    for (size_t i = 0; i < m->capacity; i++) 
    {
        node *current = m->table[i];
        while (current != NULL) 
        {
            f(current->data.key, current->data.value, arg);
            current = current->next;
        }
    }
}


/**
 * Returns an array containing pointers to all of the keys in the
 * given map.  The return value is NULL if there was an error
 * allocating the array.  The map retains ownership of the keys, and
 * the pointers to them are only valid as long until they are removed
 * from the map, or until the map is destroyed, whichever comes first.
 * It is the caller's responsibility to destroy the returned array if
 * it is non-NULL. Behavior is undefined is m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return a pointer to an array of pointers to the keys, or NULL
 */
const void **gmap_keys(gmap *m) 
{
    if (m == NULL) 
    {
        return NULL;
    }

    const void **result = malloc(sizeof(void *) * m->size);
    if (result == NULL) 
    {
        // Handle allocation failure if necessary
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < m->capacity; i++) 
    {
        node *current = m->table[i];
        while (current != NULL) 
        {
            result[j++] = current->data.key;
            current = current->next;
        }
    }

    return result;
}


void gmap_embiggen(gmap *m) 
{
    if (m == NULL) 
    {
        return;
    }

    // Allocate a new table with double the capacity
    size_t new_capacity = m->capacity * 2;
    node **new_table = malloc(sizeof(node *) * new_capacity);
    if (new_table == NULL) 
    {
        // Handle allocation failure if necessary
        return;
    }

    // Initialize the new table
    for (size_t i = 0; i < new_capacity; i++) 
    {
        new_table[i] = NULL;
    }

    // Rehash all entries into the new table
    for (size_t i = 0; i < m->capacity; i++) 
    {
        node *current = m->table[i];
        while (current != NULL) 
        {
            // Calculate new index for each key
            size_t index = m->hash(current->data.key) % new_capacity;

            // Create a new node for the rehashed entry
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL) 
            {
                // Handle allocation failure if necessary
                continue; // Or break, based on your error handling policy
            }
            new_node->data.key = current->data.key; // Assuming ownership transfer
            new_node->data.value = current->data.value; // Assuming ownership transfer
            new_node->next = new_table[index];
            new_table[index] = new_node;

            // Move to the next node
            node *temp = current;
            current = current->next;
            free(temp); // Free the old node after transferring data
        }
    }

    // Replace the old table with the new table
    free(m->table);
    m->table = new_table;
    m->capacity = new_capacity;
}


/**
 * Destroys the given map.  There is no effect if the given pointer is NULL.
 *
 * @param m a pointer to a map, or NULL
 */
void gmap_destroy(gmap *m) 
{
    if (m != NULL) 
    {
        for (size_t i = 0; i < m->capacity; i++) 
        {
            node *current = m->table[i];
            while (current != NULL) 
            {
                node *next = current->next;
                m->free(current->data.key);
                free(current);
                current = next;
            }
        }
        free(m->table);
        free(m);
    }
}