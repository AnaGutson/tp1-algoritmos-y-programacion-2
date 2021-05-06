#ifndef _EVENTO_PESCA_H_
#define _EVENTO_PESCA_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_ESPECIE 100
#define MAX_COLOR 50
#define MAX_PALABRA 100

typedef struct pokemon{
  char especie[MAX_ESPECIE];
  int velocidad;
  int peso;
  char color[MAX_COLOR];
} pokemon_t;

typedef struct acuario{
  pokemon_t* pokemon;
  int cantidad_pokemon;
} acuario_t;

typedef struct arrecife{
  pokemon_t* pokemon;
  int cantidad_pokemon;
} arrecife_t;

/*
 * Función que dado un archivo carga los pokémon que viven en el arrecife
 * reservando la memoria necesaria para el mismo. Se debe intentar leer la mayor
 * cantidad posible de registros del archivo. Al encontrar el primer registro
 * erróneo (o al llegar al final del archivo) se deben finalizar la lectura y
 * crear el arrecife con los pokémon leídos exitosamente. En caso de no
 * encontrar ningún registro con el formato correcto, se debe devolver error.
 * Devuelve un puntero a un arrecife válido o NULL en caso de error.
 */
/*Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para un arrecife, a partir de la lectura del
		archivo llamado "*ruta_archivo". En caso de no poderse realizar se devolvera NULL.*/
arrecife_t* crear_arrecife(const char* ruta_archivo);

/*
 * Función que crea un acuario vacío reservando la memoria necesaria para el mismo.
 * Devuelve el acuario o NULL en caso de error.
 */
/*Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para un acuario.
		En caso de no poderse realizar se devolvera NULL.*/
acuario_t* crear_acuario();

/*
 * Función que deberá sacar del arrecife a todos los pokémon que satisfagan la
 * condición dada por el puntero a función (que devuelvan true) y trasladarlos
 * hacia el acuario. El parámetro cant_seleccion especifica la cantidad máxima
 * de pokémon que serán trasladados. En caso de que haya menos pokémon trasladables en el
 * arrecife que los pedidos, no se deberá mover ninguno para conservar los pocos existentes.
 * El vector de pokemones del arrecife quedará solo con aquellos que no fueron
 * trasladados (su tamaño se ajustará luego de cada traslado).
 * El vector de pokemones del acuarió quedará con aquellos que fueron
 * trasladados esta vez más los que ya había en el
 * acuario (su tamaño se ajustará luego de cada traslado).
 * Devuelve -1 en caso de error o 0 en caso contrario.
 */
/*Pre-condiciones:
	"*arrecife" y "*acuario" deben ser estructuras válidas y diferentes a NULL;
	"seleccionar_pokemon" tiene que ser una función existente, es decir:
		"es_trabalenguas", "momento_lineal_al_tope", "es_farandu", "parece_acaudalado" o "no_curso_fisica";
	"cant_seleccion" es un valor entre 0 y arrecife->cantidad_pokemon. 
Post-condiciones:
	la función mueve de ser posible pokemones del arrecife al acuario. Devuelve TODO_OK si sale bien o ERROR si hay errores.*/
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion);

/* 
 * Procedimiento que dado un arrecife deberá mostrar por pantalla a todos los pokemon que contiene.
 */
/* Pre-condiciones:
	"*arrecife" debe ser una estructura válida y diferente a NULL;
	"mostrar_pokemon" tiene que ser una función existente, es decir:
		"mostrar_consonantes", "mostrar_momento_lineal", "mostrar_farandu", "mostrar_cheto", "mostrar_fisica" o "mostrar_todos".
Post-condiciones:
	la función muestra la información de los arrecife->pokemon de una forma determinada segun "mostrar_pokemon".*/
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*));

/*
 * Función que dado un acuario guarda en un archivo de texto a los pokemones que contiene.
 * Devuelve 0 si se realizo con éxito o -1 si hubo algun problema para guardar el archivo.
 */
/* Pre-condiciones:
	"*acuario" debe ser una estructura válida y diferente a NULL.
Post-condiciones:
	la función escribe la información de acuario->pokemon en el archivo.*/
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo);

/*
 * Libera la memoria que fue reservada para el acuario.
 */
/* Pre-condiciones:
	-.
Post-condiciones:
	la función libera la memoria utilizada por "acuario" y por "acuario->pokemon".*/
void liberar_acuario(acuario_t* acuario);

/*
 * Libera la memoria que fue reservada para el arrecife.
 */
/* Pre-condiciones:
	-.
Post-condiciones:
	la función libera la memoria utilizada por "arrecife" y por "arrecife->pokemon".*/
void liberar_arrecife(arrecife_t* arrecife);

#endif /* EVENTO_PESCA_H */