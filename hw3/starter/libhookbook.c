/**
 * Implementation file for libhookbook.h
 *
 * For Hookbook A in CPSC 223 SP2024.
 *
 * Author: Braeden 
 */

#include "libhookbook.h"

/**
 * Reads the next line of input from stream, discarding the trailing newline
 *  character if there is one, and stores the line in the array pointed to by
 *  str. If the next line of input is longer than count characters, this reads
 *  and stores the next count characters from stream. In either case, str ends
 *  with '\0'.
 *
 * If stream is at EOF when the function begins, returns NULL and leaves str
 *  unchanged.
 *
 * @param str the array in which to store the characters
 * @param count the maximum number of meaningful characters to store in str
 * @param stream the file from which to read
 * @does read the next line of input from stream, discarding the trailing
 *  newline character if there is one, and store those characters in str.
 * @return str, or NULL if stream is at EOF when the function begins
 * @assumes str points to enough memory to hold count+1 chars
 * @assumes stream is open and readable
 */
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

    // if i == count, then the last character read was not stored in str
    if (c != '\n') 
    {
        ungetc(c, stream); // put back the last character read (if it was not EOF)
    }

    str[i] = '\0';
    
    return str;
}

// self/crossing captains
