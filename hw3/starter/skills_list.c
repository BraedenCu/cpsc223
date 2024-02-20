/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Braeden
 */

#include "skills_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

skills_list_instance_t* skills_list_create() 
{
    skills_list_instance_t* lst = malloc(sizeof(skills_list_instance_t));
    if (lst == NULL) {
        return NULL;
    }
    lst->head = malloc(sizeof(skills_list_node));
    lst->tail = malloc(sizeof(skills_list_node));

    lst->length = 0;

    lst->head->next = lst->tail;

    lst->head->skill = NULL;
    lst->tail->skill = NULL;

    lst->tail->next = NULL;
    lst->head->next = lst->tail;
    
    return lst;
}

void skills_list_append(skills_list_instance_t *skills, char *skill) 
{
    // Create a new node
    skills_list_node *new_node = malloc(sizeof(skills_list_node));

    //printf("Appending skill: %s\n", skill);
    //printf("    Length: %d\n", skills->length);
    //printf("    Head Node Skill: %s\n", skills->head->skill);
    //printf("    Tail Node Skill: %s\n", skills->tail->skill);

    new_node->skill = malloc(strlen(skill) + 1);

    strcpy(new_node->skill, skill);
    
    new_node->next = NULL;

    if (skills->length == 0) {
        skills->head = new_node;
        skills->tail = new_node;
    }
    else {
        skills->tail->next = new_node;
        skills->tail = new_node;
    }

    skills->length++;
}


//int skills_list_remove_last(skills_list_instance_t *skills){return;}
void skills_list_destroy(skills_list_instance_t* skills) 
{
    if (!skills) return;

    skills_list_node* current = skills->head;
    while (current != NULL) {
        skills_list_node* next = current->next;
        free(current->skill);
        free(current);
        current = next;
    }
    free(skills);
}

void print_skills_list(skills_list_instance_t *skills, FILE *output) 
{
    if (skills->head->skill == NULL) 
    {
        return;
    }

    skills_list_node* current = skills->head;
    
    //printf("    Skills List Length: %d\n", skills->length);
    //printf("    Head Node Skill: %s\n", current->skill);

    while (current != NULL) {
        printf("  Skill: %s\n", current->skill);
        current = current->next; // Move to the next node
    }    
}


//int skills_list_length(skills_list_instance_t *skills){return;}

//char *skills_list_get(skills_list_instance_t *skills, int index){return;}

//int skills_list_index_of(skills_list_instance_t *skills, char *skill){return;}

