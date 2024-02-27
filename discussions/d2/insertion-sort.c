#include <stdio.h>

void insertionSort(int numbers[], int numbersSize) 
{
  for (int i = 1; i < numbersSize; i++) 
  {
    // Insert list[i] into a sorted sublist list[0..i-1] so that
    //  list[0..i] is sorted. 
    int currentElement = numbers[i];
    int k;
    for (k = i - 1; k >= 0 && numbers[k] > currentElement; k--) 
    {
      numbers[k + 1] = numbers[k];
    }

    // Insert the current element into list[k+1]
    numbers[k + 1] = currentElement;
  }
}

int main()
{
  const int numbersSize = 5;
  int numbers[] = { 11, 3, 79, 5, 45 };
  insertionSort(numbers, numbersSize);
  for (int i = 0; i < numbersSize; i++)
    printf("%d ", numbers[i]);
    printf("\n");

  return 0;
}  





