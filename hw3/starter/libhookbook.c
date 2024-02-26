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
        c = fgetc(stream); // get next character
    }

    if (c != '\n') 
    {
        ungetc(c, stream); // put back the character 
    }

    str[i] = '\0';
    
    return str;
}
