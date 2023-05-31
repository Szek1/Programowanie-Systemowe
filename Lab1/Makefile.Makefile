// PS IS1 322 LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

cc=gcc
ldflags=-g

main: lib.o main.o
	${cc} ${ldflags} -o $@ $^

clean:
	rm -f main.o lib.o main


