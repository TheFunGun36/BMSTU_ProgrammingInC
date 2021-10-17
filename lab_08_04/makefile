CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -Iinc -g3
OBJS = out/matrix.o out/userio.o

app.exe: out/main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

out/%.o: src/%.c inc/*.h
	@-mkdir out/
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clear, all

clear:
	rm out/ -r

all: app.exe
