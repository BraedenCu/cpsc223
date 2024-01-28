/*
Implementations for core functions for Game of Life assignment in CPSC 223 fall 2024

Author: Alan Weide
Modified by: Braeden Cullen
Changelog:
*/

#include "life.h"
#include <stdio.h>
#include "helpers.h"


bool is_alive(int field[ROWS][COLS], size_t i, size_t j)
{
    return field[i][j] == ALIVE;
}

int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned int num_neighbors = num_living_neighbors(field, i, j);

    if (is_alive(field, i, j)) // rules for alive cells
    { 
        if (num_neighbors < 2 || num_neighbors > 3) 
        {
            return DEAD;
        }
        return ALIVE;
    }
    else 
    { 
        if (num_neighbors == 3) // rule for dead cells
        {
            return ALIVE;
        }
        return DEAD; // base case
    }
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned int    num_living_neighbors = 0;
    int             row_adjusted;
    int             col_adjusted;

    for (int row_i = -1; row_i <= 1; row_i++) 
    {
        for (int col_j = -1; col_j <= 1; col_j++) 
        {
            if (!(row_i == 0 && col_j == 0)) // skip field[i][j] itself
            {
                row_adjusted = i + row_i;
                col_adjusted = j + col_j;

                if ((col_adjusted >= 0 && col_adjusted < COLS) && (row_adjusted >= 0 && row_adjusted < ROWS)) // check bounds before checking if alive
                {
                    if (is_alive(field, row_adjusted, col_adjusted)) {
                        num_living_neighbors++;
                    }
                }
            }
        }
    }

    return num_living_neighbors;
}

void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) 
        {
            next_field[i][j] = get_next_state(cur_field, i, j);
        }
    }
}