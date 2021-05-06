#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

#define VERDE_CLARO 	"\033[0m\033[32m"
#define VERDE_OSCURO 	"\033[1m\033[32m"
#define FIN  			"\033[0m"
#define LINEA 			"\n-------------------------------------------------\n"
#define AMARILLO 		"\033[1m\033[33m"
#define BLANCO 			"\033[1m\033[37m"
#define SILVER 			"\033[0m\033[37m"
#define ROJO_CLARO 		"\033[1m\033[31m"
#define AZUL 			"\033[1m\033[34m"
#define MAGENTA 		"\033[1m\033[35m"
#define GRIS	 		"\033[1m\033[30m"

#define MAX_PALABRA 				100

#define LEER 						"r"
#define ESCRIBIR 					"w"
#define FORMATO_ARRECIFE 			"%[^;];%i;%i;%[^\n]\n"
#define FORMATO_ACUARIO 			"%s;%i;%i;%s\n"
#define EXTENSION_ARCHIVO_TEXTO		".txt"
#define PUNTO 						'.'
#define MAX_NOMBRE_ARCHIVO 			100
#define MAX_EXTENSION_ARCHIVO 		4
#define CARACTER_VACIO				'\0'

#define CANT_FORMATO_ARRECIFE 	4

#define TODO_OK		0
#define ERROR		-1
#define LEYO_MAL	CANT_FORMATO_ARRECIFE-1


//------------------------------------MENSAJES ERROR

/*Pre-condiciones:
	-.
Post-condiciones:
	la función muestra un mensaje de error. */
void mostrar_error_realloc(){

	printf(ROJO_CLARO"Ocurrio un error inesperado al realizar un realloc\n"FIN);
}

/*Pre-condiciones:
	-.
Post-condiciones:
	la función muestra un mensaje de error. */
void mostrar_error_malloc(){

	printf(ROJO_CLARO"Ocurrio un error inesperado al realizar un malloc\n"FIN);
}

/*Pre-condiciones:
	-.
Post-condiciones:
	la función muestra un mensaje de error. */
void mostrar_error_archivo(){

	printf(ROJO_CLARO"Ocurrio un error inesperado al trabajar con un archivo\n"FIN);
}

/*Pre-condiciones:
	-.
Post-condiciones:
	la función muestra un mensaje de error. */
void mostrar_puso_cualquiera(){

	printf(ROJO_CLARO"Che, hiciste cualquier cosa, ojito que me rompes todo.\n"FIN);
}

//------------------------------------FUNCIONES GENERALES

/*Pre-condiciones:
	"palabra" es diferente a "".
Post-condiciones:
	la función retorna cuántas posiciones tiene palabra antes del primer CARACTER_NULO. */
static int cant_letras(char palabra[MAX_PALABRA]){ //LA HICE STATIC PORQUE PARA PROBARLO USTEDES NO ME DEJAN USAR FUNCIONES DE OTRA BIBLIOTECA MÍA EN EVENTO_PESCA.C 

	return (int)strlen(palabra);
}

//------------------------------------VERIFICACIONES

/*Pre-condiciones: 
	-.
Post-condiciones: 
    la función retorna si se cumplen todas las condiciones.*/
bool parametros_validos(char especie[], char color[], int velocidad, int peso){

	return ((cant_letras(especie) < MAX_ESPECIE) && (cant_letras(color) < MAX_COLOR)
		&& (velocidad > 0) && (peso > 0));
}

/*Pre-condiciones: 
    "extension" debe ser EXTENSION_ARCHIVOS_TEXTO.
Post-condiciones: 
    la función retorna si el nombre del archivo es igual a '."extension"'.*/
bool primera_parte_vacia(const char nombre_archivo[MAX_NOMBRE_ARCHIVO], char extension[MAX_EXTENSION_ARCHIVO]){
	char comparacion[MAX_NOMBRE_ARCHIVO]={CARACTER_VACIO};
	
	comparacion[0] = PUNTO;
	strcat(comparacion, extension);

	return (strncmp(comparacion, nombre_archivo, strlen(comparacion)) == 0);
}

/*Pre-condiciones: 
    "extension" debe ser EXTENSION_ARCHIVOS_TEXTO.
Post-condiciones: 
    la función retorna si la terminación del argumento es igual a "extension".*/
