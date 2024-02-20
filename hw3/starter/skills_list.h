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
typedef struct skills_list_instance_t skills_list;

// TODO: Define and implement an interface for skills_list

/**
 * Allocates enough memory for a skills_list, and sets the list's length to 0.
 * 
 * @return a pointer to a new skills_list with length 0
*/
skills_list *list_create();

/**
 * Appends a skill to the end of the list of skills.
 * 
 * @param skills the list of skills to which to append the skill
 * @param skill the skill to append to the list
*/
skills_list list_append(skills_list *skills, char *skill);

/**
 * Removes the last skill from the list of skills.
 * 
 * @param skills the list of skills from which to remove the last skill
 * @return 0 if the list is empty, 1 if the last skill was removed
*/
int list_remove_last(skills_list *skills);

/**
 * Destroys the list of skills, freeing all memory associated with it.
 * 
 * @param skills the list of skills to destroy
 * @return 0 if the list is empty, 1 if the list was destroyed
*/
void list_destroy(skills_list *skills);

/**
 * Returns the length of the list of skills.
 * 
 * @param skills the list of skills to measure
 * @return the length of the list of skills
*/
int list_length(skills_list *skills);

/**
 * Returns the skill at the given index in the list of skills.
 * 
 * @param skills the list of skills from which to get the skill
 * @param index the index of the skill to get
 * @return the skill at the given index in the list of skills
*/
char *list_get(skills_list *skills, int index);

/**
 * Returns the index of the given skill in the list of skills.
 * 
 * @param skills the list of skills in which to find the skill
 * @param skill the skill to find in the list
 * @return the index of the given skill in the list of skills
*/
int list_index_of(skills_list *skills, char *skill);
