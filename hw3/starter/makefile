CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

TARGET = Hookbook

SOURCES = hookbookb.c pirate.c pirate_list.c libhookbook.c skills_list.c 

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

hookbookb.o: hookbookb.c pirate_list.h pirate.h libhookbook.h
pirate.o: pirate.c pirate.h pirate_list.h skills_list.h
pirate_list.o: pirate_list.c pirate_list.h pirate.h 
libhookbook.o: libhookbook.c libhookbook.h

clean:
	rm -f $(TARGET) $(OBJECTS)