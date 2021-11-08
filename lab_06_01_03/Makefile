CFLAGS = -std=c99 -pedantic -Wall -Werror -g3
CC = gcc

build/app.exe: build/obj/main.o build/obj/fileio.o build/obj/product.o
	$(CC) $^ -o $@

build/obj/main.o: main.c
	$(CC) main.c $(CFLAGS) -c -o $@

build/obj/product.o: product.c product.h
	$(CC) product.c $(CFLAGS) -c -o $@

build/obj/fileio.o: fileio.c fileio.h
	$(CC) fileio.c $(CFLAGS) -c -o $@
