
# Program Structure

- What the end result should do:
- You get a file with a list of “pirate” names
- Read them into a list
- Sort the list
- Print them out

# Anatomy

- hookbook.c (driver file)
- libhookbook.c (implementation)
- libhookbook.h (interface)
- pirate_list.c (implementation file)
- pirate_list.h (interface file)
- pirate.h (interface file)
- pirate.c (implementation file, yours to create)

## Individual Function

### Pirate List

- what is a pirate list?
  - Struct containing a malloced array and two integers: length and capacity
- Need to add a typedef statement to pirate_list.h
- Need to implement a bunch of functions, will go over each quickly

### Pirate List Create

- Malloc a struct pirate list (the new pirate list)
- Malloc the array for the new pirate list, should contain INITIAL_CAPACITY number of pirate *s.
- Set length to 0, capacity to INITIAL_CAPACITY
- Return the pointer to the new pirate list

### Index Of

- Iterate over the array in a for loop with i going from 0 to length - 1
- If a pirate[i] has the same name as the pirate passed in, return i
- If you make it to the end of the for loop, return length

### Insert

- Call expand if necessary
- for i = length; i > idx; i-- Array[i] = Array[i - 1] // shifting right
- Array[idx] = new element

### Remove

- Call index of (pirate)
- If index != length
  - Store array[index]
  - Shift everything to the right of index to the left one
  - Decrement length
  - Contract if necessary
  - Return the stored pointer
- Return NULL

### Access

- Boundary check the index, return NULL if out of bounds
- Otherwise, return array[i]

### Sort

- Up to you which algorithm to implement, must be O(nlogn) average runtime complexity, O(log n) additional space
- Time requirement: eliminates most algs we’ve learned except mergesort/quicksort
- Space requirement: log additional space – consider recursive stack frames

### Length

- Return the length field of your struct

### Destroy

- Free the array, then free the struct

### Expand if necessary

- Helper function
- If length == capacity
  - Multiply capacity by resize factor
  - Realloc array to new region of size capacity * sizeof(pirate *)
  - Print something I think

### Contract if necessary

- Another helper
- If length * resize factor < capacity / resize factor
  - Capacity = capacity / resize factor
  - Realloc the region same as expand if necessary

## Specific File Implementations

### Pirate.c/Pirate.h

- Define a struct pirate in pirate.c
- Create functions to make/destroy pirates
- Function to read a pirate
  - Read from current position until back-to-back newline loading chars into string
  - Once hit back to back newline create a pirate of given name
- Functions to get, set, print pirate name
  - Should set 
- Function to compare 2 pirates
  - Should return result of string comparing the two pirate names
  - Make sure to check NULL name case!
- Add a typedef statement to pirate.h   

### Makefile

- Hookbook: hookbook.o piratelist.o pirate.o
- hoobook.o: hookbook.c piratelist.h pirate.h
- piratelist.o: piratelist.c piratelist.h pirate.h
- pirate.o: pirate.c pirate.h
  - **Be sure to add** libhookbook and skills_list logic

