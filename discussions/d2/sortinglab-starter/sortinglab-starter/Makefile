CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

Sort: driver.o selectionsort.o insertionsort.o mergesort.o quicksort.o
	$(CC) $(CFLAGS) -o $@ $^

Test: unittest.o selectionsort.o insertionsort.o mergesort.o quicksort.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) Sort Test *.o