#pragma once

/**
 * Header file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: Alan Weide
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Modified by: Braeden Cullen on Feb 18th
 * Changelog: Added a new function, print_all_pirates, to the pirate_list.h file
 * 
 * Modified by: Braeden Cullen on Feb 19th
 * Changelog: Added quick_sort function and helpers for quick_sort to pirate_list.h
 * 
 * Modified by: Braeden Cullen on Feb 19th
 * Changelog: Added remove_duplicate_pirates function to pirate_list.h
 * 
 * Modified by: Braeden Cullen on Feb 19th
 * Changelog: Removed remove_duplicate_pirates, added check_duplicate_pirate to pirate_list.h
 */

#include <stdlib.h>

#include "pirate.h"

/**
 * Type of a list of pirates, as an opaque struct.
 */
typedef struct pirate_list_instance_t pirate_list;

/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 *
 * @return a pointer to a newly-created pirate list
 */
pirate_list *list_create();

/**
 * Return the index in pirates of the pirate with the name, or a value greater
 *  than or equal to the length of the list if the there is no such pirate.
 *
 * @param pirates the list to search
 * @param name the name to search for
 * @return the index of the pirate with name, or a value greater than or equal
 *  to the length of the list if the there is no such pirate.
 * @assumes neither pirates nor p are NULL
 */
size_t list_index_of(const pirate_list *pirates, const char *name);

/**
 * Only if there is no pirate in the list with the same name as p, insert
 *  pirate p into the list at index idx by copying the pointer, shifting the
 *  latter part of the list one "slot" to the right.
 *
 * If idx >= [length of pirates], then this function appends p to the end of
 *  the list.
 *
 * If there is a pirate in the list with the same name as p, do nothing, and
 *  return p (the pirate that was not inserted).
 *
 * If the pirate was inserted into the list, return NULL.
 *
 * If p is added to the list, the list claims ownership of the pirate pointed
 *  to by p; otherwise ownership remains with p.
 *
 * @param pirates the list in which to insert p
 * @param p the pirate to insert
 * @param idx the index at which to insert p
 * @return NULL or p, depending on whether p was successfully inserted
 * @assumes neither pirates nor p are NULL, and that p has a name
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

/**
 * Remove the pirate from the list with name, and return a pointer to it.
 *
 * If name is NULL or there is no pirate in the list with name, return NULL.
 *
 * If this function does not return NULL, then the caller owns the returned
 *  pirate.
 *
 * @param pirates the list from which to remove a pirate
 * @param name the name of the pirate to remove
 * @return the removed pirate, or NULL if there is no matching pirate in the
 *  list
 * @assumes pirates is not NULL
 * @assumes every pirate in pirates has a name that is unique in the list
 */
pirate *list_remove(pirate_list *pirates, const char *name);

/**
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL
 *  if idx is not a valid index (i.e., it is >= the length of the list).
 *
 * Ownership of the returned pirate remains with the list.
 *
 * @param pirates the list to access
 * @param idx the index to access of the list
 * @return a pointer to the pirate at index idx of pirates, or NULL
 * @assumes pirates is not NULL
 */
const pirate *list_access(const pirate_list *pirates, size_t idx);

/**
 * Sort the list of pirates in lexicographical order by name.
 *
 * @param pirates the list to sort
 * @does sorts the list of pirates in lexicographical order by name
 * @assumes pirates is not NULL and every pirate in the list has a name that is
 *  unique in the list
 */
void list_sort(pirate_list *pirates);

/**
 * Sort the list of pirates in lexicographical order by name using quick sort.
 * 
 * @param pirates the list to sort
 * @param low the lowest index of the list
 * @param high the highest index of the list
 * @does sorts the list of pirates in lexicographical order by name using quick sort
 * @assumes pirates is not NULL and every pirate in the list has a name that is
 * unique in the list
 *
*/
void quick_sort(pirate **arr, int low, int high); 

/**
 * Helper function sort_swap for quick_sort function
 * 
 * @param a the first pirate to swap
 * @param b the second pirate to swap
 * @does swaps the pirates at index low and high
 * @assumes pirates is not NULL and low and high are valid indexes
 * 
*/
void sort_swap(pirate **a, pirate **b); 

/**
 * Helper function partition for quick_sort function
 * 
 * @param pirates the list to sort
 * @param low the lowest index of the list
 * @param high the highest index of the list
 * @does partitions the list of pirates in lexicographical order by name using quick sort
 * @assumes pirates is not NULL and low and high are valid indexes
*/
int sort_partition(pirate **arr, int low, int high);

/**
 * Return the number of pirates in the list.
 *
 * @param pirates the list
 * @return the number of pirates in pirates
 * @assumes pirates is not NULL
 */
size_t list_length(const pirate_list *pirates);

/**
 * Free all memory owned by the list, including the pirates in the list.
 *
 * @param pirates the list to destroy
 */
void list_destroy(pirate_list *pirates);

/**
 * Print all pirates in the list
 * 
 * @param pirates the list to print
*/
void print_all_pirates(pirate_list *pirates);

/**
 * Check for duplicate pirates
 * 
 * @param pirates the list of pirates
 * @param name the name of the pirate
 * @return 1 if the pirate is a duplicate, 0 if the pirate is not a duplicate
 * @assumes pirates is not NULL
*/
int check_duplicate_pirate(const pirate_list *pirates, char *name);

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
 * @assumes the pirate list is in the process of having a pirate added to it.
 */
void list_contract_if_necessary(pirate_list *pirates);