/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: braeden
 */

#include "pirate_list.h"
#include <string.h>                     // IS THIS ALLOWED, FOR STRCMP ???? CO CO CO CO

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

    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        if (strcmp(pirates->array[i]->name, name) == 0) 
        {
            return i;
        }
    }

    return 0;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.

    // if the list is full, double the capacity
    if (pirates->list_length == pirates->capacity) 
    {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity);
    }

    // shift all elements to the right
    for (size_t i = pirates->list_length; i > idx; i--) 
    {
        pirates->array[i] = pirates->array[i - 1];
    }

    // insert the new pirate
    pirates->array[idx] = p;
    pirates->list_length++;

    return p;
}

pirate *list_remove(pirate_list *pirates, const char *name)
{
    // TODO: Implement this function. FINISH FINISH
    // find the index of the pirate with the given name
    size_t idx = list_index_of(pirates, name);

    // if the pirate is not in the list, return NULL
    if (idx == pirates->list_length) 
    {
        return NULL;
    }

    // remove the pirate from the list
    pirate *removed_pirate = pirates->array[idx];

    for (size_t i = idx; i < pirates->list_length - 1; i++) 
    {
        pirates->array[i] = pirates->array[i + 1];
    }

    pirates->list_length--;


    return removed_pirate;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
    // TODO: Implement this function. Return a pointer to the pirate pointed to by index idx in the list, or NULL
    //  if idx is not a valid index (i.e., it is >= the length of the list).
    // Ownership of the returned pirate remains with the list.

    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        if (i == idx) 
        {
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
void list_sort(pirate_list *pirates) 
{
    if (pirates == NULL || pirates->array == NULL || pirates->list_length <= 1) 
    {
        return;
    }
    quickSort(pirates->array, 0, pirates->list_length - 1);
    //print_all_pirates(pirates);
}

void quickSort(pirate **arr, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}

void swap(pirate **a, pirate **b) 
{
    pirate *t = *a;
    *a = *b;
    *b = t;
}

int partition(pirate **arr, int low, int high) 
{
    pirate *pivot = arr[high]; // rightmost element as pivot
    int i = (low - 1); // index of smaller element

    for (int j = low; j <= high - 1; j++) 
    {
        if (pirate_compare_name(arr[j], pivot) <= 0) // if curr element is <= pivot
        {
            i++; // inc index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
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


void print_all_pirates(pirate_list *pirates) 
{
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        pirate_print(pirates->array[i], stdout);
    }
}