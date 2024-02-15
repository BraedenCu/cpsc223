/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: braeden
 */

#include "pirate_list.h"

// define initial capacity
#define INITIAL_CAPACITY 10

struct pirate_list_instance_t
{
    // TODO: Complete this struct definition
    size_t list_length;
    size_t capacity;
    // you need a pointer to the array so that you know where the pirate is // ALL pirates will be on the heap
    pirate **array; // pointing to a pointer that points to a pirate, can't just be one star need two
};

pirate_list *list_create()
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.

    // CO CO CO CO
    pirate_list *temp_list = malloc(sizeof(pirate_list));
    temp_list -> list_length = 0;
    temp_list -> capacity = INITIAL_CAPACITY;
    temp_list -> array = malloc(sizeof(pirate *) * temp_list->capacity);

    return temp_list;
}

size_t list_index_of(const pirate_list *pirates, const char *name)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return 0;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

pirate *list_remove(pirate_list *pirates, const char *name)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

void list_sort(pirate_list *pirates)
{
    // TODO: Implement this function.
}

size_t list_length(const pirate_list *pirates)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return 0;
}

void list_destroy(pirate_list *pirates)
{
    // TODO: Implement this function.
}
