# CPSC 223 Lab 1



## Background


In this assignment, you will design and write a C program to simulate a one-dimensional version of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
The basic idea of the Game of Life is that cells in a grid are used to simulate biological cells.
Each cell is either alive or dead.
At each step of the simulation, each cell’s current status and its number of living neighbors are used to determine the status of the cell for the next step of the simulation.  

Typically, the Game of Life is set up as a two-dimensional grid.
In this assignment you will build a one-dimensional version that has $N$ cells numbered $0$ through $N-1$.
Your "grid" will be stored in a **statically-allocated array**.
Each cell $i$ is adjacent to cells $i - 1$ and $i + 1$, with two exceptions: cell $0$ is adjacent only to cell $1$, and cell $N-1$ is adjacent only to cell $N-2$.
A live cell has value $1$ and a dead cell has value $0$.
At each step of the simulation, the cell values at that step determine what changes will occur at the next timestep as follows:

* If a live cell $i$ has two live neighbors, then cell $i$ will die
* If a live cell $i$ does not have two live neighbors, then any dead neighbors of cell $i$ will become alive

> **Note**: for all interior cells, two neighbors need to be examined.
> For the first and last cell, there is only one neighbor to examine, and the rules above still apply (this has the effect that once alive, edge cells can never die).

Consider the state with 10 cells:

```
0111010101
```

* Cell 0 is dead; it stays dead. 
* Cell 1 is alive; it has a dead neighbor in cell 0, so cell 0 becomes alive in the next timestep.
    It does nothing to cell 2 (which is already alive).  
* Cell 2 is alive; it has two alive neighbors, so cell 2 dies in the next timestep.
* Cell 3 is alive; it has a dead neighbor in cell 4, so cell 4 becomes alive.
    (It treats cell 2 as still "alive", since that was the cell’s state when this timestep started, and does not do anything to it!) 
* Cell 4 is dead; it stays dead (again, based on the current timestep!)
* Cell 5 is alive; it has two dead neighbors, so both cell 4 and cell 6 become alive.
* Cell 6 is dead; it stays dead.
* Cell 7 is alive; it has two dead neighbors, so both cell 6 and cell 8 become alive.
* Cell 8 is dead; it stays dead.
* Cell 9 is alive; it has a dead neighbor in cell 8, so cell 8 becomes alive.

So at the next step of the simulation, the state would be:

```
1101111111
```

After another simulation step, then the state would be:

```
1111000001
```

Work through this example by hand to make sure you understand the rules for cell modification.
 
 
## The Assignment 


```C
int main(int argc, char* argv[])
```

The `main` function should accept two command-line arguments, which will appear in the following order:

* `time_steps`: a positive integer describing how many "generations" the simulation will run for.

* `init`: a string consisting of the characters `'0'` and `'1'`, of length `SIZE`, representing the initial state for this run of Game of Life.

Thereafter, your `main` function must create a new **statically-allocated array** of length `SIZE`.
Using this array: 

* Print the initial values held in the array (they must match what was entered as the final command-line argument)
* Run the game `time_steps` times, printing the array at the end of each step (so it looks like the examples in the [sample runs](#sample-runs) below)

### Requirements for `makefile` (or `Makefile`)

`makefile` must have a rule to generate an executable called `Life`, which when executed runs the `main` function implemented in `main.c`.
The name of the target must be "`Life`".


### Sample Runs 


#### Example A:

```
$ ./Life 2 1000000001
Initial Values  [ 1 0 0 0 0 0 0 0 0 1 ]
Step 1          [ 1 1 0 0 0 0 0 0 1 1 ]
Step 2          [ 1 1 1 0 0 0 0 1 1 1 ]
```

#### Example B

```
$ ./Life 5 0000110000
Initial Values  [ 0 0 0 0 1 1 0 0 0 0 ]
Step 1          [ 0 0 0 1 1 1 1 0 0 0 ]
Step 2          [ 0 0 1 1 0 0 1 1 0 0 ]
Step 3          [ 0 1 1 1 1 1 1 1 1 0 ]
Step 4          [ 1 1 0 0 0 0 0 0 1 1 ]
Step 5          [ 1 1 1 0 0 0 0 1 1 1 ]
```

#### Example C

```
$ ./Life 3 0111010101
Initial Values  [ 0 1 1 1 0 1 0 1 0 1 ]
Step 1          [ 1 1 0 1 1 1 1 1 1 1 ]
Step 2          [ 1 1 1 1 0 0 0 0 0 1 ]
Step 3          [ 1 0 0 1 1 0 0 0 1 1 ]
```

#### Example D

```
$ ./Life 10 1010011111
Initial Values  [ 1 0 1 0 0 1 1 1 1 1 ]
Step 1          [ 1 1 1 1 1 1 0 0 0 1 ]
Step 2          [ 1 0 0 0 0 1 1 0 1 1 ]
Step 3          [ 1 1 0 0 1 1 1 1 1 1 ]
Step 4          [ 1 1 1 1 1 0 0 0 0 1 ]
Step 5          [ 1 0 0 0 1 1 0 0 1 1 ]
Step 6          [ 1 1 0 1 1 1 1 1 1 1 ]
Step 7          [ 1 1 1 1 0 0 0 0 0 1 ]
Step 8          [ 1 0 0 1 1 0 0 0 1 1 ]
Step 9          [ 1 1 1 1 1 1 0 1 1 1 ]
Step 10         [ 1 0 0 0 0 1 1 1 0 1 ]
```
