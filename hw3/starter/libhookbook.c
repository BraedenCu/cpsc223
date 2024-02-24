/**
 * Implementation file for libhookbook.h
 *
 * For Hookbook A in CPSC 223 SP2024.
 *
 * Author: Braeden 
 */

#include "libhookbook.h"

char *freadln(char *restrict str, int count, FILE *restrict stream)
{
    size_t i = 0;
    char c = fgetc(stream);

    if (c == EOF || count <= 0 || str == NULL) 
    {
        return NULL;
    }

    while (c != '\n' && c != EOF && i < count) 
    {
        str[i] = c;
        i = i + 1;
        c = fgetc(stream); // need to unget c if i==count case causes loop to exit
    }

    if (c != '\n') 
    {
        ungetc(c, stream); // put back the character (if it was not new line)
    }

    str[i] = '\0';
    
    return str;
}

// self/crossing captains
// pivot needs to be fed into quicksort, remove -1 after first quicksort call pivot
// single pir edge cases no treasure
// no treasure vs treasure edge case
// list sort should only sort the pirates, implement insertion sort as you insert