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

FILE *entry_parse_args(int argc, char *argv[], int *max_id, int *battlefields);

gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *));

void print_entry(const void *key, void *value, void *arg);

void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id);

void find_weights(gmap* map, FILE* in, int bf_weights[], int num_bf, int argc, char *argv[]);

void play_single_match(gmap* map, FILE* in, char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf);

char* concatenate_ids(const char* id1, const char* id2);

bool is_duplicate_match(gmap* played_matches, const char* id1, const char* id2);

void free_distribution(const void *key, void *value, void *arg);

void blotto_cleanup(gmap *map, FILE *in);