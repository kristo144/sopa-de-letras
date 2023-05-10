#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sopa.h"

void escribir_mensaje_bienvenida() {
	printf(
			"****************************************************\n"
			"Bienvenido al juego SOPA DE LETRAS!\n"
			"Autores: Diego Marquez, Clara Puig, Kristiyan Tonev\n"
			"****************************************************\n"
			);
	return;
}

palabra_t *leer_palabras(char *nombre_fichero, int *n_pal) {
	palabra_t *ret, *pal;
	FILE *f;
	char s[MAX_PALABRA + 1];

	f = fopen(nombre_fichero, "r");
	if (f == NULL) {
		ret = NULL;
		*n_pal = 0;
	}
	else {
		/* No se hace comprobacion de input, tal y como indica el enunciado. */
		/* Leer primera palabra. */
		fscanf(f, "%" TOSTR(MAX_PALABRA) "s", s);
		ret = nueva_palabra(s);
		*n_pal = 1;

		/* Leer resto de palabras */
		fscanf(f, "%" TOSTR(MAX_PALABRA) "s", s);
		while (!feof(f)) {
			pal = nueva_palabra(s);
			ret = insertar_palabra_en_lista(ret, pal);
			*n_pal = *n_pal + 1;
			fscanf(f, "%" TOSTR(MAX_PALABRA) "s", s);
		}
	}
	return ret;
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

palabra_t *insertar_palabra_en_lista(palabra_t *primera, palabra_t *nueva) {
	palabra_t *ret;

	/* Si la nueva va antes que la primera: */
	if (strcmp(primera->letras, nueva->letras) > 0) {
		insertar_despues(nueva, primera);
		ret = nueva;
	}
	else {
		ret = primera;
		/* Encuentra la ultima palabra en la lista que es menor que la nueva. */
		while ((primera->sig != NULL) &&
				(strcmp(primera->sig->letras, nueva->letras) < 0))
			primera = primera->sig;
		insertar_despues(primera, nueva);
	}
	return ret;
}

void insertar_despues(palabra_t *a, palabra_t *b) {
	palabra_t *aux;

	aux = a->sig;
	a->sig = b;
	if (aux != NULL) /* Comprobacion !NULL para el caso que a es la nueva y b es la lista */
		b->sig = aux;
	b->ant = a;
	if (b->sig != NULL)
		b->sig->ant = b;
	return;
}

void mostrar_palabras(palabra_t *p, int n) {
	printf("Quedan %d palabras:\n", n);
	while (p != NULL) {
		puts(p->letras);
		p = p->sig;
	}
	return;
}

int pedir_tamano_sopa(int min, int max) {
	int n = 0;

	printf("Pon la dimension de la sopa entre %d y %d: ", min, max);
	n = leer_numero();

	while (n < min || n > max) {
		printf("Numero no valido. Pon la dimension de la sopa entre %d y %d: ", min, max);
		n = leer_numero();
	}
	return n;
}

sopa_t *generar_sopa(int dim, palabra_t *p) {
	sopa_t *j = calloc(1, sizeof(sopa_t));
	if (j != NULL) {
		j->letras = calloc(dim * dim, sizeof(char));
		j->aciertos = calloc(dim * dim, sizeof(bool));

		if (j->letras != NULL && j->aciertos != NULL) {
			j->dim = dim;
			j->pal_0 = p;
			insertar_palabras(j);
			rellenar_espacios_vacios(j);
		}
		else {
			liberar_memoria(j);
			j = NULL;
		}
	}

	return j;
}

void insertar_palabras(sopa_t *j) {
	palabra_t *p = j->pal_0;
	while (p != NULL) {
		insertar_palabra(j, p);
		j->n_palabras = j->n_palabras + 1;
		p = p->sig;
	}
	return;
}

void insertar_palabra(sopa_t *j, palabra_t *p) {
	do {
		posicion_aleatoria(p, j->dim);
	} while (!comprobar_posicion_valida(j, p));
	escribir_palabra(j, p);
	return;
}

void posicion_aleatoria(palabra_t *p, int dim) {
	/* Lista de direcciones */
	int dirs[] = {HOR_DIR, HOR_REV, VER_DIR, VER_REV};
	int len, num_dirs;

	/* Calcular el numero de direcciones posibles. Elegir una aleatoria. */
	num_dirs = sizeof(dirs) / sizeof(int);
	p->dir = dirs[ran_int(0, num_dirs - 1)];
	len = strlen(p->letras);
	
	/* Restringimos los valores x_0 y y_0 posibles en funcion de la direccion de la palabra */
	p->x_0 = ran_int(0 + len * (p->dir == HOR_REV), (dim - 1) - len * (p->dir == HOR_DIR));
	p->y_0 = ran_int(0 + len * (p->dir == VER_REV), (dim - 1) - len * (p->dir == VER_DIR));
	return;
}

int ran_int(int min, int max) {
	return ((rand() % (max - min + 1)) + min);
}

bool comprobar_posicion_valida(sopa_t *j, palabra_t *p) {
	bool ret = true;
	int i = 0;
	while (p->letras[i] != '\0' && ret) {
		ret = j->letras[buscar_casilla(j->dim, p, i)] == CAR_VACIO;
		i++;
	}
	return ret;
}

int buscar_casilla(int dim, palabra_t *p, int i) {
	int d_hor, d_ver;

	/* Calcular desplazamientos a partir de direccion */
	switch (p->dir) {
		case HOR_DIR:
			d_hor = 1;
			d_ver = 0;
			break;
		case HOR_REV:
			d_hor = -1;
			d_ver = 0;
			break;
		case VER_DIR:
			d_hor = 0;
			d_ver = 1;
			break;
		case VER_REV:
			d_hor = 0;
			d_ver = -1;
			break;
	}

	return dim * (p->y_0 + i * d_ver) + (p->x_0 + i * d_hor);
}

void escribir_palabra(sopa_t *j, palabra_t *p) {
	int i = 0;

	while (p->letras[i] != '\0') {
		j->letras[buscar_casilla(j->dim, p, i)] = p->letras[i];
		i++;
	}
	return;
}

void rellenar_espacios_vacios(sopa_t *j) {
	int i, n;
	n = j->dim * j->dim;
	for (i = 0; i < n; i++)
		if (j->letras[i] == CAR_VACIO)
			j->letras[i] = ran_int('A', 'Z');
	return;
}

bool jugada_usuario(sopa_t *j) {
	bool ret;
	char input[MAX_PALABRA + 1];
	palabra_t *intento, *p;

	printf("Pon la palabra que has encontrado,\n"
			"o pon " RENDICION " para ver la solucion: ");
	leer_string(input);

	if (!strcmp(input, RENDICION)) {
		ret = true;
	}
	else {
		ret = false;
		p = encontrar_palabra_lista(j->pal_0, input);

		if (p == NULL) {
			COLOR_FG_ROJO();
			printf("La palabra no esta en la lista.\n");
			COLOR_DEFAULT();
		}
		else {
			intento = nueva_palabra(input);
			if (intento == NULL) {
				printf("Error asignacion memoria. Intentelo de nuevo.\n");
			}
			else {
				pedir_coordenadas(intento);
				if (comprobar_palabras_iguales(p, intento)) {
					marcar_acierto(j, p);
					j->n_aciertos++;
				}
				else {
					COLOR_FG_ROJO();
					printf("No has acertado.\n");
					COLOR_DEFAULT();
				}
			}
			free(intento);
		}
	}
	return ret;
}

void leer_string(char *s) {
	/* Leer como maximo MAX_PALABRA caracteres */
	scanf("%" TOSTR(MAX_PALABRA) "s", s);
	limpiar_stdin();
	return;
}

palabra_t *encontrar_palabra_lista(palabra_t *p, char *s) {
	while (p != NULL && strcmp(p->letras, s) != 0)
		p = p->sig;
	return p;
}

void pedir_coordenadas(palabra_t *p) {
	printf("En que fila empieza la palabra? ");
	p->y_0 = leer_numero() - 1;
	printf("En que columna empieza la palabra? ");
	p->x_0 = leer_numero() - 1;
	printf("En que direccion esta escrita la palabra?\n");
	mostrar_direcciones();
	p->dir = leer_numero();
	return;
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
	return (a->x_0 == b->x_0) && (a->y_0 == b->y_0) && (a->dir == b->dir);
}

void marcar_acierto(sopa_t *j, palabra_t *p) {
	marcar_letras_acertadas(j, p);
	eliminar_palabra_lista(j, p);
	return;
}

void marcar_letras_acertadas(sopa_t *j, palabra_t *p) {
	int i = 0;
	while (p->letras[i] != '\0') {
		j->aciertos[buscar_casilla(j->dim, p, i)] = true;
		i++;
	}
	return;
}

void eliminar_palabra_lista(sopa_t *j, palabra_t *p) {
	if (p->sig != NULL)
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
	return;
}

void liberar_palabras(palabra_t *p) {
	palabra_t *aux;
	while (p != NULL) {
		aux = p->sig;
		free(p);
		p = aux;
	}
	return;
}

void mostrar_sopa(sopa_t *j) {
	/* Usado codigo proporcionado */
	int i, k;

	/* Mostrar numeros de columna */
	COLOR_FG_ROJO();
	printf("\n\n  ");
	/* Decenas */
	for (i = 10; i < j->dim + 1; i+=10) {
		printf("                   %d", i/10);
	}
	/* Unidades */
	printf("\n  ");   
	for (i = 0; i < j->dim; i++)
		printf(" %d", (i + 1) % 10);
	printf("\n");
	COLOR_DEFAULT();


	/* Mostrar letras. Cada letra ocupa dos espacios: */
	/* Si esta encertada, se marca */
	for (i = 0; i < j->dim ; i++)
	{
		/* Mostrar numero de linia */
		COLOR_FG_ROJO();
		printf("%-2d", i + 1);
		COLOR_DEFAULT();

		/* Mostrar letras */
		for (k = 0; k < j->dim; k++) {
			if (j->aciertos[i * j->dim + k])
				COLOR_BG_VERDE();
			printf(" %c", j->letras[i * j->dim + k]);
			COLOR_DEFAULT();
		}
		printf("\n");
	}
	printf("\n");

	if (j->pal_0 != NULL) {
		printf("Llevas %d aciertos.\n", j->n_aciertos);
		mostrar_palabras(j->pal_0, j->n_palabras - j->n_aciertos);
	}
}

void felicitar_jugador() {
	printf("Enhorabuena! Has acertado todas las palabras!\n");
	return;
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

