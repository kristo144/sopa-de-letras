CCFLAGS := -I./include -g -Wall -Wextra -pedantic -ansi
LDFLAGS := ""

CC := cc
LD := ld

sopa: source/main.c source/sopa.c include/sopa.h
	$(CC) $(CCFLAGS) -o sopa source/main.c source/sopa.c

clean:
	rm sopa
