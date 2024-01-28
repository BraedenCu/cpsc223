/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Braeden Cullen
*/

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "life.h"
#include "helpers.h"

/* 
 * Game Loop for Game of Life
 * TODO: Implement neighbors function
 */
//int game_loop(int time_steps, int field[ROWS][COLS]);

int main(int argc, char *argv[])
{
    /*
     * TODO: Accept two command-line arguments, which will appear in the
     * following order:
     * time_steps:
     *      a positive integer describing how many "generations" the simulation
     *      will run for.
     * init:
     *      a string consisting of the characters '0' and '1', of length ROWS * COLS,
     *      representing the initial state for this run of Game of Life.
     */
    int time_steps;
    char *init;
    time_steps = atoi(argv[1]);
    init = argv[2];

    /*
     * TODO: Create a new statically-allocated array of size ROWS x COLS
     */
    int field[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            if (init[i * COLS + j] == '0') 
            {
                field[i][j] = DEAD;
            } 
            else {
                field[i][j] = ALIVE;
            }
        }
    }

    /*
     * TODO: Print the initial values held in the field
     */
    print_initial(field);   

    /*
     * TODO: Run the game time_steps times, printing the field at the end of
     * each step
     * 
     * game loop
     */
    int gen;
    for (int i = 0; i < time_steps; ++i) 
    {
        int next_field[ROWS][COLS];
        gen = i + 1;
        compute_next_gen(field, next_field);
        print_generation(next_field, gen);
        // copy next_field to field
        for (int j = 0; j < ROWS; ++j) 
        {
            for (int k = 0; k < COLS; ++k) 
            {
                field[j][k] = next_field[j][k];
            }
        }
    }

    /*
     * Print "Done." then exit.
     */
    printf("Done.\n");
    return 0;
}


