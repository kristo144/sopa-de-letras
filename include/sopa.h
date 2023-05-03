#include <stdbool.h>

#define MAX_PALABRA 8
#define MIN_PALABRA 4
#define MAX_PALABRAS 10

#define MIN_DIM 10
#define MAX_DIM 40

#define RENDICION "RENDICIO"

#define HOR_DIR 1
#define HOR_REV -1
#define VER_DIR 2
#define VER_REV -2

#define CAR_VACIO '\0'

typedef struct {
	char lletres[MAX_PALABRA + 1];
	bool acertada;
	int x_0, y_0, dir;
	paraula_t *sig, *ant;
} palabra_t;

typedef struct {
	int dim, n_palabras, n_aciertos;
	char *letras;
	bool *aciertos;
	paraula_t *pal_0;
} sopa_t;

/*
   Escribir mensaje de bienvenida. Muestra los nombres de los autores.
*/
void escribir_mensaje_bienvenida();

/*
   Lee palabras de un fichero, las guarda de forma ordenada en una lista enlazada
   de tipo palabra_t, y cuenta el numero de palabras leidas.
   @param nombre_fichero (Ref (E): puntero a caracter). Nombre del fichero del cual leer.
   @paran n_pal (Ref (E): entero). Salida, numero de palabras leidas
   @return Puntero de tipo palabra_t que apunta a la primera palabra de la lista.
   En caso de error, retorna NULL.
*/
palabra_t *leer_palabras(char *nombre_fichero, int *n_pal);

/*
   Crea una estructura palabra_t con la palabra dada.
   Los miembros sig y ant seran NULL.
   Se copiaran como maximo MAX_PALABRA + 1 caracteres de la palabra.
   No se garantiza terminacion en nulo.
   @param s (Ref (E): puntero a caracter). Letras de la palabra a crear.
   @return Puntero al nuevo palabra_t.
   En caso de error, retorna NULL
*/
palabra_t *nueva_palabra(char *s);

/*
   Dada una lista de palabra_t, insertar un elemento nuevo en orden alfabetico.
   @param primera (Ref (E): palabra_t). Primer elemento de la lista.
   @param nueva (Ref (E): palabra_t). Elemento a insertar.
*/
void insertar_palabra_en_lista(palabra_t *primera, palabra_t *nueva);

/*
   Inserta el elemento b después del elemento a en una lista de palabra_t.
   @param a (Ref (E): palabra_t). Elemento referencia.
   @param b (Ref (E): palabra_t). Elemento nuevo.
*/
void insertar_despues(palabra_t *a, palabra_t *b);

/*
   Muestra las palabras de una lista de palabra_t, y el numero total de palabras.
   @param p (Ref (E): palabra_t). Primera palabra de la lista.
   @param n (Val (E): entero). Numero total de palabras)
*/
void mostrar_palabras (palabra_t *p, int n);

/*
   Pida al usuario por teclado un tamano para la sopa de letras.
   El tamano debe ser entre un minimo y un maximo, ambos incluidos.
   Bloquea hasta tener un input valido.
   @param min (Val (E): entero). Dimension minima.
   @param max (Val (E): entero). Dimension maxima.
   @return Dimension elegida.
   Se garantiza que (ret <= max && ret >= min)
*/
int pedir_tamano_sopa(int min, int max);

/*
   Crea una nueva estructura sopa_t, con la dimension y lista de palabras dadas.
   Genera y popula el tablero.
   @param dim (Val (E): entero). Dimension tabla.
   @param p (Ref (E): palabra_t). Lista de palabras.
   @ret Puntero a la estructura creada.
   En caso de error, retorna NULL
*/
sopa_t *generar_sopa(int dim, palabra_t *p);

/*
   Dada una estructura sopa_t con lista de palabras,
   escribe las palabras en el tablero en posiciones aleatorias.
   @param j (Ref (E): sopa_t). La sopa.
*/
void insertar_palabras(sopa_t *j);

/*
   Dada una estructura sopa_t y una palabra_t
   escribe la palabra en el tablero en una posicion aleatoria disponible.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
*/
void insertar_palabra(sopa_t *j, palabra_t *p);

/*
   Dada una estructura palabra_t, genera una posicion y orientacion
   aleatoria y valida para una tabla de dimension dim.
   @param p (Ref (E): palabra_t). La palabra.
   @param dim (Val (E): int). Dimension de la tabla.
*/
void posicion_aleatoria(palabra_t *p, int dim);

