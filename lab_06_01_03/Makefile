CFLAGS = -std=c99 -pedantic -Wall -Werror -g3
CC = gcc

app.exe: main.o fileio.o product.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) main.c $(CFLAGS) -c

product.o: product.c product.h
	$(CC) product.c $(CFLAGS) -c

fileio.o: fileio.c fileio.h
	$(CC) fileio.c $(CFLAGS) -c
	