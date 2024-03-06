/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 2nd
 * Purpose: interface for blotto driver
 *
 */

#include "gmap.h"
#include "entry.h"
#include "string_key.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*================== BLOTTO INTERFACE ==================*/

/**
 * Parse cli arguments, return stdin file pointer if inputs are properly formatted
 * 
 * @param argc int number of cli arguments
 * @param argv char pointer to cli arguments
 * @param max_id int pointer to max_id
 * @param num_bf int pointer to num_bf
 * @returns FILE pointer to stdin
*/
FILE *entry_parse_args(int argc, char *argv[], int *max_id, int *battlefields);

/**
 * Populate gmap with input file data
 * 
 * @param in file pointer to input file
 * @param max_id int max_id
 * @param num_bf int num_bf
 * @param cp void pointer to cp, copy function
 * @param comp void pointer to comp, compare function
 * @param h void pointer to h, hash function
 * @param f void pointer to f, free function
 * @returns gmap pointer
*/
gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *));

/**
 * print a single entry
 * 
 * @param key void pointer to key
 * @param value void pointer to value
 * @param arg void pointer to arg
 * @returns void
*/
void print_entry(const void *key, void *value, void *arg);

/**
 * Play all matches, print their results
 * 
 * @param map gmap pointer
 * @param in file pointer to input file
 * @param bf_weights int array of weights
 * @param num_bf int number of battlefields
 * @param max_id int max id
 * @returns void
*/
void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id);

/**
 * Parse cli arguments to find the distribution weights for all of the matches
 * 
 * @param map gmap pointer
 * @param in file pointer to input file
 * @param bf_weights int array of weights
 * @param num_bf int number of battlefields
 * @param argc int number of cli arguments
 * @param argv char pointer to cli arguments
 * @returns void
*/
void find_weights(gmap* map, FILE* in, int bf_weights[], int num_bf, int argc, char *argv[]);


/**
 * play a single match and print the result
 * 
 * @param map gmap pointer
 * @param in file pointer to input file
 * @param id1 char pointer to id1
 * @param id2 char pointer to id2
 * @param dist1 int pointer to dist1
 * @param dist2 int pointer to dist2
 * @param bf_weights int array of weights
 * @param num_bf int number of battlefields
 * @returns void
*/
void play_single_match(gmap* map, FILE* in, char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf);

/**
 * Concatenate two ids with a dash separator
 * 
 * @param id1 char pointer to id1
 * @param id2 char pointer to id2
 * @returns char pointer to concatenated ids
 * @returns NULL if memory allocation fails
*/
char* concatenate_ids(const char* id1, const char* id2);

/**
 * Check if a match has been played
 * 
 * @param played_matches gmap pointer to played_matches
 * @param id1 char pointer to id1
 * @param id2 char pointer to id2
 * @returns bool
*/
bool is_duplicate_match(gmap* played_matches, const char* id1, const char* id2);

/**
 * Free all distribution values
 * 
 * @param key void pointer to key
 * @param value void pointer to value
 * @param arg void pointer to arg
 * @returns void
*/
void free_distribution(const void *key, void *value, void *arg);

/**
 * Parse cli arguments and return file pointer to input file
 * 
 * @param map gmap pointer
 * @param in file pointer to input file
 * @returns void
*/
void blotto_cleanup(gmap *map, FILE *in);