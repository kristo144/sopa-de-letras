void escribir_mensaje_bienvenida() {
}

palabra_t *leer_palabras(char *nombre_fichero, int *n_pal) {
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
			(strcmp(primera->sig->letras, nueva->letras < 0)))
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
}

int pedir_tamano_sopa(int min, int max) {
}

sopa_t *generar_sopa(int dim, palabra_t *p) {
}

void insertar_palabras(sopa_t *j) {
}

void insertar_palabra(sopa_t *j, palabra_t *p) {
}

void posicion_aleatoria(palabra_t *p, int dim) {
}

int ran_int(int min, int max) {
}

bool comprobar_posicion_valida(sopa_t *j, palabra_t *p) {
}

int buscar_casilla(int dim, palabra_t *p, int i) {
}

void escribir_palabra(sopa_t *j, palabra_t *p) {
	int i = 0;

	while (p->letras[i] != '\0') {
		j->letras[buscar_casilla(j->dim, p, i)] = p->letras[i];
		i++;
	}
}

void rellenar_espacios_vacios(sopa_t *j) {
}

bool jugada_usuario(sopa_t *j) {
	bool ret;
	char input[MAX_PALABRA + 1];
	palabra_t *intento, *p;

	printf("Pon la palabra que has encontrado,\n"
			"o pon " RENDICION " para ver la solucion:");
	scanf("%" #MAX_PALABRA "s", input);

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

palabra_t *encontrar_palabra_lista(palabra_t p, char *s) {
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
}

void marcar_acierto(sopa_t *j, palabra_t *p) {
}

void marcar_letras_acertadas(sopa_t *j, palabra_t *p) {
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
	while (j->p_0 != NULL) {
		marcar_acierto(j, j->p_0);
	}
	mostrar_sopa(j);
}

void liberar_palabras(palabra_t *p) {
}

void mostrar_sopa(sopa_t *j) {
}

void felicitar_jugador() {
}

void liberar_memoria(sopa_t *j) {
}

