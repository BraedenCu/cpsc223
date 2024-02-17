# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

# Target executable name
TARGET = Hookbook

# Source files to compile
SOURCES = hookbooka.c pirate.c pirate_list.c libhookbook.c

# Object files to generate
OBJECTS = $(SOURCES:.c=.o)

# The first target is the default, building the main executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Dependency rules for source files
hookbooka.o: hookbooka.c pirate_list.h pirate.h libhookbook.h
pirate.o: pirate.c pirate.h
pirate_list.o: pirate_list.c pirate_list.h pirate.h
libhookbook.o: libhookbook.c libhookbook.h

# Rule to clean up all generated files
clean:
	rm -f $(TARGET) $(OBJECTS)