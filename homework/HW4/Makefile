CFLAGS ?= -O2 -g -Wall -Wextra
LDLIBS  = -lm

.PHONY: all clean

all: arith

arith: main.o arith_lib.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o arith_lib.o: arith_lib.h

clean:
	rm -rf arith *.o *.dSYM
