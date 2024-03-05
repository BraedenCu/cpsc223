/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 2nd
 * Purpose: main driver for blotto
 *
 */
#include "gmap.h"
#include "entry.h"
#include "string_key.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*================== BLOTTO INTERFACE ==================*/

FILE *entry_parse_args(int argc, char *argv[], int *max_id, int *battlefields);

gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *));

void print_entry(const void *key, void *value, void *arg);

void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id);

void find_weights(int bf_weights[], int num_bf, int argc, char *argv[]);

void play_single_match(char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf);

char* concatenate_ids(const char* id1, const char* id2);

bool is_duplicate_match(gmap* played_matches, const char* id1, const char* id2);

void blotto_cleanup(gmap *map, FILE *in);

/*================== ENTER DRIVER ==================*/
int main(int argc, char *argv[])
{
/*================== TODO ==================*/

// FAILED -> cases 55, 53, 52, 51, 43, 26, 16

// case 55 -> invalid matchup, produce error
// case 53 -> invalid distribution, produce error
// case 52 -> inconsistent total units, no matches played 

/*================== POPULATE ADT ==================*/

    // Initialization remains unchanged
    int max_id = 32;
    int num_bf = argc - 1;

    FILE *in = entry_parse_args(argc, argv, &max_id, &num_bf);
    
    gmap *map = populate_gmap(in, max_id, num_bf, duplicate, compare_keys, hash29, free);
    
    int bf_weights[num_bf];

    find_weights(bf_weights, num_bf, argc, argv);
    
/*================== RUN MATCHES ==================*/

    play_matches(map, in, bf_weights, num_bf, max_id);

    blotto_cleanup(map, in);

    return 0;
}

/*================== BLOTTO IMPLEMENTATION ==================*/

void blotto_cleanup(gmap *map, FILE *in) 
{
    gmap_destroy(map);
    fclose(in);
}

void find_weights(int bf_weights[], int num_bf, int argc, char *argv[]) 
{
    if (argc - 1 < num_bf) 
    { 
        fprintf(stderr, "Error: Expected %d weights, but only %d were provided.\n", num_bf, argc - 1);
        exit(1);
    }

    for (int i = 0; i < num_bf; ++i) 
    {
        bf_weights[i] = atoi(argv[i + 1]); 
    }
}

void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id) 
{
    gmap* played_matches = gmap_create(duplicate, compare_keys, hash29, free);

    char id1[max_id], id2[max_id];

    int matches_played = 0;

    while (fscanf(in, "%s %s", id1, id2) == 2) 
    {
        matches_played++;
        if (!is_duplicate_match(played_matches, id1, id2)) 
        {
            int *dist1 = (int *)gmap_get(map, id1);
            int *dist2 = (int *)gmap_get(map, id2);

            if (dist1 && dist2)
            {
                play_single_match(id1, id2, dist1, dist2, bf_weights, num_bf);
            } 
            else 
            {
                fprintf(stderr, "Error: Invalid ID Pair\n");
                gmap_destroy(map); // cleanup
                exit(1); // these are all issues with valgrind, stemming from the fact that cleanup is not done before exit(1) is called
            }
        }
    }

    gmap_destroy(played_matches);

    if (matches_played == 0) 
    {
        fprintf(stderr, "Error: No matches played\n");
        gmap_destroy(map); // cleanup
        exit(1);
    }
}


void play_single_match(char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf)
{
    float score1 = 0.0, score2 = 0.0;

    for (int i = 0; i < num_bf; i++)
    {
        if (dist1[i] > dist2[i])
        {
            score1 += bf_weights[i];
        }
        else if (dist1[i] < dist2[i])
        {
            score2 += bf_weights[i];
        }
        else if (dist1[i] == dist2[i])
        {
            score1 += (bf_weights[i] / 2.0);
            score2 += (bf_weights[i] / 2.0);
        }
        else
        {
            fprintf(stderr, "Error: Invalid distribution\n");
            exit(1);
        }
    }

    // print results -> winnerID - score1, loserID - score2
    if (score1 > score2)
    {
        printf("%s %.1f - %s %.1f\n", id1, score1, id2, score2);
    }
    else if (score1 < score2)
    {
        printf("%s %.1f - %s %.1f\n", id2, score2, id1, score1);
    }
    else
    {
        printf("%s %.1f - %s %.1f\n", id1, score1, id2, score2);
    }
}

FILE *entry_parse_args(int argc, char *argv[], int *max_id, int *num_bf)
{
    return stdin;
}

gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *)) 
{
    gmap *map = gmap_create(cp, comp, h, f);

    fseek(in, 0, SEEK_SET); // reset file pointer to start
    
    while (!feof(in) && !ferror(in))
    {
        char peek = fgetc(in);
        if (peek == '\n') break; 
        ungetc(peek, in);

        entry e = entry_read(in, max_id, num_bf);
        
        gmap_put(map, e.id, e.distribution);

        free(e.id); // id ownership retained by entry, therefore free it
    }

    return map;
}

void print_entry(const void *key, void *value, void *arg)
{
    char *id = (char *)key;
    int *distribution = (int *)value;
    int num_bf = *(int *)arg;

    printf("ID: %s, Distribution: ", id);
    for (int i = 0; i < num_bf; i++)
    {
        printf("%d ", distribution[i]);
    }
    printf("\n");
}

char* concatenate_ids(const char* id1, const char* id2) 
{
    size_t len1 = strlen(id1);
    size_t len2 = strlen(id2);

    char* result = malloc(len1 + len2 + 2); // +1 for the separator, +1 for null-terminator

    if (result) 
    {
        strcpy(result, id1);
        strcat(result, "-"); // use a dash as separator
        strcat(result, id2);
    }

    return result; // useful for dupe matches
}

bool is_duplicate_match(gmap* played_matches, const char* id1, const char* id2) 
{
    char* match_id = concatenate_ids(id1, id2); // create match ID

    if (!match_id) 
    {
        fprintf(stderr, "Mem alloc failed for match ID.\n");
        exit(1);
    }

    bool is_duplicate = gmap_contains_key(played_matches, match_id); // check if match has been played

    if (!is_duplicate) 
    {
        gmap_put(played_matches, match_id, NULL); 
    }

    free(match_id); 

    return is_duplicate; 
}