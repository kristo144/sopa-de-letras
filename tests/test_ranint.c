#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sopa.h"

int main(void) {
	int t[10];
	int i;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
		t[i] = 0;

	for (i = 0; i < 10000; i++)
		t[ran_int(1,8)]++;

	for (i = 0; i < 10; i++)
		printf("%d:\t%d\n", i, t[i]);

	return 0;
}
