CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Iinc -g3 -fdiagnostics-color=always
OBJS = out/mylib.o

app.exe: out/main.o $(OBJS)
	$(CC) $(CFLAGS)$^ -o $@ -lm -fdiagnostics-color=always

unit_tests.exe: out/check_main.o $(OBJS)
	$(CC) $^ -o $@ -lcheck -lpthread -lrt -lm -fdiagnostics-color=always # -lsubunit

out/%.o: src/%.c inc/*.h
	@-mkdir out/
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: unit_tests/%.c
	@-mkdir out/
	$(CC) $(CFLAGS) -Iunit_tests -c $< -o $@


.PHONY: clear, all, unit

clean:
	rm out/ -r

all: app.exe

unit: unit_tests.exe
	