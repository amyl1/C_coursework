all: maths_prog libmaths.so
maths_prog: maths_prog.o add.o subtract.o
	    gcc -Wall -Wextra -pedantic -std=c11 -o maths_prog maths_prog.o add.o subtract.o
libmaths.so: maths_prog.c add.c subtract.c
		gcc -Wall -Wextra -pedantic -std=c11 maths_prog.c add.c subtract.c -o libmaths.so -fPIC -shared 
maths_prog.o: maths_prog.c add.h subtract.h
	    gcc -Wall -Wextra -pedantic -std=c11 -c maths_prog.c
add.o: add.c add.h
	    gcc -Wall -Wextra -pedantic -std=c11 -c add.c
subtract.o: subtract.c subtract.h
	    gcc -Wall -Wextra -pedantic -std=c11 -c subtract.c

clean:
	rm -rf maths_prog libmaths.so maths_prog.o add.o subtract.o
 

