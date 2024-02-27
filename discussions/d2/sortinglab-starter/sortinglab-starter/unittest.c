#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"

// Function to check if an array is sorted in ascending order
bool isSorted(int arr[], int n) {
// TODO: Implement this function

}

// Function to print array (for debugging)
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Test function for SelectionSort
void testSelectionSort(int arr[], int n) {


    SelectionSort(arr, n);
    //printf("SelectionSort: ");
    //printArray(arr, n);

    if (isSorted(arr, n)) {
        printf("SelectionSort test passed\n");
    } else {
        printf("SelectionSort test failed\n");
    }
}

// Similar test functions for Quicksort, InsertionSort, and MergeSort...

int main(void) {
    size_t numbersSize = 10000;
    int numbers[numbersSize];
    srand(time(NULL)); // initialize random seed

    for (int i = 0; i < numbersSize; ++i) {
        numbers[i] = rand() % 10000 + 1; // Generate a random number between 1 and 10000 
    }
 
    testSelectionSort( numbers, numbersSize);
    // Call other test functions here...
    return 0;
}
