CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -Werror -g

.PHONY: clean

main : main.o 
	${CC} ${CFLAGS} -o $@ $^

clean : 
	${RM} *.{o,a}
