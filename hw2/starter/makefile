# compiler and compiler flags
CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

# target executable name
TARGET = Hookbook

# source files to compile
SOURCES = hookbooka.c pirate.c pirate_list.c libhookbook.c

# object files to generate
OBJECTS = $(SOURCES:.c=.o)

# the first target is the default, building the main executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# dependency rules for source files
hookbooka.o: hookbooka.c pirate_list.h pirate.h libhookbook.h
pirate.o: pirate.c pirate.h
pirate_list.o: pirate_list.c pirate_list.h pirate.h
libhookbook.o: libhookbook.c libhookbook.h

# rule to clean up all generated files
clean:
	rm -f $(TARGET) $(OBJECTS)