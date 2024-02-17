# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g
# Add -fPIE to CFLAGS if you want to compile your source files with Position Independent Executable support
LDFLAGS = -no-pie

# Target executable name
TARGET = Hookbook

# Source files to compile (exclude pirate.c and pirate_list.c)
SOURCES = hookbooka.c libhookbook.c

# Object files to generate from SOURCES
OBJECTS = $(SOURCES:.c=.o)

# Precompiled object files to include
PRECOMPILED_OBJS = ref_pirate_list.o ref_pirate.o

# The first target is the default, building the main executable
$(TARGET): $(OBJECTS) $(PRECOMPILED_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(PRECOMPILED_OBJS)

# Dependency rules for source files
hookbooka.o: hookbooka.c pirate_list.h pirate.h libhookbook.h
libhookbook.o: libhookbook.c libhookbook.h

# Rule to clean up all generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
