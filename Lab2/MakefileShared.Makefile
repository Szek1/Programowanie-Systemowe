cc = gcc

Final: 49406.ps.lab03.shared.main.c 
	${cc} 49406.ps.lab03.shared.main.c -o Final -ldl

49406.ps.lab03.shared.lib.so: 49406.ps.lab03.shared.lib.o
	${cc} -shared -fPIC -o 49406.ps.lab03.shared.lib.so 49406.ps.lab03.shared.lib.o

49406.ps.lab03.shared.lib.o: 49406.ps.lab03.shared.lib.c
	${cc} -fPIC -c 49406.ps.lab03.shared.lib.c -o 49406.ps.lab03.shared.lib.o

clean:
	rm 49406.ps.lab03.shared.lib.o 49406.ps.lab03.shared.lib.so 49406.ps.lab03.shared.main.o Final 2> /dev/null



