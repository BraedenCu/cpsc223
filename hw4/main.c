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

FILE *entry_parse_args(int argc, char *argv[], int *max_id, int *battlefields);

gmap *populate_gmap(FILE *in, int max_id, int num_bf, void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *));

void print_entry(const void *key, void *value, void *arg);

void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id);

void find_weights(int bf_weights[], int num_bf, int argc, char *argv[]);

void play_single_match(char* id1, char* id2, int *dist1, int *dist2, int *bf_weights, int num_bf);

int main(int argc, char *argv[])
{
/*==================    populate GMAP ==================*/

    int max_id = 32;
    int num_bf = argc - 1;

    FILE *in = entry_parse_args(argc, argv, &max_id, &num_bf);

    gmap *map = populate_gmap(in, max_id, num_bf, duplicate, compare_keys, hash29, free);

    // gmap_for_each(map, print_entry, &num_bf); 

/*==================    STEP TWO, run matches ==================*/

    int bf_weights[num_bf];

    find_weights(bf_weights, num_bf, argc, argv);

    play_matches(map, in, bf_weights, num_bf, max_id);

    return 0;
}

void find_weights(int bf_weights[], int num_bf, int argc, char *argv[]) 
{
    if (argc - 1 < num_bf) 
    { 
        fprintf(stderr, "Error: Expected %d weights, but only %d were provided.\n", num_bf, argc - 1);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_bf; ++i) 
    {
        bf_weights[i] = atoi(argv[i + 1]); 
    }
}

void play_matches(gmap *map, FILE *in, int bf_weights[], int num_bf, int max_id)
{
    char id1[max_id], id2[max_id];

    while (!feof(in) && !ferror(in))
    {
        fscanf(in, "%s %s", id1, id2);

        int *dist1 = (int *)gmap_get(map, id1);
        int *dist2 = (int *)gmap_get(map, id2);

        if (dist1 && dist2)
        {
            play_single_match(id1, id2, dist1, dist2, bf_weights, num_bf);
        }
        else
        {
            printf("One of the players not found in map\n");
        }
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
            exit(EXIT_FAILURE);
        }
    }

    printf("%s %.1f - %s %.1f\n", id1, score1, id2, score2);
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

