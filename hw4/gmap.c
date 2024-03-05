/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 2nd
 * Purpose: implementation of the gmap abstract data structure
 *
 */
#include "gmap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// structure for individual node within the map
typedef struct node {
    void *key;             // node key
    void *value;           // node value
    struct node *next;     // pointer to next node
} node;

// structure for generic map
struct _gmap {
    node **table;                 // pointer to array of node pointers
    size_t capacity;              // capacity of table
    size_t size;                  // size of table table
    size_t (*hash)(const void *); // pointer to hash function

    int (*compare)(const void *, const void *);    // pointer to comparison function
    void *(*copy)(const void *);                   // pointer to copy function
    void (*free)(void *);                          // pointer to free function
};

char *gmap_error = "gmap ERROR"; // error message for gmap operations

#define INITIAL_CAPACITY 101 // initial hash table capacity

gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *)) 
{
    gmap *m = malloc(sizeof(gmap));

    if (m == NULL) 
    {
        return gmap_error;
    }

    m->table = malloc(sizeof(node *) * INITIAL_CAPACITY);

    if (m->table == NULL) 
    {
        free(m);
        return gmap_error;
    }

    for (size_t i = 0; i < INITIAL_CAPACITY; i++) 
    {
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

size_t gmap_size(const gmap *m) 
{
    return m->size;
}

void *gmap_put(gmap *m, const void *key, void *value) 
{
    if (m == NULL || key == NULL)
     {
        return gmap_error;
    }

    float load_factor = (float)m->size / m->capacity; // get the load factor

    if (load_factor > 0.75) // standard load factor of 0.75
    {
        size_t new_capacity = 2 * m->capacity; // double capacity
        node **new_table = malloc(sizeof(node *) * new_capacity);

        if (new_table == NULL) 
        {
            return gmap_error; // mem alloc error
        }

        for (size_t i = 0; i < new_capacity; i++) 
        {
            new_table[i] = NULL;
        }

        for (size_t i = 0; i < m->capacity; i++) 
        {
            node *current = m->table[i];
            while (current != NULL) 
            {
                size_t new_index = m->hash(current->key) % new_capacity; // get the new index
                node *next = current->next;

                current->next = new_table[new_index]; // prepend, necessary for O(1) retrieval
                new_table[new_index] = current;

                current = next;
            }
        }

        free(m->table);
        m->table = new_table;
        m->capacity = new_capacity;
    }

    size_t index = m->hash(key) % m->capacity; // get the index
    node *current = m->table[index]; // get the current node

    while (current != NULL) 
    {
        if (m->compare(current->key, key) == 0) // key already exists
        { 
            void *old_value = current->value;
            current->value = value;

            return old_value;
        }
        current = current->next;
    }

    node *new_node = malloc(sizeof(node));

    if (new_node == NULL) 
    {
        return gmap_error;
    }

    new_node->key = m->copy(key);
    new_node->value = value;
    new_node->next = m->table[index];

    m->table[index] = new_node;
    m->size++;

    return NULL;
}

void *gmap_remove(gmap *m, const void *key) 
{
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index], *prev = NULL;

    while (current != NULL) 
    {
        if (m->compare(current->key, key) == 0) // key found
        {
            if (prev == NULL) 
            {
                m->table[index] = current->next;
            } 
            else 
            {
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


bool gmap_contains_key(const gmap *m, const void *key) 
{
    size_t index = m->hash(key) % m->capacity; // get the index
    node *current = m->table[index];

    while (current != NULL) 
    {
        if (m->compare(current->key, key) == 0) // key found
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void *gmap_get(gmap *m, const void *key) 
{
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index];

    while (current != NULL) 
    {
        if (m->compare(current->key, key) == 0) 
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg) 
{
    for (size_t i = 0; i < m->capacity; i++) 
    {
        for (node *current = m->table[i]; current != NULL; current = current->next) 
        {
            f(current->key, current->value, arg); // call the function on each node
        }
    }
}

const void **gmap_keys(gmap *m) 
{
    const void **keys = malloc(sizeof(void *) * m->size);

    if (keys == NULL) 
    {
        return NULL;
    }

    size_t idx = 0;

    for (size_t i = 0; i < m->capacity; i++) 
    {
        for (node *current = m->table[i]; current != NULL; current = current->next) 
        {
            keys[idx++] = current->key; // store the key
        }
    }
    return keys;
}

void gmap_destroy(gmap *m) 
{
    if (m != NULL) 
    {
        for (size_t i = 0; i < m->capacity; i++) // iterate over buckets
        {
            node *current = m->table[i];

            while (current != NULL) 
            {
                node *next = current->next;

                m->free(current->key);

                free(current);

                current = next;
            }
        }

        free(m->table);

        free(m);
    }
}