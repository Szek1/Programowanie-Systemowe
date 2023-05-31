
cc=gcc
ldflags=-g

Final: 49406.ps.lab03.static.main.o 49406.ps.lab03.static.lib.o
	${cc} ${ldflags} -o $@ $^


49406.ps.lab03.static.lib.a: 49406.ps.lab03.static.lib.o
	ar rcs 49406.ps.lab03.static.lib.a 49406.ps.lab03.static.lib.o


clean:
	rm 49406.ps.lab03.static.lib.o 49406.ps.lab03.static.main.o Final 49406.ps.lab03.static.lib.a

