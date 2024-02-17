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
    // TODO: Implement this function. Return a pointer to the pirate pointed to by index idx in the list, or NULL
    //  if idx is not a valid index (i.e., it is >= the length of the list).
    // Ownership of the returned pirate remains with the list.

    for (size_t i = 0; i < pirates->list_length; i++) {
        if (i == idx) {
            return pirates->array[i];
        }
    }

    return NULL;
}

/**
 * Sort the list of pirates in lexicographical order by name.
 *
 * @param pirates the list to sort
 * @does sorts the list of pirates in lexicographical order by name
 * @assumes pirates is not NULL and every pirate in the list has a name that is
 *  unique in the list
 */
void list_sort(pirate_list *pirates) {
    if (pirates == NULL || pirates->list_length <= 1) {
        // No need to sort if the list is NULL or contains 0 or 1 element
        return;
    }

    pirate *temp;
    size_t j;
    // Start from the second element (index 1)
    for (size_t i = 1; i < pirates->list_length; i++) {
        temp = pirates->array[i]; // Take the current element
        j = i - 1;

        // Compare and shift elements to the right to make room for the current element
        while (j < pirates->list_length && pirates->array[j] && temp && strcmp(pirates->array[j]->name, temp->name) > 0) {
            pirates->array[j + 1] = pirates->array[j]; // Shift elements to the right
            if (j == 0) break; // Prevent underflow of size_t j
            j--;
        }
        pirates->array[j + 1] = temp; // Insert the current element into its correct position
    }
    // print the sorted array
    for (size_t i = 0; i < pirates->list_length; i++) {
        printf("OK: %s\n", pirates->array[i]->name);
    }
    
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
