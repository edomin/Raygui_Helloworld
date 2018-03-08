CC = mingw32-gcc
CFLAGS = -O0 -Wall -I. -I/usr/local/mingw32/include -ggdb3 -fvar-tracking
LD = mingw32-gcc
LDFLAGS = -L/usr/local/mingw32/lib

all: hello.exe

hello.exe: main.o
	$(LD) $(LDFLAGS) -o hello.exe main.o -Wl,-Bstatic -ltigr -ld3d9

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
    
clean:
	rm -r -f main.o
