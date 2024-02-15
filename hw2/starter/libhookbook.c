/**
 * Implementation file for libhookbook.h
 *
 * For Hookbook A in CPSC 223 SP2024.
 *
 * Author: braeden
 */

#include "libhookbook.h"

char *freadln(char *str, int count, FILE *stream)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    size_t i = 0;
    char c = fgetc(stream);

    if (c == EOF) {
        return NULL;
    }
    
    while (c != '\n' && c != EOF && i <= count) {
        str[i] = c;
        i = i + 1;

        // string MUST end with null terminators
        if ( i == count) {
            str[i] = '\0';
            return str;
        }
        
        c = fgetc(stream);
    }

    return NULL;
}
