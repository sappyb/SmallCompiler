
CC=gcc
CPP=g++
LIBS=
COFLAGS=-g
CWFLAGS=-Wall
CIFLAGS=
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)
all:		compile Code
compile:	javaclass.h bytecode.h global.h compile.c javaclass.o bytecode.o symbol.o lexer.o init.o error.o
		$(CC) $(CFLAGS) -o compile compile.c javaclass.o bytecode.o symbol.o lexer.o init.o error.o
Code:		compile
		
.c.o:
		$(CC) $(CFLAGS) -c $<
.PHONY: clean distclean
clean:
		rm -f *.o
distclean:
		rm -f compile *.o *.class
