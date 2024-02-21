/**
 * Implementation file for pirate_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Braeden
 */

#include "pirate_list.h"
#include "pirate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 25
#define RESIZE_RATIO 2
#define MAX_LINE_LENGTH 127


struct pirate_list_instance_t
{
    size_t      list_length;
    size_t      capacity;
    pirate      **array; // pointing to a pointer that points to a pirate
    compare_fn  compare; // comparison function 
};

/***********************
 * "Private" Functions *
 ***********************/

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
void list_expand_if_necessary(pirate_list *pirates);

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
 * @assumes the pirate list is in the process of having a pirate removed from it.
 */
void list_contract_if_necessary(pirate_list *pirates);

/*******************
 * Function bodies *
 *******************/

pirate_list *list_create()
{
    pirate_list *lst = malloc(sizeof(pirate_list)); 

    lst -> list_length = 0;
    
    lst -> capacity = INITIAL_CAPACITY;
    
    lst -> array = calloc(lst->capacity, sizeof(pirate *)); // list of pirates

    return lst;
}

pirate_list *list_create_with_cmp(compare_fn cmp)
{
    pirate_list *lst = list_create();

    lst -> compare = cmp;

    return lst;
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

}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    list_expand_if_necessary(pirates);
    
    for (size_t i = pirates->list_length; i > idx; i--) // shift to right
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

    for (size_t i = idx; i < pirates->list_length - 1; i++) // shift to left
    {
        pirates->array[i] = pirates->array[i + 1];
    }

    pirates->list_length--;

    list_contract_if_necessary(pirates);

    //pirate_destroy(removed_pirate);

    return removed_pirate;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
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
    // sort the skills list for each pirate
    //for (size_t i = 0; i < pirates->list_length; i++) 
    //{
    //    printf("sorting pirate skills")
    //    skills_list_sort(pirates->array[i]->skills);
    //}
    quick_sort(pirates->array, pirates->compare, 0, pirates->list_length - 1);
}

size_t list_length(const pirate_list *pirates)
{
    return pirates->list_length;
}

void list_destroy(pirate_list *pirates)
{
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        pirate_destroy(pirates->array[i]);
    }
    free(pirates->array);

    free(pirates);

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

void print_all_pirates(pirate_list *pirates) 
{
    if (pirates == NULL || pirates->array == NULL) 
    {
        fprintf(stderr, "No pirates to print.\n");
        return;
    }
    for (size_t i = 0; i < pirates->list_length; i++) 
    {
        pirate_print(pirates->array[i], stdout);
    }
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
}

/**
 * Populate all pirate captains from a file
*/
void populate_captains(pirate_list *pirates, const char* filepath) 
{
    char*       line;
    char*       captain;
    char*       line_next;
    char*       captain_next;
    pirate*     p;
    pirate*     p_captain;
    int idx =   0;
    int idx_captain = 0;

    FILE *file = fopen(filepath, "r");
    
    if (file == NULL) 
    {
        fprintf(stderr, "Error: Cannot open file %s\n", filepath);
        return;
    }

    line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    captain = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    line_next = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    captain_next = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));

    freadln(line_next, MAX_LINE_LENGTH, file);

    while (freadln(line, MAX_LINE_LENGTH, file) != NULL && freadln(line_next, MAX_LINE_LENGTH, file) != NULL)
    {
        strcpy(captain_next, line_next);

        strcpy(captain, line);  

        idx = list_index_of(pirates, captain);
        idx_captain = list_index_of(pirates, captain_next);

        p = (pirate *)list_access(pirates, idx);
        p_captain = (pirate *)list_access(pirates, idx_captain);

        if (p != NULL) 
        {
            p->captain = p_captain->name;
        }
    }

    free(line);
    free(captain);
    free(line_next);
    free(captain_next);
    fclose(file);
}


void quick_sort(pirate **arr, compare_fn comparison_operator, int low, int high) 
{
    if (low < high) 
    {
        int pi = sort_partition(arr, comparison_operator, low, high);
        quick_sort(arr, comparison_operator, low, pi - 1);  // Before pi
        quick_sort(arr, comparison_operator, pi + 1, high); // After pi
    }
}

void sort_swap(pirate **a, pirate **b) 
{
    pirate *t = *a;
    *a = *b;
    *b = t;
}

int sort_partition(pirate **arr, compare_fn comparison_operator, int low, int high) 
{
    pirate *pivot = arr[high]; // rightmost element as pivot
    int i = (low - 1); // index of smaller element

    for (int j = low; j <= high - 1; j++) 
    {
        if (comparison_operator(arr[j], pivot) <= 0) // if curr element is <= pivot
        {
            i++; // inc index of smaller element
            sort_swap(&arr[i], &arr[j]);
        }
    }
    
    sort_swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}
