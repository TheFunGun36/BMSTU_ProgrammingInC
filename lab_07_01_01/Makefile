CFLAGS = -std=c99 -pedantic -Wall -Werror -g3 -Iinc
CC = gcc

build/app.exe: build/obj/main.o build/obj/fileio.o build/obj/arrayworks.o
	$(CC) $^ -o $@

build/unit_testing.exe: build/obj/arrayworks.o build/obj/check_arrayworks.o build/obj/check_main.o
	$(CC) $^ -o $@

build/obj/main.o: src/main.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/fileio.o: src/fileio.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/arrayworks.o: src/arrayworks.c inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/check_arrayworks.o: unit_tests/check_arrayworks.c inc/arrayworks.h inc/arrayworks.h
	$(CC) $< $(CFLAGS) -c -o $@

build/obj/check_main.o: unit_tests/check_main.c unit_tests/check_arrayworks.h inc/arrayworks.h
	$(CC) $< $(CFLAGS) -c -o $@


.PHONY: clear, test

clear:
	rm build/obj/*. build/*.exe

test: build/unit_testing.exe
	@-./build/unit_testing.exe
	@echo Failed: $$?
