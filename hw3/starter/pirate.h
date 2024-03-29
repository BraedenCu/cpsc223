#pragma once

#include <stdio.h>
#include "skills_list.h"

/**
 * Header file for pirate for HookBook B in CPSC 223 SP2024.
 *
 * Author: Alan Weide
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Modified by: Braeden on Feb 20th
 * Changelog: Added skills list implementation under pirate structure definition
 */

/**
 * Type of a pirate, as a (non-opaque) struct
 */
typedef struct pirate_t pirate;
struct pirate_t
{
    char    *name;
    char    *rank;
    char    *vessel;
    char    *port;
    size_t   treasure;
    char    *captain;
    char    *captain_vessel;

    skills_list_instance_t *skills;
};

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 *  pointer to the newly-allocated pirate.
 *
 * @return a pointer to a new pirate with given name
 */
pirate *pirate_create(char *name);

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
pirate *pirate_read(FILE *restrict input);

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
void pirate_print(const pirate *p, FILE *restrict output);

/**
 * Compare the names of two pirates, returning negative number, zero, or a
 * positive number based on the result of a comparison between pirate a 
 * and pirate b. Ascending lexographic order. Pirates with no name come after
 * pirates with a name.
 *
 * @param a the first pirate
 * @param b the second pirate
 * @return a negative number, zero, or a positive number.
 */
int pirate_compare_name(const pirate *a, const pirate *b);

/**
 * A pirate with no vessel always comes after a pirate with a vessel. Two
 *  pirates with no vessels compare identically to pirate_compare_name(a,b)
 * Compare two pirates by their vessels. Return negative number, zero, or positive based on wether the pirate "comes before" "is equal too" or "comes after"
 * 
 * @param a the first pirate
 * @param b the second pirate
 * @return a negative number, zero, or a positive number as a "comes before",
 *  is equal to, or "comes after" b according to their vessels
 * @assumes neither a nor b are NULL
 */
int pirate_compare_vessel(const pirate *a, const pirate *b);

/**
 *  Compare the treasure of two pirates, returning negative number, zero, or a
 * positive number based on the result of a comparison between pirate a 
 * and pirate b. Pirates with no treasure come last, descending order otherwise.
 * 
 * @param a the first pirate
 * @param b the second pirate
 * @return a negative number, zero, or a positive number as a "comes before",
 *  is equal to, or "comes after" b according to their treasures
 * @assumes neither a nor b are NULL
 */
int pirate_compare_treasure(const pirate *a, const pirate *b);

/**
 * Free all memory of the pirate.
 *
 * @param p the pirate to destroy
 * @does frees all memory owned by p
 * @assumes p is not NULL
 */
void pirate_destroy(pirate *p);

/**
 * Generate the skills list.
 * 
 * @param p the pirate to populate the skills list
 * @param skill the skill to add to the skills list
 * @does adds the skill to the skills list of the pirate
*/
void populate_skills_list(skills_list_instance_t *lst, pirate *p, char* line, FILE *input);
