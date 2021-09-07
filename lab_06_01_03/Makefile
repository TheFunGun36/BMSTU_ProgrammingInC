build:
ifeq ("$(wildcard ./main.o)","")
	make main
else
ifeq ("$(wildcard ./product.o)","")
	make product
else
ifeq ("$(wildcard ./fileio.o)","")
	make fileio
else
	gcc main.o product.o fileio.o -o app.exe
endif
endif
endif

main:
	gcc -std=c99 -Wpedantic -Wall -Werror -g3 main.c -c
	make build

product:
	gcc -std=c99 -Wpedantic -Wall -Werror -g3 product.c -c
	make build

fileio:
	gcc -std=c99 -Wpedantic -Wall -Werror -g3 fileio.c -c
	make build

clear:
	rm *.o *.exe

test:
ifeq ("$(wildcard ./app.exe)","")
	make build
endif
	./test.sh
	