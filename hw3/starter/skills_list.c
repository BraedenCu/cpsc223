/**
 * Name: Braeden Cullen
 * Assignment: HookBook B
 * Class: CPSC223 Spring 2024
 * Date: Feb 26
 * Purpose: implementation for skills_list.h, contains 
 *          all of the necessary components for creating
 *          and sorting a pirate's skills.
 */

#include "skills_list.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

skills_list_instance_t* skills_list_create() 
{
    skills_list_instance_t* skills_lst = malloc(sizeof(skills_list_instance_t));

    if (skills_lst == NULL) 
    {
        return NULL;
    }

    skills_lst->head = NULL; 
    skills_lst->tail = NULL; 
    skills_lst->length = 0;

    return skills_lst;
}

// Function to append a new skill to the list
void skills_list_append(skills_list_instance_t *skills, char *skill) 
{
    skills_list_node *new_node = malloc(sizeof(skills_list_node));

    if (new_node == NULL) {
        return; 
    }

    new_node->skill = malloc(strlen(skill) + 1);

    strcpy(new_node->skill, skill);
    new_node->next = NULL;

    if (skills->length == 0) 
    {
        skills->head = new_node;
        skills->tail = new_node;
    } 
    else 
    {
        skills->tail->next = new_node;
        skills->tail = new_node;
    }

    skills->length++;
}

void skills_list_destroy(skills_list_instance_t* skills) 
{
    skills_list_node* curr = skills->head;
    skills_list_node* next = NULL;

    while (curr != NULL) 
    {
        next = curr->next;
        
        free(curr->skill);
        free(curr);

        curr = next;
    }

    free(skills);
}

void print_skills_list(skills_list_instance_t *skills, FILE *output) 
{
    int num_skills_printed = 0;
    int printed;
    int count;
    
    if (!skills || skills->length == 0 || skills->head->skill == NULL) 
    {
        return; // skills list empty
    }

    skills_list_node* current = skills->head;
    
    while (current != NULL && current->skill != NULL) 
    {
        printed = 0;

        skills_list_node* checker = skills->head;

        while (checker != current) 
        {
            if (strcmp(checker->skill, current->skill) == 0) 
            {
                printed = 1; // already printed
                break;
            }
            checker = checker->next; // move to next node
        }

        if (printed == 0) // only print if not already printed
        {
            count = 1; 

            skills_list_node* counter = current->next;

            while (counter != NULL) 
            {
                if (counter->skill && strcmp(current->skill, counter->skill) == 0) 
                {
                    count++;
                }
                counter = counter->next;
            }

            char* skill_asterisks = malloc((count + 1) * sizeof(char));

            for (int i = 0; i < count - 1; i++) 
            {
                skill_asterisks[i] = '*';
            }

            skill_asterisks[count - 1] = '\0';

            skill_asterisks[count] = '\0'; // null terminator for strings

            if (count == 1 && num_skills_printed == 0) 
            {
                fprintf(output, "    Skills: %s\n", current->skill);
            }
            else if (count == 1 && num_skills_printed >= 0) 
            {
                fprintf(output, "            %s\n", current->skill);
            }
            else if(num_skills_printed == 0 && count >= 1) 
            {
                fprintf(output,"    Skills: %s %s\n", current->skill, skill_asterisks);
            }
            else 
            {
                fprintf(output,"            %s %s\n", current->skill, skill_asterisks);
            }
            
            num_skills_printed += 1; 

            free(skill_asterisks);
        }

        current = current->next;
    }
}

int skills_list_length(skills_list_instance_t *skills)
{
    return skills->length;
}

char *skills_list_get(skills_list_instance_t *skills, int index)
{
    if (index < 0 || index >= skills->length) 
    {
        return NULL; // improper input
    }

    skills_list_node* curr = skills->head;

    for (int i = 0; i < index; i++) 
    {
        curr = curr->next;
    }
    
    return curr->skill;
}

int skills_list_index_of(skills_list_instance_t *skills, char *skill)
{
    skills_list_node* curr = skills->head;

    for (int i = 0; i < skills->length; i++) 
    {
        if (strcmp(curr->skill, skill) == 0) 
        {
            return i; // hit proper index
        }

        curr = curr->next;
    }

    return -1; // not found
}

int skills_list_remove_last(skills_list_instance_t *skills)
{
    if (skills->length == 0) 
    {
        return 0;
    }

    else if (skills->length == 1) // only one skill
    {
        free(skills->head->skill);
        free(skills->head);

        skills->head = NULL;
        skills->tail = NULL;
        skills->length = 0;

        return 1;
    }
    else // traverse to find tail
    {
        skills_list_node* curr = skills->head;

        for (int i = 0; i < skills->length - 2; i++) 
        {
            curr = curr->next;
        }

        free(curr->next->skill);
        free(curr->next);

        curr->next = NULL;
        skills->tail = curr;
        skills->length--;

        return 1;
    }
}

void skills_list_sort(skills_list_instance_t *skills) 
{
    if (skills == NULL || skills->length <= 1) 
    {
        return; 
    }

    skills_list_node *sorted = NULL; 
    skills_list_node *curr = skills->head->next; 

    skills->head->next = NULL;
    sorted = skills->head;

    while (curr != NULL) // insertion sort, O(N^2)
    {
        skills_list_node *next = curr->next; 

        if (strcmp(curr->skill, sorted->skill) < 0) // if less than head, continue
        {
            curr->next = sorted;
            sorted = curr;
        } 
        else // if greater than head, traverse to find proper spot
        {
            skills_list_node *search = sorted;

            while (search->next != NULL && strcmp(curr->skill, search->next->skill) > 0) 
            {
                search = search->next; // continue traversing 
            }

            curr->next = search->next; // found proper spot
            search->next = curr;
        }

        curr = next; 
    }

    skills->head = sorted; // update head to sorted head

    skills_list_node *temp = skills->head;

    while (temp != NULL && temp->next != NULL) 
    {
        temp = temp->next; // traverse one again to find tail
    }

    skills->tail = temp; 
}
