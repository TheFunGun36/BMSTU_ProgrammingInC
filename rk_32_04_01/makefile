OBJS = main.o student.o list.o fileio.o
CC = gcc
CARGS = -Wall -Werror -std=c99

app.exe: $(OBJS)
	$(CC) $(CARGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CARGS) -c $<