#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sopa.h"

void escribir_mensaje_bienvenida() {
}

palabra_t *leer_palabras(char *nombre_fichero, int *n_pal) {
	nombre_fichero = nombre_fichero;
	n_pal = n_pal;
	return NULL;
}

palabra_t *nueva_palabra(char *s) {
	palabra_t *ret;

	ret = calloc(1, sizeof(palabra_t));
	if (ret != NULL) {
		ret->sig = NULL;
		ret->ant = NULL;
		strncpy(ret->letras, s, MAX_PALABRA + 1);
	}
	return ret;
}

void insertar_palabra_en_lista(palabra_t *primera, palabra_t *nueva) {
	/* Encuentra la ultima palabra en la lista que es menor que la nueva. */
	while ((primera->sig != NULL) &&
			(strcmp(primera->sig->letras, nueva->letras) < 0))
		primera = primera->sig;
	insertar_despues(primera, nueva);
}

void insertar_despues(palabra_t *a, palabra_t *b) {
	palabra_t *aux;
	aux = a->sig;
	a->sig = b;
	b->sig = aux;
	b->ant = a;
	if (b->sig != NULL)
		b->sig->ant = b;
	return;
}

void mostrar_palabras (palabra_t *p, int n) {
	p = p;
	n = n;
}

int pedir_tamano_sopa(int min, int max) {
	min = min;
	max = max;
	return 0;
}

sopa_t *generar_sopa(int dim, palabra_t *p) {
	dim = dim;
	p = p;
	return NULL;
}

void insertar_palabras(sopa_t *j) {
	j = j;
}

void insertar_palabra(sopa_t *j, palabra_t *p) {
	j = j;
	p = p;
}

void posicion_aleatoria(palabra_t *p, int dim) {
	p = p;
	dim = dim;
}

int ran_int(int min, int max) {
	min = min;
	max = max;
	return 0;
}

bool comprobar_posicion_valida(sopa_t *j, palabra_t *p) {
	j = j;
	p = p;
	return false;
}

int buscar_casilla(int dim, palabra_t *p, int i) {
	dim = dim;
	p = p;
	i = i;
	return 0;
}

void escribir_palabra(sopa_t *j, palabra_t *p) {
	int i = 0;

	while (p->letras[i] != '\0') {
		j->letras[buscar_casilla(j->dim, p, i)] = p->letras[i];
		i++;
	}
}

void rellenar_espacios_vacios(sopa_t *j) {
	j = j;
}

bool jugada_usuario(sopa_t *j) {
	bool ret;
	char input[MAX_PALABRA + 1];
	palabra_t *intento, *p;

	printf("Pon la palabra que has encontrado,\n"
			"o pon " RENDICION " para ver la solucion:");
	leer_string(input);

	if (!strcmp(input, RENDICION)) {
		ret = true;
	}
	else {
		ret = false;
		p = encontrar_palabra_lista(j->pal_0, input);

		if (p == NULL) {
			printf("La palabra no esta en la lista.");
		}
		else {
			intento = nueva_palabra(input);
			if (intento == NULL) {
				printf("Error asignacion memoria. Intentelo de nuevo.\n");
			}
			else {
				pedir_coordenadas(intento);
				if (comprobar_palabras_iguales(p, intento))
					marcar_acierto(j, p);
				else
					printf("No has acertado.");
			}
			free(intento);
		}
	}
	return ret;
}

void leer_string(char *s) {
	scanf("%" TOSTR(MAX_PALABRA) "s", s);
	limpiar_stdin();
}

palabra_t *encontrar_palabra_lista(palabra_t *p, char *s) {
	p = p;
	s = s;
	return NULL;
}

void pedir_coordenadas(palabra_t *p) {
	printf("En que fila empieza la palabra? ");
	p->x_0 = leer_numero();
	printf("En que columna empieza la palabra? ");
	p->y_0 = leer_numero();
	printf("En que direccion esta escrita la palabra?\n");
	mostrar_direcciones();
	p->dir = leer_numero();
}

void mostrar_direcciones() {
	printf("Posibles direcciones:\n"
			" 1: horizontal\n"
			"-1: horizontal reves\n"
			" 2: vertical\n"
			"-2: vertical reves\n");
	return;
}

int leer_numero() {
	int n;
	scanf("%d", &n);
	limpiar_stdin();
	return n;
}

void limpiar_stdin() {
	char c;
	do {
		c = getchar();
	} while (c != '\n');
	return;
}

bool comprobar_palabras_iguales(palabra_t *a, palabra_t *b) {
	a = a;
	b = b;
	return true;
}

void marcar_acierto(sopa_t *j, palabra_t *p) {
	j = j;
	p = p;
}

void marcar_letras_acertadas(sopa_t *j, palabra_t *p) {
	j = j;
	p = p;
}

void eliminar_palabra_lista(sopa_t *j, palabra_t *p) {
	p->sig->ant = p->ant;
	if (p == j->pal_0)
		j->pal_0 = p->sig;
	else
		p->ant->sig = p->sig;
	free(p);
	return;
}

void mostrar_solucion(sopa_t *j) {
	while (j->pal_0 != NULL) {
		marcar_acierto(j, j->pal_0);
	}
	mostrar_sopa(j);
}

void liberar_palabras(palabra_t *p) {
	p = p;
}

void mostrar_sopa(sopa_t *j) {
	/* Usado codigo proporcionado */
	int i, k;

	/* Mostrar numeros de columna */
	COLOR_FG_ROJO();
	printf("\033[0;31m");   /* Color */
	printf("  ");
	for (i = 10; i < j->dim + 1; i+=10) {
		for (k=0; k < 18; k++)
			printf(" ");
		printf(" %d", i/10);
	}

	printf("\n  ");   
	for (i = 0; i < j->dim; i++) {   
		printf(" %d", (i + 1) % 10);
		/*
		int p = (i % 10) + 1;
		p != 10 ? printf(" %d", p) : printf(" 0");
		*/
	}

	printf("\n");
	printf("\033[0m");  /* Volver al color por defecto */


	/* Mostrar letras. Cada letra ocupa dos espacios: */
	/* Si esta encertada, se marca */
	for (i = 0; i < j->dim ; i++)
	{
		printf("\033[0;31m");	/* Color  */
		printf("%-2d", i + 1);	/* Mostrar numero de linia */
		printf("\033[0m");	/* Tornem al color per defecte */

		for (k = 0; k < j->dim; k++) {
			if (j->aciertos[i * j->dim + k]) {
				printf("\033[0;42m");   /* Color verd de fons */
				printf(" %c", j->letras[i * j->dim + k]);
				printf("\033[0m");  /* Tornem al color per defecte */
			}
			else {
				printf(" %c", j->letras[i * j->dim + k]);
			}
		}
		printf("\n");
	}
	printf("\n");

	printf("Llevas %d aciertos.\n", j->n_aciertos);
	mostrar_palabras(j->pal_0, j->n_palabras);
}

void felicitar_jugador() {
	printf("Enhorabuena! Has acertado todas las palabras!\n");
}

void liberar_memoria(sopa_t *j) {
	if (j != NULL) {
		liberar_palabras(j->pal_0);
		free(j->letras);
		free(j->aciertos);
		free(j);
	}
	return;
}

