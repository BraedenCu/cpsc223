/**
 * Name: Braeden Cullen
 * Assignment: HookBook B
 * Class: CPSC223 Spring 2024
 * Date: Feb 26
 * Purpose: implementation for pirate.h, provides a toolkit
 *          for creating and populating pirates.
 */

#include "pirate.h"
#include "libhookbook.h"
#include "skills_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

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
        pirate* new_pirate = pirate_create(""); // empty name

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
    
    free(line);    

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

void pirate_print(const pirate *p, FILE *restrict output)
{
    // sort
    skills_list_sort(p->skills);
    
    if (p == NULL)              return; 
    if (p->name != NULL)        fprintf(output, "%s\n", p->name);
    if (p->captain != NULL)     fprintf(output, "    Captain: %s (%s)\n", p->captain, p->captain_vessel); 
    if (p->rank != NULL)        fprintf(output, "    Rank: %s\n", p->rank);
    if (p->vessel != NULL)      fprintf(output, "    Vessel: %s\n", p->vessel);
    if (p->port != NULL)        fprintf(output, "    Port: %s\n", p->port);
    if (p->treasure)            fprintf(output, "    Treasure: %li\n", p->treasure); 
    if (p->skills != NULL)      print_skills_list(p->skills, output);   
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
    else if (!a->vessel && b->vessel)   {   return 1;   }
    else if (a->vessel && !b->vessel)   {   return -1;   } 
    else                                {   return pirate_compare_name(a, b); }
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
    free(p->name);
    free(p->rank);
    free(p->vessel);
    free(p->port);

    free(p);
}