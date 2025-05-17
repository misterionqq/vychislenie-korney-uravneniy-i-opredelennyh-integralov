#-----------------------
# Compiler/linker flags
#-----------------------


CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
    -Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
    -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
    -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
    -Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

#---------------
# Build scripts
#---------------

.PHONY: all

all: main test

main: main.o src/functions.o src/f.o
	$(CC) $(CFLAGS) -o $@ main.o $(LDLIBS) src/functions.o src/f.o

test: test.o src/functions.o src/f.o
	$(CC) $(CFLAGS) -o $@ test.o $(LDLIBS) src/functions.o src/f.o

main.o: main.c src/functions.h
	$(CC) $(CFLAGS) -Isrc -c main.c -o main.o

test.o: test.c src/functions.h
	$(CC) $(CFLAGS) -Isrc -c test.c -o test.o

src/functions.o: src/functions.c src/functions.h
	$(CC) $(CFLAGS) -Isrc -c src/functions.c -o src/functions.o

src/f.o : src/functions.asm
	nasm -felf32 src/functions.asm -o src/f.o

clean:
	rm -rf *.o src/*.o main test
