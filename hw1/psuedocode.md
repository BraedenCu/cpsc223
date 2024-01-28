
# Step by Step Plan

## Main Function

### User Input

- Convert init to a 2d array
- Store data using ALIVE and DEAD types
- print array using print_initial helper function
- store time_steps in a integer

### Game Logic

- Run game time_steps times using a simple loop
  
#### Game Loop

- Loop over each step time_steps times
  - **get_next_state -> calls -> get_next_state**
    - Computes the state at the next time step given the state described by cur_field, storing the next state in next_field.
    - **get_next_state -> calls -> num_living_neighbors**
      - Reports the state of field[i][j] in the next time step according to the rules of the Game of Life.
      -**num_living_neighbors -> calls -> is_alive**
        - Reports the number of alive neighbors of cell field[i][j].
        -**is_alive -> calls -> none**
          - Reports whether field[i][j] is alive.