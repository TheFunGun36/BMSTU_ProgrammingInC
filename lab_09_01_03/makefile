CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -Iinc -g3 -fdiagnostics-color=always
OBJS = out/fileio.o out/product.o out/fileio.o

app.exe: out/main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

unit_tests.exe: out/check_main.o $(OBJS)
	$(CC) $^ -o $@ -lcheck -lpthread -lrt -lm # -lsubunit

out/%.o: src/%.c inc/*.h
	@-mkdir out/
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: unit_tests/%.c inc/*.h
	@-mkdir out/
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clear, all, unit

clean:
	rm out/ -r

all: app.exe

unit: unit_tests.exe
	./unit_tests.exe
	