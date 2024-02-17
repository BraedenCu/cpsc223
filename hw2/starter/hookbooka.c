#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"

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
     * 
    */

    // input checking
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pirate_file>\n", argv[0]);
        return 1;
    }

    // attempt to collect input, if not possible, return error
    FILE *file = fopen(argv[1], "r");   // read in the file

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    // initialize an empty pirate list structure
    pirate_list *all_pirates = list_create();

    // read a pirate profile from the input file
    
    pirate *next_pirate = pirate_read(file);
    /*
    while (next_pirate != NULL) {
        pirate *p = list_insert(all_pirates, next_pirate, list_length(all_pirates));

        // destroy the pirate
        pirate_destroy(next_pirate);
        
        next_pirate = pirate_read(file);
    }
    */
    // code structure according to ozan (next three lines)
    //list_sort(allpirates); 
    
    //list_destroy(allpirates); 
    
    //fclose(infile);









    // now read pirates and assign them one by one to slots

    // now using the initialized list create a pirate list

    // create a pirate_list using create_pirate_list()

    // read from file using pirate_read

    // print all the pirates you have created using pirate_print


    // sort the list using pirate_list_sort(list)

    // print the pirates using pirate_list_print(list)    

    // release resources using pirate_destroy() 

    return 0;
}
