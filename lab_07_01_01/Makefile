CFLAGS = -std=c99 -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wall -Werror -g3 -Iinc
CC = gcc

app.exe: out/main.o out/fileio.o out/arrayworks.o
	$(CC) $^ -o $@

unit_testing.exe: out/arrayworks.o out/check_arrayworks.o out/check_main.o
	$(CC) $^ -o $@

out/main.o: src/main.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

out/fileio.o: src/fileio.c inc/fileio.h inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

out/arrayworks.o: src/arrayworks.c inc/arrayworks.h inc/errorcodes.h
	$(CC) $< $(CFLAGS) -c -o $@

out/check_arrayworks.o: unit_tests/check_arrayworks.c inc/arrayworks.h inc/arrayworks.h
	$(CC) $< $(CFLAGS) -c -o $@

out/check_main.o: unit_tests/check_main.c unit_tests/check_arrayworks.h inc/arrayworks.h
	$(CC) $< $(CFLAGS) -c -o $@


.PHONY: clear, test

clear:
	rm out/*. /*.exe

test: /unit_testing.exe
	@-.//unit_testing.exe
	@echo Failed: $$?
