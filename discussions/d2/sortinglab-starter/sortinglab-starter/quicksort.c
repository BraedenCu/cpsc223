#include <stdbool.h>

int HoarePartition(int numbers[], int i, int k) {
    int pivot = numbers[i];
    int l = i - 1;
    int h = k + 1;

    while (true) {
        do {
            l++;
        } while (numbers[l] < pivot);

        do {
            h--;
        } while (numbers[h] > pivot);

        if (l >= h) return h;

        int temp = numbers[l];
        numbers[l] = numbers[h];
        numbers[h] = temp;
    }
}

void Quicksort(int numbers[], int i, int k) {
    if (i < k) {
        int p = HoarePartition(numbers, i, k);
        Quicksort(numbers, i, p);
        Quicksort(numbers, p + 1, k);
    }
}
