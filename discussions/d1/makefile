CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

Life: main.o life.o helpers.o
	$(CC) $(CFLAGS) -o $@ $^

Test: testdemo.o life.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) Life Test *.o
