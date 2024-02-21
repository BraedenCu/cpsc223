#pragma once

/**
 * Header file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Author: Braeden
 */

/**
 * Type of a list of skills, as an opaque struct.
 */
/**
     * Consider the following possibilities:
     * access a particular skill by name?
     * access a skill at a particular index?
     * remove a skill from the list?
     * handle several skills with the same name?
     * implement a custom type to track additional data about a skill in the list, or will a built-in type suffice?
     * put the skills in a particular order
     * print the list of skills?
     * 
     * You are required to implement the list of skills as a singly-linked list.
    */

#include <stdio.h>


typedef struct skills_list_node {
    char*                       skill; // The data in the node
    struct skills_list_node*    next; // The next node in the list
} skills_list_node;

/**
 * Node within a singly-linked list of skills.
*/
typedef struct skills_list_instance_t {
    skills_list_node*   head;
    skills_list_node*   tail;
    int                 length;
} skills_list_instance_t;

/**
 * Allocates enough memory for a skills_list, and sets the list's length to 0.
 * 
 * @return a pointer to a new skills_list with length 0
*/
skills_list_instance_t *skills_list_create();

/**
 * Appends a skill to the end of the list of skills.
 * 
 * @param skills the list of skills to which to append the skill
 * @param skill the skill to append to the list
*/
void skills_list_append(skills_list_instance_t *skills, char *skill);

/**
 * Removes the last skill from the list of skills.
 * 
 * @param skills the list of skills from which to remove the last skill
 * @return 0 if the list is empty, 1 if the last skill was removed
*/
int skills_list_remove_last(skills_list_instance_t *skills);

/**
 * Destroys the list of skills, freeing all memory associated with it.
 * 
 * @param skills the list of skills to destroy
 * @return 0 if the list is empty, 1 if the list was destroyed
*/
void skills_list_destroy(skills_list_instance_t *skills);

/**
 * Returns the length of the list of skills.
 * 
 * @param skills the list of skills to measure
 * @return the length of the list of skills
*/
int skills_list_length(skills_list_instance_t *skills);

/**
 * Returns the skill at the given index in the list of skills.
 * 
 * @param skills the list of skills from which to get the skill
 * @param index the index of the skill to get
 * @return the skill at the given index in the list of skills
*/
char *skills_list_get(skills_list_instance_t *skills, int index);

/**
 * Returns the index of the given skill in the list of skills.
 * 
 * @param skills the list of skills in which to find the skill
 * @param skill the skill to find in the list
 * @return the index of the given skill in the list of skills
*/
int skills_list_index_of(skills_list_instance_t *skills, char *skill);

/**
 * Print skills list elements
 * 
 * @param skills the list of skills to print
 * @assumes skills is not NULL
*/
void print_skills_list(skills_list_instance_t *skills, FILE* output);

/**
 * Sort the skills list using insertion sort, 
 * There is no required bound on sorting a skills_list!
 * 
 * @param skills the list of skills to sort
 * @assumes skills is not NULL
*/
void skills_list_sort(skills_list_instance_t *skills);