CCFLAGS := -I./include -g -Wall -Wextra -pedantic -ansi
LDFLAGS := ""

CC := cc
LD := ld

sopa: source/main.c source/sopa.c include/sopa.h
	$(CC) $(CCFLAGS) -o sopa source/main.c source/sopa.c

clean:
	rm sopa

test_leer_ordenar: source/sopa.c include/sopa.h tests/test_leer_ordenar.c
	$(CC) $(CCFLAGS) -o test_leer_ordenar tests/test_leer_ordenar.c source/sopa.c

test_ranint: source/sopa.c include/sopa.h tests/test_ranint.c
	$(CC) $(CCFLAGS) -o test_ranint tests/test_ranint.c source/sopa.c
