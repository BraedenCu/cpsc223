/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 5th
 * Purpose: implementation for blotto driver
 *
 */

#include "gmap.h"
#include "entry.h"
#include "string_key.h"
#include "blotto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*================== BLOTTO IMPLEMENTATION ==================*/

void blotto_cleanup(gmap *map, FILE *in) 
{
    if (map != NULL) 
    {
        gmap_for_each(map, free_distribution, NULL);
    }

    gmap_destroy(map);

    if (in != NULL) 
    {
        fclose(in);
    }
}

void free_distribution(const void *key, void *value, void *arg) 
{
    (void)key; // ignore key, avoid warnings

    int *distribution = (int *)value;

    free(distribution);

    (void)arg; // ignore arg, avoid warnings
}

void find_weights(gmap* map, FILE* in, int bf_weights[], int num_bf, int argc, char *argv[])
{
    if (argc - 1 < num_bf) 
    { 
        fprintf(stderr, "Expected %d, but only %d weights were given.\n", num_bf, argc - 1);
        blotto_cleanup(map, in); // cleanup
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

    char id1[max_id];
    char id2[max_id];

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
                play_single_match(map, in, id1, id2, dist1, dist2, bf_weights, num_bf);
            } 
            else 
            {
                fprintf(stderr, "Invalid ID\n");
                blotto_cleanup(map, in); // cleanup
                exit(1); 
            }
        }
    }

    gmap_destroy(played_matches);

    if (matches_played == 0) 
    {
        fprintf(stderr, "No Matches Played\n");
        blotto_cleanup(map, in); // cleanup
        exit(1);
    }
}

void play_single_match(gmap* map, FILE* in, char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf)
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
            fprintf(stderr, "Invalid distribution\n");
            blotto_cleanup(map, in); // cleanup
            exit(1);
        }
    }

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
    // make sure distributions are integers, ensure max_id and num_bf 
    if (argc < 3 || argc > 34)
    {
        fprintf(stderr, "Improper usage, format as follows: %s max_id num_battlefields\n", argv[0]);
        exit(1);
    }

    return stdin;
}

gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *)) 
{
    gmap *map = gmap_create(cp, comp, h, f);

    fseek(in, 0, SEEK_SET); // reset file pointer to start
    
    while (!feof(in) && !ferror(in))
    {
        char peek = fgetc(in);
        if (peek == '\n') break; // stop reading at newline
        ungetc(peek, in);

        entry e = entry_read(in, max_id, num_bf);

        if (e.id == NULL) 
        {
            fprintf(stderr, "Invalid ID\n");
            blotto_cleanup(map, in); // cleanup
            exit(1);
        }

        if (e.distribution == NULL) 
        {
            fprintf(stderr, "Invalid Distribution\n");
            blotto_cleanup(map, in); // cleanup
            exit(1);
        }
        
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

    char* result = malloc(len1 + len2 + 2); // +2 for separator & null-terminator

    if (result) 
    {
        strcpy(result, id1);
        strcat(result, "-"); // dash as separator
        strcat(result, id2);
    }

    return result; 
}

bool is_duplicate_match(gmap* played_matches, const char* id1, const char* id2) 
{
    char* match_id = concatenate_ids(id1, id2); // create match ID

    if (!match_id) 
    {
        fprintf(stderr, "Mem alloc failed for match ID.\n");
        gmap_destroy(played_matches); // cleanup
    }

    bool is_duplicate = gmap_contains_key(played_matches, match_id); // check if match has been played

    if (!is_duplicate) 
    {
        gmap_put(played_matches, match_id, NULL); 
    }

    free(match_id); 

    return is_duplicate; 
}
