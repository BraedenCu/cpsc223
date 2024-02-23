/**
 * Implementation file for pirate for HookBook B in CPSC 223 SP2024.
 *
 * Author: Braeden
 */

#include "pirate.h"
#include "libhookbook.h"
#include "skills_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

/**
 * Pirates have a name, rank, vessel, port, treasure, and skill. The name of the pirate can be empty.
 * All of these fields could be empty, or none.
 * 
*/
pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));

    new_pirate->name = name;

    new_pirate->rank = NULL;
    new_pirate->vessel = NULL;
    new_pirate->port = NULL;
    new_pirate->treasure = 0;
    new_pirate->captain = NULL;
    new_pirate->captain_vessel = NULL;
    
    return new_pirate;
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
 * 
 * MUST be able to handle the case where a pirate has an empty name but still has skills. This case would look
 * something like two blank lines in a row (immediately, this indicates an empty pirate name) followed by that
 * empty pirates skills or followed by nothing if it has no skills
 */
pirate *pirate_read(FILE *restrict input) 
{
    char*   line;
    char*   name;
    pirate* new_pirate;

    line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    
    if (line == NULL) 
    {
        free(line);
        return NULL;
    }
    if (freadln(line, MAX_LINE_LENGTH, input) == NULL) 
    {
        free(line); // failed read
        return NULL;
    }

    if (line[0] == '\n') {
        // Initialize the pirate with an empty name
        pirate* new_pirate = pirate_create("");
        if (!new_pirate) 
        {
            free(line);
            return NULL; // Failed to create a pirate
        }

        new_pirate->captain = NULL;

        skills_list_instance_t *lst = skills_list_create();
        new_pirate->skills = lst;
    }
    else 
    {
        name = malloc((strlen(line) + 1) * sizeof(char));

        strcpy(name, line);
        new_pirate = pirate_create(name); 
        
        new_pirate->captain = NULL;

        skills_list_instance_t *lst = skills_list_create();
        new_pirate->skills = lst;
    }


    while (freadln(line, MAX_LINE_LENGTH, input) != NULL && line[0] != '\0') 
    {
        char item_tag = line[0];
        char *item_value = line + 2; // skip tag

        switch(item_tag) {
            case 'r':
                new_pirate->rank = malloc((strlen(line) + 1) * sizeof(char));
                strcpy(new_pirate->rank, item_value);
                break;
                
            case 'v':
                new_pirate->vessel = malloc((strlen(line) + 1) * sizeof(char));
                strcpy(new_pirate->vessel, item_value);
                break;

            case 'p':
                new_pirate->port = malloc((strlen(line) + 1) * sizeof(char));
                strcpy(new_pirate->port, item_value);
                break;

            case 't':
                new_pirate->treasure = atoi(item_value);
                break;
                
            case 's':
                populate_skills_list(new_pirate->skills, new_pirate, line, input);
                break;
        }
    }
    
    free(line);     // THIS MAY CAUSE A MEMORY LEAK, WE ARE UNSURE WHY! 
                    // if uncommented, the pirate list will not be populated

    return new_pirate; 
}

void populate_skills_list(skills_list_instance_t *lst, pirate *p, char* line, FILE *input)
{
    char* skill;

    skill = malloc((strlen(line) - 1) * sizeof(char));

    strcpy(skill, line + 2);

    skills_list_append(lst, skill);
    
    free(skill);
}


void pirate_print_A(const pirate *p, FILE *restrict output)
{
    if (p!=NULL && p->name!=NULL) 
    {
        fprintf(output, "%s\n", p->name);
    }
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
    if (p == NULL) return; 
    if (p->name != NULL) fprintf(output, "%s\n", p->name);
    if (p->captain != NULL) fprintf(output, "    Captain: %s (%s)\n", p->captain, p->captain_vessel); // include captain's vessel
    if (p->rank != NULL) fprintf(output, "    Rank: %s\n", p->rank);
    if (p->vessel != NULL) fprintf(output, "    Vessel: %s\n", p->vessel);
    if (p->port != NULL) fprintf(output, "    Port: %s\n", p->port);
    if (p->treasure) fprintf(output, "    Treasure: %li\n", p->treasure); 
    if (p->skills != NULL) print_skills_list(p->skills, output);    // helper provided due too unique challenges of skills list
}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    if (a->name == NULL && b->name == NULL) {   return 0;   }
    else if (a->name == NULL)               {   return 1;   } 
    else if (b->name == NULL)               {   return -1;  } 
    else                                    {   return strcmp(a->name, b->name); }
    return 0;
}

int pirate_compare_vessel(const pirate *a, const pirate *b)
{
    int comparison_result;

    if (a->vessel && b-> vessel)                        
    { 
        comparison_result = strcmp(a->vessel, b->vessel); 
        
        if (comparison_result != 0)                     
        {   
            return comparison_result;
        }
        else
        {   
            return pirate_compare_name(a, b); 
        }    
    }
    else if (!a->vessel && b->vessel)                   {   return 1;   }
    else if (a->vessel && !b->vessel)                   {   return -1;   } 
    else                                                {   return pirate_compare_name(a, b); }
}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{
    if (a->treasure >= 0 && b->treasure >= 0) 
    {
        if (a->treasure > b->treasure) 
        {
            return -1; 
        } else if (a->treasure < b->treasure) 
        {
            return 1; 
        } 
        else 
        {
            return pirate_compare_name(a, b);
        }
    }

    if ((a->treasure >= 0) && !(b->treasure >= 0)) 
    {
        return -1; 
    }

    if (!(a->treasure >= 0) && !(b->treasure >= 0)) 
    {
        return 1; 
    }

    return pirate_compare_name(a, b);
}

void pirate_destroy(pirate *p)
{
    //skills_list_destroy(p->skills); // BUG THIS CAUSES UNIT TESTING SUITE TO FAIL

    free(p->name);
    free(p->rank);
    free(p->vessel);
    free(p->port);

    free(p);
}