bool es_archivo_valido_segun_extension(const char argumento[MAX_NOMBRE_ARCHIVO], char extension[MAX_EXTENSION_ARCHIVO]){
	size_t largo_archivo, largo_extension;
	bool valido = false;

	largo_archivo = strlen(argumento);
	largo_extension = strlen(extension);

	if(largo_archivo > largo_extension)
		valido = (strcmp(&argumento[largo_archivo-largo_extension], extension) == 0);

	return valido;
}

/*Pre-condiciones: 
	"extension" debe ser EXTENSION_ARCHIVOS_TEXTO.
Post-condiciones:
	la función retorna si el archivo es correcto.*/
bool nombre_archivo_ingresado_correcto(const char ruta[MAX_NOMBRE_ARCHIVO], char extension[MAX_EXTENSION_ARCHIVO]){
	bool correcto;

	correcto = ( es_archivo_valido_segun_extension(ruta, extension) && !primera_parte_vacia(ruta, extension) );

	if(!correcto)
		mostrar_puso_cualquiera();

	return correcto;
}

/*Pre-condiciones:
	-.
Post-condiciones:
	la función retornará si "leidos" es igual a CANT_FORMATO_ARRECIFE.*/
bool lee_bien(int leidos){

	return (leidos == CANT_FORMATO_ARRECIFE);
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función retornará si el archivo se pudo abrir para leer y en caso de no poderse mostrará un mensaje de error.*/
static bool archivo_existe(const char archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* archivo_nuevo;
	bool existe = true;

	archivo_nuevo = fopen(archivo, LEER);

	if(!archivo_nuevo){

		mostrar_error_archivo();
		existe = false;
	}
	else
		fclose(archivo_nuevo);
	
	return existe;
}

/* Pre-condiciones:
	"*archivo_arrecife" debe estar correctamente abierto.
Post-condiciones:
	la función actualiza "*pokemon_leido" con lo leido de "*archivo_arrecife";
	la funcion retorna cuantos campos pudo leer bien:
		cumpliendo con lo establecido en la última condición.*/
int lectura_pokemon(FILE* archivo_arrecife, pokemon_t *pokemon_leido){
	int leidos;

	leidos = fscanf(archivo_arrecife, FORMATO_ARRECIFE, pokemon_leido->especie, &(pokemon_leido->velocidad), &(pokemon_leido->peso), pokemon_leido->color);

	if((leidos == CANT_FORMATO_ARRECIFE) && !parametros_validos(pokemon_leido->especie, pokemon_leido->color, pokemon_leido->velocidad, pokemon_leido->peso))
		leidos = LEYO_MAL;

	return leidos;
} 

/* Pre-condiciones:
	"pokemon_leido" debe tener todas sus campos válidos:
    	"pokemon_leido.especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon_leido.peso" debe ser positivo;
    	"pokemon_leido.velocidad" debe ser positivo;
		"pokemon_leido.color" debe tener un tamaño menor a MAX_COLOR y mayor a 0;
	"*puntero" debe tener todas sus campos válidos:
    	"puntero->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"puntero->peso" debe ser positivo;
    	"puntero->velocidad" debe ser positivo;
		"puntero->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0;
	"*posicion" deber ser mayor o igual a 0;
    "*retorno" debe ser ERROR o TODO_OK.
Post-condiciones:
	la función mueve "pokemon_leido" a la ultima posicion de "*puntero", ademas de actualizar "*posicion" y "*retorno" de ser posible;
	la funcion retorna puntero.*/
pokemon_t* agregar_pokemon(pokemon_t pokemon_leido, pokemon_t* puntero, int *posicion, int *retorno){

	if(*retorno == TODO_OK){

		pokemon_t* nuevo_puntero = NULL;
		nuevo_puntero = realloc(puntero, sizeof(pokemon_t)*(size_t)(*posicion + 1));
		if(!nuevo_puntero){

			mostrar_error_realloc();
			*retorno = false;
			return NULL;
		}
		puntero = nuevo_puntero;
		puntero[*posicion] = pokemon_leido;
		(*posicion)++;
	}

	return puntero;
}

/* Pre-condiciones:
	"*arrecife" es diferente a NULL.
Post-condiciones:
	la función actualiza el valor de sus campos por valores válidos;
	la funcion devuelve arrecife.*/
arrecife_t* inicializo_arrecife(arrecife_t* arrecife){

	arrecife->cantidad_pokemon = 0;
	arrecife->pokemon = NULL;

	return arrecife;
}

/*** Pre y post condiciones en evento_pesca.h ***/
arrecife_t* crear_arrecife(const char* ruta_archivo){
	arrecife_t* arrecife = NULL;
	pokemon_t pokemon_leido;
	int leidos, retorno = TODO_OK;
	FILE* archivo_arrecife;

	if(nombre_archivo_ingresado_correcto(ruta_archivo, EXTENSION_ARCHIVO_TEXTO) && archivo_existe(ruta_archivo)){
		
		archivo_arrecife = fopen(ruta_archivo, LEER);
		arrecife = malloc(sizeof(arrecife_t));
		if(arrecife){

			arrecife = inicializo_arrecife(arrecife);
			leidos = lectura_pokemon(archivo_arrecife, &pokemon_leido);
			if(lee_bien(leidos)){

				while(lee_bien(leidos) && (retorno == TODO_OK)){//Cuando falle el agregar pokemon o falle la lectura, termina

					arrecife->pokemon = agregar_pokemon(pokemon_leido, arrecife->pokemon, &(arrecife->cantidad_pokemon), &retorno);
					leidos = lectura_pokemon(archivo_arrecife, &pokemon_leido);
				}
			}
			else{

				liberar_arrecife(arrecife);
				mostrar_puso_cualquiera();
				fclose(archivo_arrecife);
				return NULL;
			}
		}
		else
			mostrar_error_realloc();
		fclose(archivo_arrecife);
	}

	return arrecife;
}

/* Pre-condiciones:
	"*acuario" es diferente a NULL.
Post-condiciones:
	la función actualiza el valor de sus campos por valores válidos;
	la funcion devuelve acuario.*/
acuario_t* inicializo_acuario(acuario_t* acuario){

	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;

	return acuario;
}

/*** Pre y post condiciones en evento_pesca.h ***/
acuario_t* crear_acuario(){
	acuario_t* acuario;
	
	acuario = malloc(sizeof(acuario_t));
	if(acuario)
		acuario = inicializo_acuario(acuario);
	else
		mostrar_error_realloc();

	return acuario;
}

/* Pre-condiciones:
	"*arrecife" tiene todos sus campos válidos:
    	"arrecife->pokemon" debe tener todos sus campos válidos;
    		"(arrecife->pokemon)->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    		"(arrecife->pokemon)->peso" debe ser positivo;
    		"(arrecife->pokemon)->velocidad" debe ser positivo;
			"(arrecife->pokemon)->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
    	"arrecife->cant_pokemon" debe ser positivo.
    "posicion" deber ser mayor o igual a 0;
Post-condiciones:
	la función elimina ordenadamente arrecife->pokemon[posicion];
	la función actualiza el valor de "arrecife->cantidad_pokemon";
	la funcion devuelve arrecife.*/
arrecife_t* actualizar_arrecife(arrecife_t* arrecife, int posicion){

	while(posicion < ((arrecife->cantidad_pokemon) - 1)){ //ACLARAR EN EL READ ME QUE LO HAGO ASÍ PORQUE ME GUSTA ELIMINAR ASÍ

		arrecife->pokemon[posicion] = arrecife->pokemon[posicion+1]; 
		posicion++;
	}
	(arrecife->cantidad_pokemon)--;

	return arrecife;
}

/* Pre-condiciones:
	"*arrecife" tiene todos sus campos válidos:
    	"arrecife->pokemon" debe tener todos sus campos válidos;
    		"(arrecife->pokemon)->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    		"(arrecife->pokemon)->peso" debe ser positivo;
    		"(arrecife->pokemon)->velocidad" debe ser positivo;
			"(arrecife->pokemon)->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
    	"arrecife->cant_pokemon" debe ser positivo.
    "posicion" deber ser mayor o igual a 0;
    "*retorno" debe ser ERROR o TODO_OK.
Post-condiciones:
	la función elimina ordenadamente arrecife->pokemon[posicion];
	la funcion, si "arrecife->cantidad_pokemon" != 0, achica el tamaño del puntero, y si no logra hacerlo devuelve NULL y actualiza "*retorno";
	la funcion retorna arrecife.*/
arrecife_t* eliminar_pokemon(arrecife_t* arrecife, int posicion, int *retorno){
	
	arrecife = actualizar_arrecife(arrecife, posicion);

	if(arrecife->cantidad_pokemon > 0){
		pokemon_t* nuevo_puntero = realloc(arrecife->pokemon, sizeof(pokemon_t)*(size_t)arrecife->cantidad_pokemon -1);
	
		if(nuevo_puntero == NULL){

			mostrar_error_realloc();
			*retorno = ERROR;
			return NULL;
		}
		arrecife->pokemon = nuevo_puntero;
	}

	return arrecife;
}

/* Pre-condiciones:
	"*pokemon_leido" debe tener todas sus campos válidos:
    	"pokemon_leido->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon_leido->peso" debe ser positivo;
    	"pokemon_leido->velocidad" debe ser positivo;
		"pokemon_leido->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0;
	"*acuario" tiene todos sus campos válidos:
    	"acuario->pokemon" debe tener todos sus campos válidos;
    		"(acuario->pokemon)->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    		"(acuario->pokemon)->peso" debe ser positivo;
    		"(acuario->pokemon)->velocidad" debe ser positivo;
			"(acuario->pokemon)->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
    	"acuario->cant_pokemon" debe ser positivo.
    "*posicion" deber ser mayor o igual a 0;
    "*retorno" debe ser ERROR o TODO_OK;
    "trasladados" debe ser mayor o igual a 0 y menor o igual a acuario->cant_pokemon.
Post-condiciones:
	la función mueve "pokemon_leido" a la ultima posicion de "acuario->pokemon", ademas de actualizar "*trasladados" y "*posicion" de ser posible;
	la funcion retorna acuario->pokemon.*/
pokemon_t* agregar_al_acuario(pokemon_t pokemon_leido, acuario_t* acuario, int *posicion, int *retorno, int *trasladados){

	acuario->pokemon = agregar_pokemon(pokemon_leido, acuario->pokemon, posicion, retorno);
	if(*retorno == TODO_OK)
		(*trasladados)++;

	return acuario->pokemon;
}

/*** Pre y post condiciones en evento_pesca.h ***/
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool(*es_seleccionable)(pokemon_t*), int cant_seleccion){
	int retorno = TODO_OK, i = 0, trasladados = 0;

	if(arrecife->cantidad_pokemon < cant_seleccion)
		retorno = ERROR;
	else{

		while((i < (arrecife->cantidad_pokemon)) && (trasladados < cant_seleccion)){

			if(es_seleccionable(&(arrecife->pokemon[i])))
				trasladados++;
			i++;
		}
		if(trasladados < cant_seleccion)
			retorno = ERROR;
		else{

			i = 0;
			trasladados = 0;
			while((i < arrecife->cantidad_pokemon) && (trasladados < cant_seleccion) && (retorno == TODO_OK)){

				if(es_seleccionable(&(arrecife->pokemon[i]))){
					
					arrecife = eliminar_pokemon(arrecife, i, &retorno);
					acuario->pokemon = agregar_al_acuario(arrecife->pokemon[i], acuario, &(acuario->cantidad_pokemon), &retorno, &trasladados);
				}
				else
					i++;
			}
		}
	}

	return retorno;
}

