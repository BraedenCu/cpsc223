/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 2nd
 * Purpose: implementation of the gmap abstract data structure
 *
 */

/* RULES
* `gmap_create`: $O(1)$
* `gmap_size`: $O(1)$ (worst-case)
* `gmap_contains_key`: expected $O(1)$, worst-case $O(n)$
* `gmap_get`: expected $O(1)$, worst-case $O(n)$
* `gmap_put`: expected $O(1)$, worst-case $O(n)$
* `gmap_remove`: expected $O(1)$, worst-case $O(n)$
* `gmap_for_each`: $O(n)$ (assuming `f` runs in $O(1)$ time)
* `gmap_keys`: $O(n)$
* `gmap_destroy`: $O(n)$
*/

#include "gmap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//gmap error
char *gmap_error = "gmap_error";

// Assuming entry and node structures are defined as previously discussed
typedef struct node {
    void *key;
    void *value;
    struct node *next;
} node;

struct _gmap {
    node **table;
    size_t capacity;
    size_t size;
    size_t (*hash)(const void *);
    int (*compare)(const void *, const void *);
    void *(*copy)(const void *);
    void (*free)(void *);
};

#define INITIAL_CAPACITY 101 // Prime number as initial capacity

/**
 * Creates a new, empty map.
 */
gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *)) {
    gmap *m = malloc(sizeof(gmap));
    if (m == NULL) {
        return NULL;
    }
    m->table = malloc(sizeof(node *) * INITIAL_CAPACITY);
    if (m->table == NULL) {
        free(m);
        return NULL;
    }
    for (size_t i = 0; i < INITIAL_CAPACITY; i++) {
        m->table[i] = NULL;
    }
    m->capacity = INITIAL_CAPACITY;
    m->size = 0;
    m->hash = h;
    m->compare = comp;
    m->copy = cp;
    m->free = f;
    return m;
}

/**
 * Returns the number of (key, value) pairs in the given map.
 */
size_t gmap_size(const gmap *m) {
    return m->size;
}

void *gmap_put(gmap *m, const void *key, void *value) {
    if (m == NULL || key == NULL) {
        return gmap_error;
    }

    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];
    while (current != NULL) {
        if (m->compare(current->key, key) == 0) {
            void *old_value = current->value;
            current->value = value;
            return old_value;
        }
        current = current->next;
    }

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return gmap_error;
    }

    new_node->key = m->copy(key);
    new_node->value = value;
    new_node->next = m->table[index];
    m->table[index] = new_node;
    m->size++;
    return NULL;
}


/**
 * Removes the given key and its associated value from the map.
 */
void *gmap_remove(gmap *m, const void *key) {
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index], *prev = NULL;

    while (current != NULL) {
        if (m->compare(current->key, key) == 0) {
            if (prev == NULL) {
                m->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            void *value = current->value;
            m->free(current->key);
            free(current);
            m->size--;
            return value;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

/**
 * Checks if the given key is present in the map.
 */
bool gmap_contains_key(const gmap *m, const void *key) {
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    while (current != NULL) {
        if (m->compare(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 * Returns the value associated with the given key in the map.
 */
void *gmap_get(gmap *m, const void *key) {
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    while (current != NULL) {
        if (m->compare(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Calls the given function for each (key, value) pair in the map.
 */
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg) {
    for (size_t i = 0; i < m->capacity; i++) {
        for (node *current = m->table[i]; current != NULL; current = current->next) {
            f(current->key, current->value, arg);
        }
    }
}

/**
 * Returns an array of pointers to the keys in the map.
 */
const void **gmap_keys(gmap *m) {
    const void **keys = malloc(sizeof(void *) * m->size);
    if (keys == NULL) {
        return NULL;
    }
    size_t idx = 0;
    for (size_t i = 0; i < m->capacity; i++) {
        for (node *current = m->table[i]; current != NULL; current = current->next) {
            keys[idx++] = current->key;
        }
    }
    return keys;
}


void gmap_destroy(gmap *m) {
    if (m != NULL) {
        // Iterate through each bucket
        for (size_t i = 0; i < m->capacity; i++) {
            node *current = m->table[i];
            while (current != NULL) {
                // Keep a reference to the next node before freeing the current
                node *next = current->next;

                // Free the key using the free function provided at map creation
                m->free(current->key);

                // Free the current node
                free(current);

                // Move to the next node
                current = next;
            }
        }
        // After freeing all nodes, free the table itself
        free(m->table);

        // Finally, free the map structure
        free(m);
    }
}
