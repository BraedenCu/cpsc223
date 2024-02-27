void Merge(int numbers[], int i, int j, int k) {
    int n1 = j - i + 1; // Size of left subarray
    int n2 = k - j;     // Size of right subarray

    // Create temporary arrays
    int Left[n1], Right[n2];

    // Copy data to temporary arrays
    for (int a = 0; a < n1; a++)
        Left[a] = numbers[i + a];
    for (int b = 0; b < n2; b++)
        Right[b] = numbers[j + 1 + b];

    int leftIndex = 0, rightIndex = 0, mergeIndex = i;

    // Merge the temp arrays back into numbers[i..k]
    while (leftIndex < n1 && rightIndex < n2) {
        //TODO: Merge the temp arrays back into numbers[i..k]
    }

    // Copy the remaining elements of Left[], if there are any
    while (leftIndex < n1) {
        //TODO: Copy the remaining elements of Left[], if there are any
    }

    // Copy the remaining elements of Right[], if there are any
    while (rightIndex < n2) {
        //TODO: Copy the remaining elements of Right[], if there are any
    }
}

void MergeSort(int numbers[], int i, int k) {
    if (i < k) {
        int j = (i + k) / 2;

        //TODO: Implement this function here. Need to call MergeSort recursively twice.
    }
}
