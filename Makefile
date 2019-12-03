CC = gcc
CFLAGS = -Wall -Werror -std=c99

all: matrix first second

matrix : matrix.c matrix.h
	$(CC) $(CFLAGS) matrix.c -o matrix

first : first.c first.h
	$(CC) $(CFLAGS) first.c -o first

second : second.c second.h
	$(CC) $(CFLAGS) second.c -o second

clean:
	rm -rf matrix first second
