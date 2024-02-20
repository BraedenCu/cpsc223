#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdlib.h>
#include "skills_list.h"

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 * pointer to the newly-allocated pirate.
 * 
 * @return a pointer to a new pirate with given name
*/
pirate_list* load_pirates_from_file(const char* filepath);
pirate_list* load_profiles_from_file(const char* filepath);
pirate_list* populate_captains(pirate_list *pirates, const char* filepath);

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
     *  4. Sort the list in the order defined by the sort-flag command-line
     *      argument
     *  5. Print the sorted list to stdout, conforming to the format described
     *      in the README
     *  6. Release all resources (files, memory, etc.)
     */

    /**
     * Step One: Dealing with input
     * 
     * 3 CLI arguments, not in order,the name of the profiles file, the name of the captains file, and a flag indicating the method by which to sort the output
     *      The sort method flag may appear anywhere in the command-line arguments, or not appear at all.
     *      The two non-sort-flag arguments are to be interpreted in left-to-right order: the first-appearing one is the list of pirate profiles and the second-appearing one is the list of pirates and their captains.
     * If present, the sort flag argument should be one of "-n", "-v", or "-t"
     *      -n: sort the output in ascending order by the pirates' names
     *      -v: sort the output in ascending order by the pirates' vessels
     *      -t: sort the output in descending order by the pirates' treasures
     *      Default sort: the output should be sorted in ascending order by the pirates' names (as if the -n sort flag was provided). Your sorting algorithm must break ties by sorting tied pirates in ascending order of their names.
    */
    if (argc != 2) 
    {
        fprintf(stderr, "Must Enter Three Arguments");
        return 1;
    }

    // first, lets create the pirate profiles. (assume profiles are the first argument)
    pirate_list *all_profiles = load_profiles_from_file(argv[1]);

    if (all_profiles == NULL) 
    {
        fprintf(stderr, "Error: Failed to load pirates from file %s\n", argv[1]);
        return 1;
    }

    // next, lets create the pirate/captain pairs. (assume pairs are the second argument)
    all_profiles = populate_captains(all_profiles, argv[2]);

    // now, lets determine which sorting algorithm should be used (assume sort flag is the third argument)

    /*
    if (argc != 2) 
    {
        fprintf(stderr, "Must Enter Three Arguments");
        return 1;
    }
    //pirate_list *all_pirates = load_pirates_from_file(argv[1]);
    if (all_pirates == NULL) 
    {
        fprintf(stderr, "Error: Failed to load pirates from file %s\n", argv[1]);
        return 1;
    }
        
    list_sort(all_pirates);

    print_all_pirates(all_pirates);

    list_destroy(all_pirates); 

    */

    return 0;
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
        
        pirate_print(next_profile, stdout);

        next_profile = pirate_read(file);
    }

    fclose(file);

    return all_profiles;
}

/**
 * Create pirate/captain pairs from a file and add them to the pirate_list
 * 
 * @params pirates: the pirate_list to add the pairs to
 * @params filepath: the path to the file containing the pirate/captain pairs
 * @return a pointer to a pirate_list containing all the pirates
 * 
 */
pirate_list* populate_captains(pirate_list *pirates, const char* filepath) {
    return NULL;
}


/**
 * From HookbookA
 * 
*/
pirate_list* load_pirates_from_file(const char* filepath) 
{
    FILE *file = fopen(filepath, "r");
    
    if (file == NULL) 
    {
        fprintf(stderr, "Error: Cannot open file %s\n", filepath);
        return NULL;
    }

    pirate_list *all_pirates = list_create();

    if (all_pirates == NULL) 
    {
        fprintf(stderr, "Error: Failed to create a pirate list\n");
        fclose(file);
        return NULL;
    }

    // read first pirate, ensure that it is not an empty line
    pirate *next_pirate = pirate_read(file); 
    
    if (next_pirate == NULL) 
    {
        fprintf(stderr, "Error: Failed to read a pirate from the file\n");
        list_destroy(all_pirates);
        fclose(file);
        return NULL;
    }

    // continue reading until end of file
    while (next_pirate != NULL) 
    {
        // first check if duplicate pirate exists
        if(check_duplicate_pirate(all_pirates, next_pirate->name) == 1)
        {
            pirate_destroy(next_pirate);
        }
        else if (list_insert(all_pirates, next_pirate, list_length(all_pirates)) == NULL)
        { 
            fprintf(stderr, "Error: Failed to insert a pirate into the list\n");
            pirate_destroy(next_pirate);
            list_destroy(all_pirates);
            fclose(file);
            return NULL;
        }
        //pirate_print(next_pirate, stdout);
        next_pirate = pirate_read(file);
    }

    fclose(file);

    return all_pirates;
}
