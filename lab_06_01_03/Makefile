CFLAGS = -std=c99 -pedantic -Wall -Werror -g3
CC = gcc

build/app.exe: build/obj/main.o build/obj/fileio.o build/obj/product.o
	$(CC) $^ -o $@

build/obj/main.o: src/main.c
	$(CC) src/main.c $(CFLAGS) -c -o $@

build/obj/product.o: src/product.c src/product.h
	$(CC) src/product.c $(CFLAGS) -c -o $@

build/obj/fileio.o: src/fileio.c src/fileio.h
	$(CC) src/fileio.c $(CFLAGS) -c -o $@
