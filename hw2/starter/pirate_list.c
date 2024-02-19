/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: Braeden Cullen
 */

#include "pirate_list.h"
#include <string.h>              

#define INITIAL_CAPACITY 25
#define RESIZE_RATIO 2


struct pirate_list_instance_t
{
    size_t list_length;
    size_t capacity;
    pirate **array; // pointing to a pointer that points to a pirate

    // done 
};


pirate_list *list_create()
{
    pirate_list *temp_list = malloc(sizeof(pirate_list));
    temp_list -> list_length = 0;
    temp_list -> capacity = INITIAL_CAPACITY;
    temp_list -> array = calloc(temp_list->capacity, sizeof(pirate *));

    return temp_list;

    // done
}

size_t list_index_of(const pirate_list *pirates, const char *name)
{
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        if (strcmp(pirates->array[i]->name, name) == 0) 
        {
            return i;
        }
    }
    return pirates->list_length;

    // done
}

int check_duplicate_pirate(const pirate_list *pirates, char *name)
{
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        if (strcmp(pirates->array[i]->name, name) == 0) 
        {
            return 1;
        }
    }
    return 0;

    // done
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    // check if list should be expanded
    list_expand_if_necessary(pirates);
    
    // shift all elements to the right
    for (size_t i = pirates->list_length; i > idx; i--) 
    {
        pirates->array[i] = pirates->array[i - 1];
    }

    pirates->array[idx] = p;

    pirates->list_length++;

    return p;
}

pirate *list_remove(pirate_list *pirates, const char *name)
{
    size_t idx = list_index_of(pirates, name);
    if (idx == pirates->list_length) 
    {
        return NULL;
    }

    pirate *removed_pirate = pirates->array[idx];

    // shift all elements to the left
    for (size_t i = idx; i < pirates->list_length - 1; i++) 
    {
        pirates->array[i] = pirates->array[i + 1];
    }

    pirates->list_length--;

    list_contract_if_necessary(pirates);

    // free memory of removed_pirate
    //pirate_destroy(removed_pirate);

    return removed_pirate;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
    // Oonership of the returned pirate remains with the list.
    if (idx >= pirates->list_length) 
    {
        return NULL;
    }
    return pirates->array[idx];
}

void list_sort(pirate_list *pirates) 
{
    if (pirates == NULL || pirates->array == NULL || pirates->list_length <= 1) 
    {
        return;
    }
    quick_sort(pirates->array, 0, pirates->list_length - 1);
    //print_all_pirates(pirates);
}

void quick_sort(pirate **arr, int low, int high) 
{
    if (low < high) 
    {
        int pi = sort_partition(arr, low, high);
        quick_sort(arr, low, pi - 1);  // Before pi
        quick_sort(arr, pi + 1, high); // After pi
    }
}

void sort_swap(pirate **a, pirate **b) 
{
    pirate *t = *a;
    *a = *b;
    *b = t;
}

int sort_partition(pirate **arr, int low, int high) 
{
    pirate *pivot = arr[high]; // rightmost element as pivot
    int i = (low - 1); // index of smaller element

    for (int j = low; j <= high - 1; j++) 
    {
        if (pirate_compare_name(arr[j], pivot) <= 0) // if curr element is <= pivot
        {
            i++; // inc index of smaller element
            sort_swap(&arr[i], &arr[j]);
        }
    }
    sort_swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

size_t list_length(const pirate_list *pirates)
{
    return pirates->list_length;

    // done
}

void list_destroy(pirate_list *pirates)
{
    // destroy every pirate
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        pirate_destroy(pirates->array[i]);
    }
    // free the array
    free(pirates->array);

    // free the list
    free(pirates);

    // done
}

void print_all_pirates(pirate_list *pirates) 
{
    if (pirates == NULL || pirates->array == NULL) 
    {
        fprintf(stderr, "No pirates to print.\n");
        return;
    }
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        if (pirates->array[i] != NULL && pirates->array[i]->name != NULL) 
        {
            printf("%s\n", pirates->array[i]->name);
        }
    }
}

void list_expand_if_necessary(pirate_list *pirates) 
{
    if (pirates->list_length >= pirates->capacity) // if list full, RESIZE_RATIO capacity
    {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity);
        fprintf(stderr, "Expand to %zu\n", pirates->capacity);
    }
}

void list_contract_if_necessary(pirate_list *pirates) 
{
    if (pirates->capacity > INITIAL_CAPACITY && pirates->list_length * RESIZE_RATIO <= pirates->capacity / RESIZE_RATIO) // check if list needs to contract
    {
        pirates->capacity /= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity); // contract
        fprintf(stderr, "Contract to %zu\n", pirates->capacity);
    }
}
