CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g
all: HelloWorld HelloJack
HelloWorld: hello_1.c
	$(CC) $(CFLAGS) -o HelloWorld hello_1.c
HelloJack: hello_2.c
	$(CC) $(CFLAGS) -o HelloJack hello_2.c
clean: 
	rm -f HelloWorld HelloJack
	
