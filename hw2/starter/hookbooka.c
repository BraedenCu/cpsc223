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
     *   1. Take as the only command-line argument the path to a file
     *      containing the pirates' names to be placed into your Hookbook.
     *   2. Open that file and read from it the list of pirate names, formatted
     *      as specified in the README, and store them in a pirate_list*
     *   3. Sort the list in lexicographic order by pirate name
     *   4. Print the sorted list to stdout, conforming to the format described
     *      in the README
     *   5. Release all resources (files, memory, etc.)
     */

    /**
     * - Anatomy
     *  - hookbook.c (driver file
     *  - libhookbook.c (implementation)
     *  - pirate.c (implementation file, yours to create)
     *  - pirate_list.c (implementation file)
     *  - libhookbook.h (interface)
     *  - pirate_list.h (interface file)
     *  - pirate.h (interface file)
     * 
    */

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pirate_file>\n", argv[0]);
        return 1;
    }

    pirate_list *all_pirates = load_pirates_from_file(argv[1]);
    
    if (all_pirates == NULL) {
        fprintf(stderr, "Error: Failed to load pirates from file %s\n", argv[1]);
        return 1;
    }

    
    // assuming list_sort and pirate_list_print are implemented functions
    list_sort(all_pirates);

    // release resources
    list_destroy(all_pirates); 

    return 0;
}


pirate_list* load_pirates_from_file(const char* filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filepath);
        return NULL;
    }

    pirate_list *all_pirates = list_create();
    if (all_pirates == NULL) {
        fprintf(stderr, "Error: Failed to create a pirate list\n");
        fclose(file);
        return NULL;
    }

    pirate *next_pirate = pirate_read(file);
    if (next_pirate == NULL) {
        fprintf(stderr, "Error: Failed to read a pirate from the file\n");
        list_destroy(all_pirates);
        fclose(file);
        return NULL;
    }
    
    while (next_pirate != NULL) 
    {
        if (list_insert(all_pirates, next_pirate, list_length(all_pirates)) == NULL)
        { 
            fprintf(stderr, "Error: Failed to insert a pirate into the list\n");
            pirate_destroy(next_pirate);
            list_destroy(all_pirates);
            fclose(file);
            return NULL;
        }
        next_pirate = pirate_read(file);
    }

    // release resources
    fclose(file);

    return all_pirates;
}