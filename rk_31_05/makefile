CC = gcc
CFLAGS = -Wall -Werror -Iinc
OBJS = out/field.o out/fileio.o

app.exe: out/main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

out/%.o: src/%.c inc/*.h
	@-mkdir out
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: all, clear

all: app.exe

clear:
	rm out/*.o app.exe

