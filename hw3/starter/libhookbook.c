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
char *freadln(char *str, int count, FILE *stream)
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
        c = fgetc(stream);
    }

    str[i] = '\0';
    
    return str;
}


