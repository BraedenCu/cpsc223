#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include "skills_list.h"

#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 * pointer to the newly-allocated pirate.
 * 
 * @return a pointer to a new pirate with given name
*/
pirate_list* load_profiles_from_file(const char* filepath, compare_fn comparison_function);

/**
 * Check if a sort flag was passed by the user
 * 
 * @param argc the number of arguments
 * @param argv the list of arguments
 * @return the sort flag
*/
char* check_sort_flag(int argc, char *argv[]);

/**
 * Handle Sort Behavior
 * 
 * @param pirates the list of pirates
 * @param sort_flag the sort flag
 * @assumes pirates is not NULL
 * @assumes sort_flag is not NULL
 * @assumes sort_flag is a valid flag
*/
compare_fn handle_sort_behavior(char *sort_flag);

int main(int argc, char *argv[])
{
   
    char* sort_flag = check_sort_flag(argc, argv);

    compare_fn compare = handle_sort_behavior(sort_flag);

    pirate_list *all_profiles = load_profiles_from_file(argv[1], compare);

    populate_captains(all_profiles, argv[2]);

    list_sort(all_profiles);

    print_all_pirates(all_profiles); 

    skills_list_destroy_all(all_profiles);
    
    list_destroy(all_profiles);

    return 0;
}

char* check_sort_flag(int argc, char *argv[]) 
{
    if (argc != 3 && argc != 4) 
    {
        fprintf(stderr, "You must enter 2 Arguments and optionally 1 sort flag\n");
        exit(1);
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-t") == 0) {
            return argv[i];
        }
    }
    if (argc == 4) {
        fprintf(stderr, "Invalid sort flag\n");
        exit(1);
    }
    return "-n";
}

compare_fn handle_sort_behavior(char *sort_flag) 
{
    compare_fn compare;

    if (strcmp(sort_flag, "-n") == 0) 
    {
        compare = pirate_compare_name;
    } 
    else if (strcmp(sort_flag, "-v") == 0) 
    {
        compare = pirate_compare_vessel;
    } 
    else if (strcmp(sort_flag, "-t") == 0) 
    {
        compare = pirate_compare_treasure;
    }
    else 
    {
        compare = pirate_compare_name; // default to name 
    }
    return compare;
}

pirate_list* load_profiles_from_file(const char* filepath, compare_fn compare) 
{
    FILE *file = fopen(filepath, "r");

    if (file == NULL) 
    {
        fprintf(stderr, "Cannot open file %s\n", filepath);
        return NULL;
    }

    pirate_list *all_profiles = list_create_with_cmp(compare);

    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Failed to create a pirate list\n");
        fclose(file);
        return NULL;
    }

    pirate *next_profile = pirate_read(file);

    while (next_profile != NULL)
    {
        if (check_duplicate_pirate(all_profiles, next_profile->name) == 1)
        {
            pirate_destroy(next_profile);
        }
        else 
        {
            list_insert(all_profiles, next_profile, list_length(all_profiles));
        }

        //pirate_print(next_profile, stdout);           // crucial debug checkpoint

        next_profile = pirate_read(file);
    }

    fclose(file);
    
    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Failed to load pirates from file\n");
        exit(1);
    }

    return all_profiles;
}

