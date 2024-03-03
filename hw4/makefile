CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

TARGET = Blotto

SOURCES = main.c entry.c gmap_array.c gmap_test_functions.c libmain.c string_key.c

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.c: libmain.h entry.h gmap.h gmap_test_functions.h libmain.h string_key.h 
entry.c: entry.h
gmap_array.c: gmap.h
gmap_test_functions.c: gmap_test_functions.h
libmain.c: libmain.h
string_key.c: string_key.h

clean:
	rm -f $(TARGET) $(OBJECTS)