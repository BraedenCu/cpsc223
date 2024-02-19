/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: Braeden Cullen
 */

#include "pirate_list.h"
#include <string.h>               // IS THIS ALLOWED, FOR STRCMP ???? CO CO CO CO

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
    return 0;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    /*   
    if (pirates->list_length == pirates->capacity) // if list full, RESIZE_RATIO capacity
    {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity);
    }
    */
    
    list_expand_if_necessary(pirates);

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
    size_t idx = list_index_of(pirates, name);
    if (idx == pirates->list_length) 
    {
        return NULL;
    }

    pirate *removed_pirate = pirates->array[idx];

    for (size_t i = idx; i < pirates->list_length - 1; i++) 
    {
        pirates->array[i] = pirates->array[i + 1];
    }

    pirates->list_length--;

    // check if list should be resized after removal
    list_contract_if_necessary(pirates);

    // free memory of removed_pirate
    pirate_destroy(removed_pirate);

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
    // Implement this function.

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


void print_all_pirates(pirate_list *pirates) {
    if (pirates == NULL || pirates->array == NULL) {
        fprintf(stderr, "No pirates to print.\n");
        return;
    }
    for (size_t i = 0; i < pirates->list_length; i++) {
        if (pirates->array[i] != NULL && pirates->array[i]->name != NULL) {
            printf("%s\n", pirates->array[i]->name);
        }
    }
}


/**
 * Check if the actual number of pirates in the array is "too large"; if it is,
 *  increase the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * Given N actual pirates in the array of capacity C, we say N is "too large"
 *  whenever N >= C
 *
 * If the array capacity was changed, print to stderr the string "Expand to ",
 *  followed by the new capacity of the list and a newline. Here is a possible
 *  print statement:
 *
 *     fprintf(stderr, "Expand to %zu\n", new_capacity);
 *
 * If the capacity was not changed, print nothing.
 *
 * @param pirates the pirate list to expand, if necessary
 * @does increases the capacity of the array if there are too many pirates in
 *  it
 * @assumes the pirate list is in the process of having a pirate added to it.
 */
void list_expand_if_necessary(pirate_list *pirates) 
{
    if (pirates->list_length == pirates->capacity) // if list full, RESIZE_RATIO capacity
    {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity);
        fprintf(stderr, "Expand to %zu\n", pirates->capacity);
    }
    /*
    if (pirates->list_length >= pirates->capacity)  // check if list needs to resize
    {
        pirates->capacity *= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity); // resize list
        fprintf(stderr, "Expand to %zu\n", pirates->capacity *= RESIZE_RATIO);
    }
    */
}

/**
 * Check if the actual number of pirates in the array is "too small"; if it is,
 *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * Given N actual pirates in the array of capacity C, we say N is "too small"
 *  whenever C > INITIAL_CAPACITY and N * RESIZE_FACTOR <= C / RESIZE_FACTOR
 *
 * If the array capacity was changed, print to stderr the string "Contract to "
 *  followed by the new capacity of the list. Here is a possible print
 *  statement:
 *
 *     fprintf(stderr, Contract to %zu\n, new_capacity);
 *
 * If the capacity was not changed, print nothing.
 *
 * The capacity of the array must never fall below INITIAL_CAPACITY!
 *
 * @param pirates the pirate list to contract, if necessary
 * @does decreases the capacity of the array if there are too few pirates in
 *  it.
 * @assumes the pirate list is in the process of having a pirate added to it.
 */
void list_contract_if_necessary(pirate_list *pirates) 
{
    if (pirates->capacity > INITIAL_CAPACITY && pirates->list_length * RESIZE_RATIO <= pirates->capacity / RESIZE_RATIO) // check if list needs to contract
    {
        pirates->capacity /= RESIZE_RATIO;
        pirates->array = realloc(pirates->array, sizeof(pirate *) * pirates->capacity); // contract
    }
}


/**
 * Remove duplicate pirates
 * 
 * @param pirates the list of pirates
 * @does removes duplicate pirates from the list
 * @assumes pirates is not NULL
*/
void remove_duplicate_pirates(pirate_list *pirates) {
    for (size_t i = 0; i < pirates->list_length; i++) {
        for (size_t j = i + 1; j < pirates->list_length; j++) {
            if (pirate_compare_name(pirates->array[i], pirates->array[j]) == 0) {
                list_remove(pirates, pirates->array[j]->name);
                // resize                                                   ASK ABOUT
                list_contract_if_necessary(pirates);
                j--;
            }
        }
    }
}