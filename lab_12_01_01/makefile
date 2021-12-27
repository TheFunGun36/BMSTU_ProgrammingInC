CFLAGS = -std=c99 -Wfloat-conversion -Wvla -Wfloat-equal -Wall -Werror -g3 -Iinc -ldl
CC = gcc

app.exe: out/main.o out/fileio.a arrayworks.dll
	$(CC) $^ -o $@ -ldl

unit_tests.exe: out/check_main.o out/arrayworks.o out/check_arrayworks.a
	$(CC) $^ -o $@

out/%.o: src/%.c inc/*.h
	@-mkdir out
	$(CC) $< $(CFLAGS) -c -o $@

out/%.o: unit_tests/%.c inc/*.h unit_tests/*.h
	@-mkdir out
	$(CC) $< $(CFLAGS) -c -o $@

out/%.a: src/%.o inc/*.h
	@-mkdir out
	ar rc $@ $<
	ranlib $@

out/%.a: unit_tests/%.o inc/*.h unit_tests/*.h
	@-mkdir out
	ar rc $@ $<
	ranlib $@

%.dll: src/%.o inc/*.h
	@-mkdir out
	$(CC) -shared $< -o $@ -fPIC

%.dll: unit_tests/%.o inc/*.h unit_tests/*.h
	@-mkdir out
	$(CC) -shared $< -o $@

.PHONY: clear, unit

clear:
	@-rm out -r
	@-rm log -r
	@-rm app.exe unit_tests.exe
	@-rm check_arrayworks.dll arrayworks.dll

unit: unit_tests.exe
	./unit_tests.exe
