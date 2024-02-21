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
    int num_skills_printed = 0;

    if (!skills || skills->length == 0 || skills->head->skill == NULL) 
    {
        return; // skills list empty
    }

    skills_list_node* current = skills->head;
    
    while (current != NULL && current->skill != NULL) 
    {
        int printed = 0;

        skills_list_node* checker = skills->head;
        while (checker != current) 
        {
            if (strcmp(checker->skill, current->skill) == 0) 
            {
                printed = 1;
                break;
            }
            checker = checker->next;
        }

        if (printed == 0) 
        {
            int count = 1; 
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

            for (int i = 0; i + 1 < count; i++) 
            {
                skill_asterisks[i] = '*';
            }

            skill_asterisks[count] = '\0'; // Null terminator
            
            if (count == 1 && num_skills_printed == 0) {
                fprintf(output, "    Skills: %s\n", current->skill);
            }
            else if (count == 1 && num_skills_printed >= 0) {
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
            num_skills_printed +=1;

            free(skill_asterisks);
        }

        current = current->next;
    }
}


// 5 BELOW CO CO CO
int skills_list_length(skills_list_instance_t *skills)
{
    return skills->length;
}

char *skills_list_get(skills_list_instance_t *skills, int index)
{
    if (index < 0 || index >= skills->length) 
    {
        return NULL;
    }

    skills_list_node* current = skills->head;
    for (int i = 0; i < index; i++) 
    {
        current = current->next;
    }
    return current->skill;
}

int skills_list_index_of(skills_list_instance_t *skills, char *skill)
{
    skills_list_node* current = skills->head;
    for (int i = 0; i < skills->length; i++) 
    {
        if (strcmp(current->skill, skill) == 0) 
        {
            return i;
        }
        current = current->next;
    }
    return -1;
}

int skills_list_remove_last(skills_list_instance_t *skills)
{
    if (skills->length == 0) 
    {
        return 0;
    }
    else if (skills->length == 1) 
    {
        free(skills->head->skill);
        free(skills->head);
        skills->head = NULL;
        skills->tail = NULL;
        skills->length = 0;
        return 1;
    }
    else 
    {
        skills_list_node* current = skills->head;
        for (int i = 0; i < skills->length - 2; i++) 
        {
            current = current->next;
        }
        free(current->next->skill);
        free(current->next);
        current->next = NULL;
        skills->tail = current;
        skills->length--;
        return 1;
    }
}

void skills_list_sort(skills_list_instance_t *skills) {
    if (!skills || !skills->head || !skills->head->next) {
        return; // List is empty or has one element
    }
    
    quick_sort_linked_list(skills->head, skills->tail);
}

void quick_sort_linked_list(skills_list_node* head, skills_list_node* tail) {
    if (head == tail || head == NULL || tail == NULL) {
        return;
    }

    // Partition the list and get new pivot
    skills_list_node* pivot = partition_linked_list(head, tail);

    // Sort the sublists recursively
    if (pivot != NULL && pivot->next != NULL) {
        quick_sort_linked_list(head, pivot);
        quick_sort_linked_list(pivot->next, tail);
    }
}

skills_list_node* partition_linked_list(skills_list_node* head, skills_list_node* tail) {
    char* pivotValue = tail->skill;
    skills_list_node* smallerLast = NULL;
    skills_list_node* current = head;
    while (current != tail) {
        if (strcmp(current->skill, pivotValue) < 0) {
            // This should move current node to the "smaller" part
            // Since we're working with a linked list, this might involve node swapping or data swapping
            // For simplicity, you can swap skills between nodes rather than rearranging nodes
        }
        current = current->next;
    }

    // Now, move the pivot to its correct position and return its node
    // This might involve swapping the pivot with the first element of the "greater" part

    skills_list_node *pivotNode = tail;

    return pivotNode; // This should be the node of the pivot after partition
}