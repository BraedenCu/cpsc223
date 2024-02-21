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
pirate_list* load_profiles_from_file(const char* filepath);

/**
 * Check if a pirate with the same name already exists in the list
 * 
 * @param pirates the list of pirates
 * @param name the name of the pirate
*/
char* check_sort_flag(int argc, char *argv[]);


int main(int argc, char *argv[])
{
    /**
     * Your main function must:
     *  1. Take three command-line arguments: the path to a file containing the
     *      pirates' profiles, the path to a file containing pirate/captain
     *      pairs, and the sort order.
     *  2. Open the profiles file and read from it the list of pirate profiles,
     *      appearing as specified in the README, and store them in a
     *      pirate_list*
     *  3. Open the captains file and read from it the list of pirate/captain
     *      pairs, appearing as specified in the README
     * 
     *  4. Sort the list in the order defined by the sort-flag command-line
     *      argument
     *  5. Print the sorted list to stdout, conforming to the format described
     *      in the README
     *  6. Release all resources (files, memory, etc.)
     */

    if (argc != 3 && argc != 4) 
    {
        fprintf(stderr, "You must enter 2 Arguments +/- 1 optional sort flag\n");
        return 1;
    }

    char* sort_flag = check_sort_flag(argc, argv);

    if (sort_flag == NULL) 
    {
        fprintf(stderr, "Error: Invalid sort flag\n");
        return 1;
    }

    pirate_list *all_profiles = load_profiles_from_file(argv[1]);

    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Error: Failed to load pirates from file %s\n", argv[1]);
        return 1;
    }

    populate_captains(all_profiles, argv[2]);

    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Error: Failed to load captains from file %s\n", argv[2]);
        return 1;
    }

    print_all_pirates(all_profiles);

    list_destroy(all_profiles);

    return 0;
}

/**
 * Check if a pirate with the same name already exists in the list
 * 
 * @param pirates the list of pirates
 * @param name the name of the pirate
*/
char* check_sort_flag(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-t") == 0) {
            return argv[i];
        }
    }
    if (argc == 4) {
        return NULL;
    }
    return "-n";
}



/**
 * Load exclusively the pirate profiles from a file
 * 
 * @params filepath: the path to the file containing the pirate profiles
 * @return a pointer to a pirate_list containing all the pirates
*/
pirate_list* load_profiles_from_file(const char* filepath) {
    FILE *file = fopen(filepath, "r");

    if (file == NULL) 
    {
        fprintf(stderr, "Error: Cannot open file %s\n", filepath);
        return NULL;
    }

    pirate_list *all_profiles = list_create();

    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Error: Failed to create a pirate list\n");
        fclose(file);
        return NULL;
    }

    // read first pirate, ensure that it is not an empty line
    pirate *next_profile = pirate_read(file);

    // continue reading until end of file
    while(next_profile != NULL)
    {
        // first check if duplicate pirate exists
        if(check_duplicate_pirate(all_profiles, next_profile->name) == 1)
        {
            pirate_destroy(next_profile);
        }
        else if (list_insert(all_profiles, next_profile, list_length(all_profiles)) == NULL)
        { 
            fprintf(stderr, "Error: Failed to insert a pirate into the list\n");
            pirate_destroy(next_profile);
            list_destroy(all_profiles);
            fclose(file);
            return NULL;
        }
        
        //pirate_print(next_profile, stdout);

        next_profile = pirate_read(file);
    }

    fclose(file);

    return all_profiles;
}

