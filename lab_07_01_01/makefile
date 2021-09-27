CFLAGS = -std=c99 -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wall -Werror -g3 -Iinc
CC = gcc
OBJ = out/fileio.o out/arrayworks.o
CHECKOBJ = out/check_arrayworks.o out/check_main.o

app.exe: out/main.o $(OBJ)
	$(CC) $^ -o $@

unit_tests.exe: $(CHECKOBJ) $(OBJ)
	$(CC) $^ -o $@

out/%.o: src/%.c inc/*.h
	@-mkdir out
	$(CC) $< $(CFLAGS) -c -o $@

out/%.o: unit_tests/%.c inc/*.h
	@-mkdir out
	$(CC) $< $(CFLAGS) -c -o $@

.PHONY: clear, test

clear:
	rm out/*.o *.exe
