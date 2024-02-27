# Pointers

## pointers primer

- a pointer can point to an array in memory
- recall: an array is a contiguous chunk of memory, indexable from zero
- never declare variables of type void*
- remember: you are smarter than the compiler. you must be fully aware of the types of the variables you are dealing with at all times
- but how much memory should I be allocating?
  - use sizeof()

## passing by value vs reference

- passing a variable into a function copies the value of that variable
  - for pointers creates an alias
- returning a variable from a function copies the value of that variable
  - for pointers creates an alias

## dereference (*) and address of operators (&)

- two kinds of expressions: lvalue and rvalue
  - lvalue can be used on the left or right hand side of an assignment statement
  - rvalue can only be used on the right hand side of an assignment statement

## memory layout summary

- text: code, constant data
- data: initialized global & static variables
- BSS: uninitialized global and static variables
- Heap: dynamic memory
- Stack: local variables

## freeing memory

- what happens if all memory is in use? crash.
- how to solve? **free(variable)**
- always keep track of **ownership**
  - variable claims ownership over newly-allocated memory
  - parameter passing might transfer ownership
    - note in function documentation !
  - returning from a function might transfer owernship
    - note in function documentation !
  - assignment introduces shared ownership
- when the last owner goes out of scope, memory **must be freed**
  - prefer a single owner for every slot in memory -> prevent freeing memory still in use
- summary
  - variables are values are stored on the **stack**
    - for pointer variables, the **address** points to
  - use **malloc** and **calloc** to allocate memory for a pointer variable
    - how much? depends on use
    - returns a **void'*'** which is a "pointer to something" 
  - assigning between pointers creates an alias
    - also parameter passing, function return
  - memory is a resource, must **release** it when done using the **free** function
    - always track memory ownership

## the problem with static types

- the length of a static array is immutable
- the length of a static array must be constant
- possible solution to handling data of an unknown length
  - memory allocation is a constant-time operation
  - array access is a constant-time operation
  - copying n items takes O(n) time
  - we gather n pieces of data
  - the steps
    - allocate a nominally sized array into memory, to store the first, say, k0 pieces of data
    - gather data keeping track of how "full" our allocated array is adding new data to the "end" of our array
    - when the array is full **allocate more space** enough for ki+1 > ki pieces of data
    - copy the old array to the new array and **free** the old array
    -  repeat until all data is gathered


