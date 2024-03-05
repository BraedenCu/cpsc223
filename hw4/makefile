CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

TARGET1 = Blotto
TARGET2 = GmapUnit

SOURCES1 = main.c entry.c gmap.c gmap_test_functions.c string_key.c
SOURCES2 = gmap_unit.c gmap_test_functions.c entry.c string_key.c gmap.c

OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJECTS1)

$(TARGET2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJECTS2)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJECTS1) $(OBJECTS2)
