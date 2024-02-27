

void InsertionSort(int numbers[], int numbersSize) 
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







