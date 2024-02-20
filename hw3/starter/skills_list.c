/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Braeden
 */

#include "skills_list.h"

struct skills_list_instance_t
{
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
};

// TODO: Implement all functions declared in skills_list.h

skills_list *skills_list_create(){return;}

skills_list skills_list_append(skills_list *skills, char *skill){return;}

int skills_list_remove_last(skills_list *skills){return;}

void skills_list_destroy(skills_list *skills){return;}

int skills_list_length(skills_list *skills){return;}

char *skills_list_get(skills_list *skills, int index){return;}

int skills_list_index_of(skills_list *skills, char *skill){return;}

