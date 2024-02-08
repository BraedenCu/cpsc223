#include "life.h"
#include "helpers.h"
#include <stdio.h>
#include <string.h>

#ifndef SIZE
#define SIZE 10
#endif

int main(int argc, char *argv[])
{
    // argv[0] = the executable name, therefore we must use argv[1]
    // atoi converts anything into an integer, therefore we use it on the argument
    unsigned int time_steps = atoi( argv[1] ); // time_steps: a positive integer describing how many "generations" the simulation will run for.

    if (time_steps == 0)
    {
        fprintf(stderr, "ERROR: time steps must be positive.");
        return 1;
    }
    int field[SIZE];
    // must use char* since it is an array of characters (string), not just one character
    char *field_str = argv[2]; // field_str: a string of 0's and 1's describing the initial state of the field. You dont have to perform any conversion in this case.
    size_t field_size = strlen(field_str); // use field_str here, str_len is from string.h
    if (field_size != SIZE)
    {
        fprintf(stderr, "ERROR: Field must contain exactly %d characters, but has length %zu.\n", SIZE, field_size);
        return 1;
    }
    for (size_t i = 0; i < SIZE; i++)
    {
        if (field_str[i] == '1')
        {
            field[i] = 1; //initialize field
        }
        else if (field_str[i] == '0')
        {
            field[i] = 0;// 5. initialize field
        }
        else
        {
            fprintf(stderr, "ERROR: Field must contain exactly %d 0's and 1's, but found field[%zu] is '%c'.\n", SIZE, i, field_str[i]);
            return 1;
        }
    }

    print_initial(field, SIZE);

    for (int generation = 1; generation <= time_steps; generation++)
    {
        int prev[SIZE];
        for (size_t i = 0; i < SIZE; i++)
        {
            prev[i] = field[i];
        }

        for (size_t i = 0; i < SIZE; i++)
        
        {
            if (/* 6 */) // What would you be checking here using index i?
            {
                if (/* 7 */) //Let's say you have an active cell at index i. What would you be checking here?
                {
                    /* 8: take action */ // What would you be doing here? (Hint: use the functions you wrote in Life.c)
                }
                else
                {
                    if (0 < i && /*9: check neighbor*/)
                    {
                        /* 10: take action */ // What would you be doing here? (Hint: use the functions you wrote in Life.c)
                    }
                    if (/* 11 */ && !isAlive(prev, i + 1, SIZE)) // What would you be checking here using index i? Look at the if statement above for a hint.
                    {
                        /* 12: take action */ // What would you be doing here? (Hint: use the functions you wrote in Life.c)
                    }
                }
            }
        }
        print_generation(field, generation, SIZE);
    }
}
