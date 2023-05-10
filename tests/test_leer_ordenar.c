#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sopa.h"

typedef struct cases {
	int number;
	int word_count;
	char path[128];
} cases;

cases test_cases[] = {
	{0, 5, "test_cases/palabras/1"},
	{1, 5, "test_cases/palabras/2"},
	{2, 5, "test_cases/palabras/3"},
	{3, 5, "test_cases/palabras/4"},
	{4, 5, "test_cases/palabras/5"},
	{5, 1, "test_cases/palabras/6"},
	{6, 2, "test_cases/palabras/7"},
	{7, 2, "test_cases/palabras/8"},
};

bool ordenadas(palabra_t *l) {
	bool ret = true;

	while (ret && l->sig != NULL) {
		ret = (strcmp(l->letras, l->sig->letras) < 0);
		l = l->sig;
	}
	return ret;
}

int main(void) {
	palabra_t *l;
	int n, i;

	for (i = 0; i < 8; i++) {
		l = leer_palabras(test_cases[i].path, &n);
		printf("Caso %d\t Ordenado: %d\t num palabras correcto: %d\n",
				i, ordenadas(l), n == test_cases[i].word_count);
	}

	return 0;
}
