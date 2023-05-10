#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sopa.h"

int main (int argc, char *argv[]) {
	sopa_t *j;
	palabra_t *pal_0;
	bool juego_finalizado, rendido;
	int n, dim;
	time_t seed;

	if (argc < 2) {
		printf("Pon el fichero con palabras como primer parametro.\n");
	}
	else {
		seed = time(NULL);
		srand(seed);
		printf("seed: %ld\n", seed);

		escribir_mensaje_bienvenida();
		pal_0 = leer_palabras(argv[1], &n);

		if (pal_0 == NULL) {
			printf("Error lectura palabras.\n");
		}
		else {
			mostrar_palabras(pal_0, n);
			dim = pedir_tamano_sopa(MIN_DIM, MAX_DIM);
			j = generar_sopa(dim, pal_0);

			if (j == NULL) {
				printf("Error generacion tabla.\n");
				liberar_palabras(pal_0);
			}
			else {
				do {
					mostrar_sopa(j);
					rendido = jugada_usuario(j);
					juego_finalizado = rendido || (j->pal_0 == NULL);
				} while (!juego_finalizado);

				if (rendido)
					mostrar_solucion(j);
				else {
					mostrar_sopa(j);
					felicitar_jugador();
				}

				liberar_memoria(j);
			}
		}
	}

	return 0;
}

