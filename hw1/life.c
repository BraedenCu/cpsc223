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
    /*
     * TODO: Implement this function. This line here only so starter code compiles
     * psuedo code:
     * check if i and j are within the bounds of the field
     * if not: return false
     * check if field[i][j] == ALIVE
     * if so: return true
     * else: return false
     * 
     * Reports whether field[i][j] is alive.
     * 
     */
    // ensure that i and j are within the bounds of the field
    if (i < 0 || i >= ROWS || j < 0 || j >= COLS) {
        return false;
    }
    return field[i][j] == ALIVE;
}



int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
     * TODO: Implement this function. This line here only so starter code compiles
     * psuedo code:
     * check if should_live
     * if should_live: return ALIVE
     * else: return DEAD
     * 
     * Reports the state of field[i][j] in the next time step according to the rules of the Game of Life.
     * 
     */
    
    return DEAD;
}

bool should_live(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
     * TODO: Implement this function. This line here only so starter code compiles
     * psuedo code:
     * get num_living_neighbors
     * if field[i][j] is alive:
     *    if num_living_neighbors < 2: return false
     *   if num_living_neighbors > 3: return false
     *  else: return true
     * else:
     *   if num_living_neighbors == 3: return true
     *  else: return false
     */

    int num_neighbors = num_living_neighbors(field, i, j);
    //printf("num neighbors: %d\n", num_neighbors);
    if (is_alive(field, i, j)) { // rule for alive cells
        if (num_neighbors < 2) {
            return false;
        }
        if (num_neighbors > 3) { // rule for dead cells
            return false;
        }
        return true;
    }
    return false;
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    /*
     * TODO: Implement this function. This line here only so starter code compiles
     * psuedo code
     * for each neighbor:
     *    check if neighbor is out of bounds, if so, treat that neighbor as dead
     *    if neighbor is alive: increment num_living_neighbors
     * return num_living_neighbors
     * 
     * Reports the number of alive neighbors of cell field[i][j].
     * 
     */
    unsigned int num_living_neighbors = 0;
    // check top left neighbor
    if (is_alive(field, i - 1, j - 1)) {
        num_living_neighbors++;
    }
    // check top neighbor
    if (is_alive(field, i - 1, j)) {
        num_living_neighbors++;
    }
    // check top right neighbor
    if (is_alive(field, i - 1, j + 1)) {
        num_living_neighbors++;
    }
    // check left neighbor
    if (is_alive(field, i, j - 1)) {
        num_living_neighbors++;
    }
    // check right neighbor
    if (is_alive(field, i, j + 1)) {
        num_living_neighbors++;
    }
    // check bottom left neighbor
    if (is_alive(field, i + 1, j - 1)) {
        num_living_neighbors++;
    }
    // check bottom neighbor
    if (is_alive(field, i + 1, j)) {
        num_living_neighbors++;
    }
    // check bottom right neighbor
    if (is_alive(field, i + 1, j + 1)) {
        num_living_neighbors++;
    }
    return num_living_neighbors;
}

void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS])
{
    /*
     * TODO: Implement this function.
     * psuedo code:
     * for each cell in the field:
     *     get next state
     *     set next state in next_field
     * 
     * Computes the state at the next time step given the state described by cur_field, storing the next state in next_field.
     */

    // get the num_living_neighbors for each cell in the field and print it
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int num_neighbors = num_living_neighbors(cur_field, i, j);
            printf("%d ", num_neighbors);
        }
        printf("\n");
    }

    printf("Done.\n");
}
