/*
Implementations for core functions for Game of Life assignment in CPSC 223 fall 2024

Author: Alan Weide
Modified by: Braeden Cullen
Changelog:
 */

#include "life.h"

#include <stdio.h>

bool is_alive(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
    TODO: Implement this function. This line here only so starter code compiles
    */
    // ensure that i and j are within the bounds of the field
    if (i < 0 || i > ROWS || j < 0 || j > COLS) {
        return false;
    }
    return field[i][j] == ALIVE;
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
    TODO: Implement this function. This line here only so starter code compiles
    */    
    return 0;
}

int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
    TODO: Implement this function. This line here only so starter code compiles
    */
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (is_alive(field, i, j)) {
                if (num_living_neighbors(field, i, j) < 2) {
                    return DEAD;
                } else if (num_living_neighbors(field, i, j) > 3) {
                    return DEAD;
                } else {
                    return ALIVE;
                }
            } else {
                if (num_living_neighbors(field, i, j) == 3) {
                    return ALIVE;
                } else {
                    return DEAD;
                }
            }
        }
    }
    return DEAD;
}

bool should_live(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
    TODO: Implement this function. This line here only so starter code compiles
    */
    return false;
}

void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS])
{
    /*
    TODO: Implement this function.
     */
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS ; ++j) {
            next_field[i][j] = get_next_state(cur_field, i, j);
        }
    }
}
