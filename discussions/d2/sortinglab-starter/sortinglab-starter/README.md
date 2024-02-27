# Section - Sorting Lab

In this assignment you will implement crucial sorting algorithms and see how they perform under various input size. 

The program starts with the `driver.c` and uses the functions listed in `interface.h`. You have following tasks to do files below:

* `selectionsort.c`
* `unittest.c`
* `mergesort.c`

# Tasks

## Part 1
0. Listen to your instructor for the explanation of the driver and interface files.

1. Go to selectionsort.c and complete the inner loop with given variables.

2. Go to unitest.c and complete the isSorted function to test your Selection sort function.

3. Type `make` in your terminal for compilation. Also, type `make Test` to create Test executable. 

4. Execute `Sort` with the following command: `./Sort selection 8` Please note that argv[1] defines the type of sorting and argv[2] creates random numbers. Check if the sort is correct.

5. Execute `./Test` and see if your test function works correctly. 

6. Run `./Sort selection 10000`  and `./Sort insertion 10000` separately and evaluate the time difference. 

## Part 2

1. Go to `mergesort.c`and finish the implementation of `MergeSort`function. You need a recursive structure. You can look at the `quicksort.c` to cheat. 

2. Now go to `Merge` function and complete the missing codes under while loops to finish the merge. 

3. Run `./Sort merge 8` to see if your implementation is correct. 

4. Run `./Sort merge 10000` , `./Sort quick 10000` , and `./Sort insertion 10000` separately and evaluate the time difference. 

5. Optional: Go to `unittest.c` and create an additional function `void testMergeSort` to test your MergeSort.

### ENJOY!


