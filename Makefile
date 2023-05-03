CCFLAGS := -c -I./include -g -Wall -Wextra -pedantic -ansi
LDFLAGS := ""

CC := cc
LD := ld

sopa: main.o sopa.o
	$(LD) $(LDFLAGS) build/main.o build/sopa.o -o sopa

main.o: source/main.c include/sopa.h
	$(CC) $(CCFLAGS) source/main.c -o build/main.o

sopa.o: source/sopa.c include/sopa.h
	$(CC) $(CCFLAGS) source/sopa.c -o build/sopa.o
