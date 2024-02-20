/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Braeden
 */

#include "skills_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

skills_list_instance_t* skills_list_create() {
    skills_list_instance_t* lst = malloc(sizeof(skills_list_instance_t));
    if (lst == NULL) {
        return NULL; // Memory allocation failed
    }
    lst->head = NULL;
    lst->tail = NULL;
    lst->length = 0;
    return lst;
}

void skills_list_append(skills_list_instance_t *skills, char *skill) {
    // Create a new node
    skills_list_node *new_node = (skills_list_node *)malloc(sizeof(skills_list_node));
    if (new_node == NULL) {
        // Handle memory allocation failure if necessary
        return;
    }
    
    // Manually duplicate the skill string
    new_node->skill = malloc(strlen(skill) + 1); // +1 for the null terminator
    if (new_node->skill == NULL) {
        // Handle memory allocation failure if necessary
        free(new_node);
        return;
    }
    strcpy(new_node->skill, skill); // Copy the skill into the newly allocated space

    // Initialize the new node to be the last node, so its next should be NULL
    new_node->next = NULL;

    // If the list is empty, this new node becomes both the head and the tail
    if (skills->head == NULL) {
        skills->head = new_node;
        skills->tail = new_node; // Update tail to new node
    } else {
        // If the list is not empty, append the new node to the end and update the tail
        skills->tail->next = new_node; // Append new node at the end
        skills->tail = new_node; // Update tail to new node
    }
    
    // Increment the length of the list
    skills->length++;
}



//int skills_list_remove_last(skills_list_instance_t *skills){return;}

void skills_list_destroy(skills_list_instance_t* skills) {
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

void print_skills_list(skills_list_instance_t *skills, FILE *output) {
    printf("Skills List Information \n");
    if (!skills) return;

    skills_list_node* current = skills->head;
    
    /*
    printf("Skills List Length: %d\n", skills->length);
    printf("Current Node Address: %p\n", current);
    printf("Current Node Skill: %s\n", current->skill);
    */
   
    while (current != NULL) {
        printf("  Skill: %s\n", current->skill);
        current = current->next; // Move to the next node
    }
}

    

//int skills_list_length(skills_list_instance_t *skills){return;}

//char *skills_list_get(skills_list_instance_t *skills, int index){return;}

//int skills_list_index_of(skills_list_instance_t *skills, char *skill){return;}

