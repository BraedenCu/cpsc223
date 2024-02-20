#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 * pointer to the newly-allocated pirate.
 * 
 * @return a pointer to a new pirate with given name
*/
pirate_list* load_pirates_from_file(const char* filepath);

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

    if (argc != 2) 
    {
        fprintf(stderr, "Correct Input Format: %s <pirate_file>\n", argv[0]);
        return 1;
    }

    pirate_list *all_pirates = load_pirates_from_file(argv[1]);

    if (all_pirates == NULL) 
    {
        fprintf(stderr, "Error: Failed to load pirates from file %s\n", argv[1]);
        return 1;
    }
        
    list_sort(all_pirates);

    print_all_pirates(all_pirates);

    list_destroy(all_pirates); 

    return 0;
}

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
