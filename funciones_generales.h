#ifndef _FUNCIONES_GENERALES_H_
#define _FUNCIONES_GENERALES_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_ESPECIE 100
#define MAX_COLOR 50
#define MAX_PALABRA 100

#define VOCAL_1		'A'
#define VOCAL_2		'E'
#define VOCAL_3		'I'
#define VOCAL_4		'O'
#define VOCAL_5		'U'

#define DECENA 						10
#define VALOR_NULO					0

#define FIN  			"\033[0m"
#define NEGRO	 		"\033[0m\033[30m"
#define GRIS	 		"\033[1m\033[30m"
#define ROJO_OSCURO 	"\033[0m\033[31m"
#define ROJO_CLARO 		"\033[1m\033[31m"
#define VERDE_CLARO 	"\033[0m\033[32m"
#define VERDE_OSCURO 	"\033[1m\033[32m"
#define AMARILLO 		"\033[1m\033[33m"
#define MARRON	 		"\033[0m\033[33m"
#define AZUL_SUAVE 		"\033[0m\033[34m"
#define AZUL 			"\033[1m\033[34m"
#define MAGENTA_SUAVE	"\033[0m\033[35m"
#define MAGENTA 		"\033[1m\033[35m"
#define CELESTE_SUAVE	"\033[0m\033[36m"
#define CELESTE			"\033[1m\033[36m"
#define SILVER 			"\033[0m\033[37m"
#define BLANCO 			"\033[1m\033[37m"
#define CANT_COLORES	15

const static char TEXTO_COLORES[][MAX_COLOR] = {"negro", "azul", "amarillo", "blanco", "blanquirrojo", "rosa", "bermellon", "gris", "naranja", "marron",  "morado", "violeta", "rojo", "verde", "celeste"};
const static char CODIGO_COLORES[][MAX_COLOR] = {NEGRO, AZUL, AMARILLO, BLANCO, ROJO_CLARO, ROJO_CLARO, ROJO_CLARO, GRIS, MARRON, MARRON, MAGENTA, MAGENTA, ROJO_OSCURO, VERDE_OSCURO, CELESTE};

//GENERALES

/*Pre-condiciones:
	-
Post-condiciones:
	la función convierte en mayúscula "letra" si el mismo no lo estaba; si "letra" ya estaba en mayúscula, se devolverá el mismo valor.*/
void mayusculizar_letra(char *letra);

/*Pre-condiciones:
	-
Post-condiciones:
	la función retorna si la letra es diferente a todas las vocales. */
bool es_consonante(char letra);

/*Pre-condiciones:
	-
Post-condiciones:
	la función retorna cuántas posiciones de "nombre" son diferentes a todas las vocales. */
int cant_consonantes(char nombre[MAX_ESPECIE]);

/*Pre-condiciones: 
    "valor" positivo.
Post-condiciones: 
    la función devolverá la cantidad de digitos de "valor".*/
int cant_digitos(int valor);

/*Pre-condiciones:
	"palabra" es diferente a "".
Post-condiciones:
	la función retorna cuántas posiciones tiene palabra antes del primer CARACTER_NULO. */
int cant_letras(char palabra[MAX_PALABRA]);

/*Pre-condiciones: 
    "tope" debe ser mayor a 0;
Post-condiciones: 
    la función retornará un valor entre 1 y "tope".*/
int numero_random(int tope);

/*Pre-condiciones: 
	"texto" y "color" tienen tamaño mayor a 0 y menor a MAX_COLOR.
Post-condiciones: 
    la función actualiza "color" de ser posible, con alguna posición de "CODIGO_COLORES".*/
void asumo_color(char texto[MAX_COLOR], char color[MAX_COLOR]);

/*Pre-condiciones: 
	"caracteres_totales" es mayor a 0;
	"valor_1" es mayor a 0;
	"valor_2" es mayor a 0;
	"string_1" es diferente a "";
	"string_2" es diferente a "".
Post-condiciones: 
    la función devuelve el valor obtenido al realizar una operación matemática.*/
int cant_espacios_4_datos(int caracteres_totales, int valor_1, int valor_2, char string_1[MAX_PALABRA], char string_2[MAX_PALABRA]);

/*Pre-condiciones: 
	"caracteres_totales" es mayor a 0;
	"valor_1" es mayor a 0;
	"valor_2" es mayor a 0;
	"string_1" es diferente a "";
	"string_2" es diferente a "";
	"string_3" es diferente a "";
	"string_4" es diferente a "".
Post-condiciones: 
    la función devuelve el valor obtenido al realizar una operación matemática.*/
int cant_espacios_6_datos(int caracteres_totales, int valor_1, int valor_2, char string_1[MAX_PALABRA], char string_2[MAX_PALABRA], char string_3[MAX_PALABRA], char string_4[MAX_PALABRA]);

/*Pre-condiciones: 
    "palabra" es diferente a "".
Post-condiciones: 
    la función actualiza el valor de nueva_palabra.*/
void palabra_invertida(char palabra[MAX_PALABRA], char nueva_palabra[MAX_PALABRA]);

#endif /* _FUNCIONES_GENERALES_H_ */
