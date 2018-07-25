CC = gcc

SRCS = sha3/blake.c sha3/bmw.c sha3/cubehash.c sha3/echo.c sha3/groestl.c sha3/jh.c sha3/keccak.c sha3/luffa.c sha3/shavite.c sha3/simd.c sha3/skein.c x11.c util.c
OBJS = sha3/blake.o sha3/bmw.o sha3/cubehash.o sha3/echo.o sha3/groestl.o sha3/jh.o sha3/keccak.o sha3/luffa.o sha3/shavite.o sha3/simd.o sha3/skein.o x11.o util.o

test: $(OBJS) test.o
	$(CC) test.o x11.o util.o sha3/*.o

all: $(OBJS) main.o
	$(CC) main.o x11.o util.o sha3/*.o

clean:
	rm -fr a.out a.out.dSYM *.o sha3/*.o
