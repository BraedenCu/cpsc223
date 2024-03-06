/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 5th
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

#define INITIAL_CAPACITY 101 // initial hash table capacity, must be odd number

gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *)) 
{
    gmap *m = malloc(sizeof(gmap));

    if (m == NULL) 
    {
        return NULL;
    }

    m->table = malloc(sizeof(node *) * INITIAL_CAPACITY);

    if (m->table == NULL || m == NULL) 
    {
        free(m);
        return NULL;
    }

    for (size_t i = 0; i < INITIAL_CAPACITY; i++) 
    {
        m->table[i] = NULL;
    }

    m->capacity     = INITIAL_CAPACITY;
    m->size         = 0;
    m->hash         = h;
    m->compare      = comp;
    m->copy         = cp;
    m->free         = f;

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
        return NULL;
    }

    float load_factor = (float)m->size / m->capacity; // get the load factor

    if (load_factor > 0.75) // standard load factor of 0.75
    {
        size_t expanded_capacity = 2 * m->capacity; // double capacity
        
        node **expanded_table = malloc(sizeof(node *) * expanded_capacity);

        if (expanded_table == NULL) 
        {
            return NULL; // mem alloc error
        }

        for (size_t i = 0; i < expanded_capacity; i++) 
        {
            expanded_table[i] = NULL;
        }

        for (size_t i = 0; i < m->capacity; i++) 
        {
            node *curr = m->table[i];
            while (curr != NULL) 
            {
                size_t new_index = m->hash(curr->key) % expanded_capacity; // get the new index
                node *next = curr->next;

                curr->next = expanded_table[new_index]; // prepend, necessary for O(1) 
                expanded_table[new_index] = curr;

                curr = next;
            }
        }

        free(m->table);
        m->table = expanded_table; // update the hashmap
        m->capacity = expanded_capacity;
    }

    size_t idx = m->hash(key) % m->capacity; // get the index
    node *curr = m->table[idx]; // get the current node

    while (curr != NULL) 
    {
        if (m->compare(curr->key, key) == 0) // key already exists
        { 
            void *initial_value = curr->value; 
            curr->value = value;

            return initial_value;
        }
        curr = curr->next; // prepend, necessary for O(1) 
    }

    node *create_link = malloc(sizeof(node));

    if (create_link == NULL) 
    {
        return NULL;
    }

    create_link->key   = m->copy(key);
    create_link->value = value;
    create_link->next  = m->table[idx];
    m->table[idx]   = create_link;

    m->size++;

    return NULL;
}

void *gmap_remove(gmap *m, const void *key) 
{
    size_t idx = m->hash(key) % m->capacity;
    node *curr = m->table[idx];
    node *prev = NULL;

    while (curr != NULL) 
    {
        if (m->compare(curr->key, key) == 0) // key found, remove
        {
            if (prev == NULL) 
            {
                m->table[idx] = curr->next; // one link
            } 
            else 
            {
                prev->next = curr->next;
            }

            void *value = curr->value;
            m->free(curr->key);
            free(curr);
            m->size--;

            return value;
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}


bool gmap_contains_key(const gmap *m, const void *key) 
{
    size_t idx = m->hash(key) % m->capacity; // get the index
    node *curr   = m->table[idx];

    while (curr != NULL) 
    {
        if (m->compare(curr->key, key) == 0) // key found
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void *gmap_get(gmap *m, const void *key) 
{
    size_t idx = m->hash(key) % m->capacity;
    node *curr = m->table[idx];

    while (curr != NULL) 
    {
        if (m->compare(curr->key, key) == 0) 
        {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg) 
{
    for (size_t i = 0; i < m->capacity; i++) 
    {
        for (node *curr = m->table[i]; curr != NULL; curr = curr->next) // iterate over buckets
        {
            f(curr->key, curr->value, arg); // call the function on each node
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
        for (node *curr = m->table[i]; curr != NULL; curr = curr->next) // iterate over buckets
        {
            keys[idx++] = curr->key; // store the key
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
            node *curr = m->table[i];

            while (curr != NULL) 
            {
                node *next = curr->next;

                m->free(curr->key);

                free(curr);

                curr = next;
            }
        }

        free(m->table);

        free(m);
    }
}