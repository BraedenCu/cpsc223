#include "pirate.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implementation file for pirate for HookBook A in CPSC 223 SP2024.
 *
 * Author: Braeden Cullen
 * 
 * What this file needs to do
 * - Define a struct pirate in pirate.c
 * - Create functions to make/destroy pirates
 * - Function to read a pirate
 * - Read from current position until back-to-back newline loading chars into string
 * - Once hit back to back newline create a pirate of given name
 * - Functions to get, set, print pirate name
 * - Should set 
 * - Function to compare 2 pirates
 * - Should return result of string comparing the two pirate names
 * - Make sure to check NULL name case!
 * - Add a typedef statement to pirate.h
 * 
 */


pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));
    
    new_pirate->name = name;

    return new_pirate;

    // done
}


pirate *pirate_read(FILE *input) 
{
    int     next_pirate_char;
    char*   line;
    pirate* new_pirate;

    line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    
    if (line == NULL) 
    {
        return NULL;
    }
    if (freadln(line, MAX_LINE_LENGTH, input) == NULL) 
    {
        free(line); // clean up allocated memory if failed read
        return NULL;
    }
    
    new_pirate = pirate_create(line);
    
    // free(line);       // THIS MAY CAUSE A MEMORY LEAK, WE ARE UNSURE WHY! 
                         // if uncommented, the pirate list will not be populated
    
    // fscanf(input, "\n"); // cannot simply use fscanf, will skip blank pirate names

    next_pirate_char = fgetc(input);

    if (next_pirate_char != '\n' && next_pirate_char != EOF) 
    {
        ungetc(next_pirate_char, input); // decrements the stream indicator position by one
    }

    return new_pirate; 

    // done
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p!=NULL && p->name!=NULL) 
    {
        fprintf(output, "%s\n", p->name);
    }

    // done
}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    if (a->name == NULL && b->name == NULL) {
        return 0;
    }
    else if (a->name == NULL) {
        return 1;
    } 
    else if (b->name == NULL) {
        return -1;
    } 
    else {
        return strcmp(a->name, b->name); // strcmp returns 0 if equal, -1 if a < b, 1 if a > b
    }
    return 0;

    // done
}

void pirate_destroy(pirate *p)
{
    // free the pirate's name
    free(p->name);

    // free the pirate
    free(p);

    // done
}