/*** Pre y post condiciones en evento_pesca.h ***/
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){

	for(int i = 0; i < arrecife->cantidad_pokemon; i++)
		mostrar_pokemon(&(arrecife->pokemon[i]));
}

/* Pre-condiciones:
	"*pokemon" debe tener todas sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones:
	la función escribe la información de "*pokemon" en el archivo.*/
void escribir_pokemon(FILE* archivo_acuario, pokemon_t* pokemon){

	fprintf(archivo_acuario, FORMATO_ACUARIO, pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

/*** Pre y post condiciones en evento_pesca.h ***/
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	int retorno = TODO_OK;
	FILE* archivo_acuario;

	if(nombre_archivo_ingresado_correcto(nombre_archivo, EXTENSION_ARCHIVO_TEXTO) && (acuario->cantidad_pokemon > 0)){

		archivo_acuario = fopen(nombre_archivo, ESCRIBIR);
		if(archivo_acuario){

			for(int i = 0; i < acuario->cantidad_pokemon; i++)
				escribir_pokemon(archivo_acuario, &(acuario->pokemon[i]));
			fclose(archivo_acuario);
		}
		else
			retorno = ERROR;
	}

	return retorno;
}

/*** Pre y post condiciones en evento_pesca.h ***/
void liberar_acuario(acuario_t* acuario){
	
	if(acuario){
		
		free(acuario->pokemon);
		free(acuario);
	}
}

/*** Pre y post condiciones en evento_pesca.h ***/
void liberar_arrecife(arrecife_t* arrecife){

	if(arrecife){
		
		free(arrecife->pokemon);
		free(arrecife);
	}
}