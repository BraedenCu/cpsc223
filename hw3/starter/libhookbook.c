/**
 * Name: Braeden Cullen
 * Assignment: HookBook B
 * Class: CPSC223 Spring 2024
 * Date: Feb 26
 * Purpose: interface for libhookbook.h, provide a toolkit
 *          for reading in lines from a passed file.
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
