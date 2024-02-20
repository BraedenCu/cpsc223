/**
 * Implementation file for pirate for HookBook B in CPSC 223 SP2024.
 *
 * Author: [your name here]
 */

#include "pirate.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 127

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
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p!=NULL && p->name!=NULL) 
    {
        fprintf(output, "%s\n", p->name);
    }
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
}

int pirate_compare_vessel(const pirate *a, const pirate *b)
{
    // TODO: implement this function
    // This line is here only so starter code compiles.
    return 0;
}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{
    // TODO: implement this function
    // This line is here only so starter code compiles.
    return 0;
}

void pirate_destroy(pirate *p)
{
    // free the pirate's name
    free(p->name);

    // free the pirate
    free(p);
}