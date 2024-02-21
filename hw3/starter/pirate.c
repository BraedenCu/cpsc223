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

#define MAX_LINE_LENGTH 127

/**
 * Pirates have a name, rank, vessel, port, treasure, and skill. The name of the pirate can be empty.
 * All of these fields could be empty, or none.
 * 
*/
pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));

    new_pirate->name = name;
    
    return new_pirate;
}

pirate *pirate_read(FILE *input) 
{
    int     next_pirate_char;
    char*   line;
    char*   name;
    pirate* new_pirate;

    line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    
    if (line == NULL) 
    {
        return NULL;
    }
    if (freadln(line, MAX_LINE_LENGTH, input) == NULL) 
    {
        free(line); // failed read
        return NULL;
    }
    
    name = malloc((strlen(line) + 1) * sizeof(char));

    strcpy(name, line);
    new_pirate = pirate_create(name); 
    
    new_pirate->captain = NULL;

    skills_list_instance_t *lst = skills_list_create();
    new_pirate->skills = lst;

    while (freadln(line, MAX_LINE_LENGTH, input) != NULL && line[0] != '\0') 
    {
        char item_tag = line[0];
        char *item_value = line + 2; // skip tag

        switch(item_tag) {
            case 'r':
                new_pirate->rank = malloc((strlen(line) -2) * sizeof(char));
                strcpy(new_pirate->rank, item_value);
                break;
            case 'v':
                new_pirate->vessel = malloc((strlen(line) - 2) * sizeof(char));
                strcpy(new_pirate->vessel, item_value);
                break;
            case 'p':
                new_pirate->port = malloc((strlen(line) - 2) * sizeof(char));
                strcpy(new_pirate->port, item_value);
                break;
            case 't':
                new_pirate->treasure = atoi(item_value);
                break;
            case 's':
                populate_skills_list(lst, new_pirate, line, input);
                break;
        }
    }
    
    // free(line);       // THIS MAY CAUSE A MEMORY LEAK, WE ARE UNSURE WHY! 
                         // if uncommented, the pirate list will not be populated
    
    next_pirate_char = fgetc(input);

    if (next_pirate_char != '\n' && next_pirate_char != EOF) 
    {
        ungetc(next_pirate_char, input); // decrements stream indicator position by 1
    }

    return new_pirate; 
}

void populate_skills_list(skills_list_instance_t *lst, pirate *p, char* line, FILE *input)
{
    char* skill;

    skill = malloc((strlen(line) - 1) * sizeof(char));

    strcpy(skill, line + 2);

    skills_list_append(lst, skill);
}


void pirate_print_A(const pirate *p, FILE *restrict output)
{
    if (p!=NULL && p->name!=NULL) 
    {
        fprintf(output, "%s\n", p->name);
    }
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p == NULL) return; 
    if (p->name != NULL) fprintf(output, "%s\n", p->name);
    if (p->captain != NULL) fprintf(output, "    Captain: %s (%s)\n", p->captain, p->captain_vessel);
    if (p->rank != NULL) fprintf(output, "    Rank: %s\n", p->rank);
    if (p->vessel != NULL) fprintf(output, "    Vessel: %s\n", p->vessel);
    if (p->port != NULL) fprintf(output, "    Port: %s\n", p->port);
    if (p->treasure) fprintf(output, "    Treasure: %i\n", p->treasure); 
    if (p->skills != NULL) print_skills_list(p->skills, output);    // unique challenges of skills list
}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    if (a->name == NULL && b->name == NULL) {   return 0;   }
    else if (a->name == NULL)               {   return 1;   } 
    else if (b->name == NULL)               {   return -1;  } 
    else                                    {  return strcmp(a->name, b->name); }
    return 0;
}

int pirate_compare_vessel(const pirate *a, const pirate *b)
{
    if (a->vessel == NULL && b->vessel == NULL) {   return 0;   }
    else if (a->vessel == NULL)                 {   return 1;   } 
    else if (b->vessel == NULL)                 {   return -1;  } 
    else                                        {   return strcmp(a->vessel, b->vessel); }
    return 0;
}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{
    // note: descending order !
    if (a->treasure == b->treasure)     {   return 0;   }
    else if (a->treasure < b->treasure) {   return -1;  } 
    else                                {   return 1;   }
}

void pirate_destroy(pirate *p)
{
    free(p->name);
    free(p->rank);
    free(p->vessel);
    free(p->port);
    //free(p->captain);
    //free(p->captain_vessel);
    skills_list_destroy(p->skills);
    free(p);
}