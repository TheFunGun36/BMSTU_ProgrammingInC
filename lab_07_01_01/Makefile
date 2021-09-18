CFLAGS = -std=c99 -pedantic -Wall -Werror -g3 -Iinc
CC = gcc

build/app.exe: build/obj/main.o build/obj/fileio.o build/obj/arrayworks.o
	$(CC) $^ -o $@

build/obj/main.o: src/main.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/fileio.o: src/fileio.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/arrayworks.o: src/arrayworks.c inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

.PHONY: clear

clear:
	rm build/obj/*. build/*.exe
