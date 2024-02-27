#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 2
#define RESIZE_FACTOR 2

int array_is_full(size_t length, size_t capacity)
{
    return length == capacity;
}

int array_too_small(size_t length, size_t capacity)
{
    return capacity > INITIAL_CAPACITY && length * RESIZE_FACTOR * RESIZE_FACTOR < capacity;
}

size_t grow_capacity(size_t capacity)
{
    capacity *= RESIZE_FACTOR;
    return capacity;
}

size_t shrink_capacity(size_t capacity)
{
    capacity /= RESIZE_FACTOR;
    return capacity;
}

int main(int argc, char *argv[])
{
    // Create a list of ints
    size_t length = 0, capacity = INITIAL_CAPACITY;
    int *lst = calloc(capacity, sizeof(int));
    int num;
    while (fscanf(stdin, "%d", &num) > 0)
    {
        if (num >= 0)
        {
            // Add a '1' to the end of the list
            if (array_is_full(length, capacity))
            {
                capacity = grow_capacity(capacity);
                lst = realloc(lst, capacity * sizeof(int));
            }
            lst[length] = 1;
            length++;
        }
        else if (length > 0)
        {
            // Remove the last element of the list
            length--;
            if (array_too_small(length, capacity))
            {
                capacity = shrink_capacity(capacity);
                lst = realloc(lst, capacity * sizeof(int));
            }
        }

        // Print the important part of the list
        for (size_t i = 0; i < length; i++)
        {
            fprintf(stdout, "%d", lst[i]);
        }

        // Print the rest of the array as '_'s
        for (size_t i = length; i < capacity; i++)
        {
            fprintf(stdout, "_");
        }
        fprintf(stdout, "\n");
    }

    free(lst);

    printf("Done.\n");
    return 0;
}
