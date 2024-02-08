/*
Implementation file for core functions for Game of Life assignment for CPSC 223 Fall 2023.

Author: Alan Weide
*/

#include "life.h"

#include <stdio.h>

#define ALIVE 1
#define DEAD 0

bool isAlive(int field[], size_t i, size_t size)
{
    // return true if field[i] is alive, false otherwise
}

bool shouldDie(int field[], size_t i, size_t size)
{
    // return true if field[i] should die, false otherwise
    // don't forget to check edge cases! what are those?
}

void activate_cell(int field[], size_t i, size_t size)
{
    // activate field[i] (set it to ALIVE)
}

void kill_cell(int field[], size_t i, size_t size)
{
    // kill field[i] (set it to DEAD)
}
