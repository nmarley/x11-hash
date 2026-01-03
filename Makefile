CC = clang
AR = ar

SRCS = sha3/blake.c sha3/bmw.c sha3/cubehash.c sha3/echo.c sha3/groestl.c sha3/jh.c sha3/keccak.c sha3/luffa.c sha3/shavite.c sha3/simd.c sha3/skein.c x11.c util.c
OBJS = sha3/blake.o sha3/bmw.o sha3/cubehash.o sha3/echo.o sha3/groestl.o sha3/jh.o sha3/keccak.o sha3/luffa.o sha3/shavite.o sha3/simd.o sha3/skein.o x11.o util.o

DEBUG_TGT=debug
TEST_TGT=test
X11SUM_TGT=x11sum
LIB_TGT=libx11.a
TARGETS=$(DEBUG_TGT) $(TEST_TGT) $(X11SUM_TGT) $(LIB_TGT)

test: $(OBJS) test.o
	$(CC) test.o x11.o util.o sha3/*.o -o test
	./test

debug: $(OBJS) main.o
	$(CC) main.o x11.o util.o sha3/*.o -o debug

x11sum: $(OBJS) main.o
	$(CC) main.o x11.o util.o sha3/*.o -o x11sum

libx11.a: $(OBJS)
	$(AR) -ru $@ $^

clean:
	rm -fr a.out a.out.dSYM *.o sha3/*.o $(TARGETS)
