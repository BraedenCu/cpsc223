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
 * 
 * 
 * 
 */

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 *  pointer to the newly-allocated pirate.
 *
 * @return a pointer to a new pirate with given name
 */
pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));
    new_pirate->name = name;
    return new_pirate;

    // done
}


/**
 * Reads a pirate profile from input. Assumes that the input cursor is at the
 *  beginning of a pirate profile (otherwise, the behavior is undefined).
 *
 * Returns a pointer to a pirate created from the profile in input.
 *
 * This function consumes the blank line after the end of the current profile
 *  before returning (that is, the first newline character and the second, if
 *  there is one, or the EOF marker if not), meaning that after this function
 *  is done, the input cursor is either at the end of the input file or at the
 *  beginning of the next pirate profile.
 *
 * @param input the stream from which to read a pirate profile
 * @returns a new pirate based on the contents of input
 * @assumes input is an open and readable stream
 * @assumes the next character in input is the first character of a pirate's
 *  profile, and that input is well-formed according to the input specification
 *  in the README.
 */
pirate *pirate_read(FILE *input) 
{
    char *line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    if (line == NULL) 
    {
        return NULL;
    }
    if (freadln(line, MAX_LINE_LENGTH, input) == NULL) 
    {
        free(line); // clean up allocated memory if failed read
        return NULL;
    }

    pirate *new_pirate = pirate_create(line);
    
    // free(line);       // THIS MAY CAUSE A MEMORY LEAK, WE ARE UNSURE WHY! 
                         // if uncommented, the pirate list will not be populated
    
    fscanf(input, "\n"); // skip blank lines

    return new_pirate;

    // done
}

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 *
 * @param p the pirate to print
 * @param output the stream to which the pirate's profile should be printed
 * @does prints p's profile to output
 * @assumes p is not NULL
 * @assumes output is an open, writable stream
 */
void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p!=NULL && p->name!=NULL) 
    {
        fprintf(output, "%s\n", p->name);
    }

    // done
}

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 * For this function, we say a "comes before" b if the name of pirate a is
 *  lexicographically less than the name of pirate b, and that they are equal
 *  if they have the same name.
 *
 * A pirate with no name always comes after a pirate with a name. No order is
 *  defined between two pirates with no name.
 *
 * @param a the first pirate
 * @param b the second pirate
 * @return a negative number, zero, or a positive number as a "comes before",
 *  is equal to, or "comes after" b according to their names
 * @assumes neither a nor b are NULL
 */
int pirate_compare_name(const pirate *a, const pirate *b)
{
    if (a->name == NULL) {
        return 1;
    } 
    else if (b->name == NULL) {
        return -1;
    } 
    else if (a->name == NULL && b->name == NULL) {
        return 0;
    } 
    else {
        return strcmp(a->name, b->name); // strcmp returns 0 if equal, -1 if a < b, 1 if a > b
    }
    return 0;

    // done
}

/**
 * Frees all memory owned by p. This function claims ownership of p.
 *
 * @param p the pirate to destroy
 * @does frees all memory owned by p
 * @assumes p is not NULL
 */
void pirate_destroy(pirate *p)
{
    // free the pirate's name
    free(p->name);

    // free the pirate
    free(p);

    // done
}
