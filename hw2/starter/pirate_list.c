/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: braeden
 */

#include "pirate_list.h"

// define initial capacity
#define INITIAL_CAPACITY 10
#define RESIZE_RATIO 2


struct pirate_list_instance_t
{
    // Complete this struct definition
    size_t list_length;
    size_t capacity;
    pirate **array; // pointing to a pointer that points to a pirate, can't just be one star need two

    // done 
};

pirate_list *list_create()
{
    // Implement this function.
    pirate_list *temp_list = malloc(sizeof(pirate_list));
    temp_list -> list_length = 0;
    temp_list -> capacity = INITIAL_CAPACITY;
    temp_list -> array = calloc(temp_list->capacity, sizeof(pirate *));
    return temp_list;

    // done
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

    // if the list is full, double the capacity
    if (pirates->list_length == pirates->capacity) {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity);
    }

    // shift all elements to the right
    for (size_t i = pirates->list_length; i > idx; i--) {
        pirates->array[i] = pirates->array[i - 1];
    }

    // insert the new pirate
    pirates->array[idx] = p;
    pirates->list_length++;

    return p;
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
    // Implement this function.

    return pirates->list_length;

    // done
}

void list_destroy(pirate_list *pirates)
{
    // Implement this function.

    // free the array
    free(pirates->array);

    // free the list
    free(pirates);

    // done
}