/*
   Genera un entero aleatorio entre un maximo y un minimo, ambos incluidos.
   @param min (Val (E): entero). Minimo
   @param max (Val (E): entero). Maximo
   @return Valor aleatorio tal que (ret >= min && ret <= max)
*/
int ran_int(int min, int max);

/*
   Dada una estructura sopa_t y una palabra_t, comprobar que la palabra se puede
   escribir en la posicion deseada en el tablero de la sopa.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
   @return Cierto si se puede escribir, falso si no.
*/
bool comprobar_posicion_valida(sopa_t *j, palabra_t *p);

/*
   Retorna el desplazamiento desde la posicion 0 de la letra i-esima de una palabra
   en una tabla de dimension dim.
   @param dim (Val (E): entero). Dimension de la tabla.
   @param p (Ref (E): palabra_t). La palabra.
   @param i (Val (E): entero). Indice de la letra de la palabra.
   @return Posicion de la letra deseada relativa al (0,0)
*/
int buscar_casilla(int dim, palabra_t *p, int i);

/*
   Escribir las letras de una palabra_t en las posiciones indicadas en el tablero
   de una sopa_t.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
*/
void escribir_palabra(sopa_t *j, palabra_t *p);

/*
   Rellenar espacios vacios del tablero de una sopa_t con letras mayusculas aleatorias.
   @param j (Ref (E): sopa_t). La sopa.
*/
void rellenar_espacios_vacios(sopa_t *j);

/*
   Pedir, validar y marcar la jugada de un usuario.
   @param j (Ref (E): sopa_t). La sopa.
   @return Cierto si el usuario se rinde, falso si no
*/
bool jugada_usuario(sopa_t *j);

/*
   Buscar una palabra en una lista de palabra_t.
   @param p (Ref (E): palabra_t). Lista de palabras.
   @param s (Ref (E): tabla[] de caracter). Palabra buscada
   @return Puntero al primer elemento en que coincide la palabra.
   Si no se encuentra la palabra, retorna NULL
*/
palabra_t *encontrar_palabra_lista(palabra_t p, char *s);

/*
   Pedir coordenadas y direccion de la palabra encontrada por teclado.
   Guardarlas en una estructura palabra_t.
   @param p (Ref (E): palabra_t). Palabra donde guardar las coordenadas.
*/
void pedir_coordenadas(palabra_t *p);

/*
   Comprobar si dos palabra_t tienen coordenadas y direccion identicas.
   @param a (Ref (E): palabra_t). Una de las palabras.
   @param b (Ref (E): palabra_t). La otra palabra.
   @return Cierto si son iguales, falso si no.
*/
bool comprobar_palabras_iguales(palabra_t *a, palabra_t *b);

/*
   Marcar palabra como acertada en una sopa.
   Elimina la palabra de su lista y libra su memoria.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
*/
void marcar_acierto(sopa_t *j, palabra_t *p);

/*
   Marcar las letras de una palabra como acertada.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
*/
void marcar_letras_acertadas(sopa_t *j, palabra_t *p);

/*
   Eliminar una palabra de una lista y liberar su memoria.
   @param j (Ref (E): sopa_t). La sopa.
   @param p (Ref (E): palabra_t). La palabra.
*/
void eliminar_palabra_lista(sopa_t *j, palabra_t *p);

/*
   Marca todas las palabras de una sopa como acertadas y muestra la tabla.
   @param j (Ref (E): sopa_t). La sopa.
*/
void mostrar_solucion(sopa_t *j);

/*
   Eliminar una lista de palabras entera y liberar su memoria.
   Si la lista es NULL, no hace nada.
   @param p (Ref (E): palabra_t). La lista de palabras.
*/
void liberar_palabras(palabra_t *p);

/*
   Mostrar el tablero de la sopa y las palabras que quedan por encontrar
   @param j (Ref (E): sopa_t). La sopa.
*/
void mostrar_sopa(sopa_t *j);

/*
   Mostrar mensaje de enhorabuena al jugador.
*/
void felicitar_jugador();

/*
   Liberar memoria de una sopa. Si la sopa es NULL, no hace nada.
   @param j (Ref (E): sopa_t). La sopa.
*/
void liberar_memoria(sopa_t *j);

