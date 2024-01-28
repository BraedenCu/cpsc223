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
 * Game Loop for Conway's Game of Life 
 */
void game_loop(int time_steps, int field[ROWS][COLS]);

/* 
 * Populate the field with the initial values
 */
void field_population(int field[ROWS][COLS], char* init);

/* 
 * Copy the next field to the current field
 */
void copy_field(int field[ROWS][COLS], int next_field[ROWS][COLS]);

/*
 * Main function
 */ 
int main(int argc, char *argv[])
{
    int     time_steps;
    char    *init;
    int     field[ROWS][COLS];

    time_steps = atoi(argv[1]);
    init = argv[2];

    field_population(field, init);

    print_initial(field);   

    game_loop(time_steps, field);
    
    printf("Done.\n");
    return 0;
}

void game_loop(int time_steps, int field[ROWS][COLS])
{
    int gen;
    int next_field[ROWS][COLS];

    for (int i = 0; i < time_steps; ++i) 
    {
        gen = i + 1;
        compute_next_gen(field, next_field);
        print_generation(next_field, gen);
        copy_field(field, next_field);
    }
}

void field_population(int field[ROWS][COLS], char* init)
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            if (init[i * COLS + j] == '0') 
            {
                field[i][j] = DEAD;
            } 
            else 
            {
                field[i][j] = ALIVE;
            }
        }
    }
}

void copy_field(int field[ROWS][COLS], int next_field[ROWS][COLS])
{
    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            field[i][j] = next_field[i][j];
        }
    }
}
