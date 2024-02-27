#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"

int main(int argc, char *argv[]) {
  
    if (argc < 3) {
        fprintf(stderr, "Need more input\n");
        return 1;
    }

    char *sortType = argv[1];
    size_t numbersSize = atoi (argv[2]);
    int numbers[numbersSize];

    srand(time(NULL)); // initialize random seed

    printf("UNSORTED: ");
    for (int i = 0; i < numbersSize; ++i) {
        numbers[i] = rand() % 1000 + 1; // Generate a random number between 1 and 100
        printf("%i ", numbers[i]);
    }
        printf("\n");

    clock_t start, end;
    double cpu_time_used;
    start = clock(); // Start the timer

    if (strcmp(sortType, "selection") == 0) 
    {
        SelectionSort(numbers, numbersSize);
    } 
    else if (strcmp(sortType, "quick") == 0)
    {
        Quicksort(numbers, 0, numbersSize - 1);
    } 
    else if (strcmp(sortType, "insertion") == 0)
    {
        InsertionSort(numbers, numbersSize);
    } 
    else if (strcmp(sortType, "merge") == 0)
    {
        MergeSort(numbers, 0, numbersSize - 1);
    } 
    else
     {
        fprintf(stderr, "Invalid sort type\n");
        return 1;
     }
    
    end = clock(); // End the timer
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calculate elapsed time

 
    printf("SORTED: ");
    for (int i = 0; i < numbersSize; ++i) {
      printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Time used: %f seconds\n", cpu_time_used);

    return 0;
}
