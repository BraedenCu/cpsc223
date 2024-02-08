#pragma once
/*
Interface for helper functions for Game of Life assignment for CPSC 223 Fall 2023.

Author: Alan Weide
*/

#include <stdlib.h>

void print_initial(int field[], size_t size);

void print_generation(int field[], unsigned int gen, size_t size);
