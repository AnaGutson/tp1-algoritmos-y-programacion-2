#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_generales.h"

#define DEFAULT 		3

/*** Pre y post condiciones en funciones_generales.h ***/
void mayusculizar_letra(char *letra){

    *letra = (char)toupper(*letra);
}

/*** Pre y post condiciones en funciones_generales.h ***/
bool es_consonante(char letra){

	mayusculizar_letra(&letra);

	return ( (letra != VOCAL_1) && (letra != VOCAL_2) && (letra != VOCAL_3)
		&& (letra != VOCAL_4) && (letra != VOCAL_5) );
}

/*** Pre y post condiciones en funciones_generales.h ***/
int cant_consonantes(char nombre[MAX_ESPECIE]){
	int largo, consonantes = 0;

	largo = (int)strlen(nombre);
	for(int i = 0; i < largo; i++){

		if(es_consonante(nombre[i]))
			consonantes++;
	}

	return consonantes;
}

/*** Pre y post condiciones en funciones_generales.h ***/
int cant_digitos(int valor){
	int digitos = 0;
	
	do{
		
		digitos++;
		valor/=DECENA;
	}while(valor != VALOR_NULO);
	
	return digitos;
}

/*** Pre y post condiciones en funciones_generales.h ***/
int cant_letras(char palabra[MAX_PALABRA]){

	return (int)strlen(palabra);
}

/*** Pre y post condiciones en funciones_generales.h ***/
int numero_random(int tope){
	
	return (rand()%tope + 1);
}

/*Pre-condiciones: 
	"texto_original", "texto_a_comparar", "donde_guardar" y "color" tienen tamaño mayor a 0 y menor a MAX_COLOR;
	"color" es un codigo para mostrar el color;
	"*i" es positivo;
	"*encontro_color" es false.
Post-condiciones: 
    la función actualiza "donde_guardar" de ser posible, con "color", además de actualizar el valor del puntero "*encontro_color";
    no solo eso, sino que la función siempre actualiza el valor del puntero "*i" incrementandolo en uno.*/
void definir_color(char texto_original[MAX_COLOR], const char texto_a_comparar[MAX_COLOR], char donde_guardar[MAX_COLOR], const char color[MAX_COLOR], int *i, bool *encontro_color){

	if(strcmp(texto_original, texto_a_comparar) == 0){

		strcpy(donde_guardar, color);
		*encontro_color = true;
	}
	(*i)++;
}

/*** Pre y post condiciones en funciones_generales.h ***/
void asumo_color(char texto[MAX_COLOR], char color[MAX_COLOR]){
	int i = 0;
	bool encontro_color = false;
	
	while((i < CANT_COLORES) && (!encontro_color))
		definir_color(texto, TEXTO_COLORES[i], color, CODIGO_COLORES[i], &i, &encontro_color);
	
	if(!encontro_color)
		strcpy(color, CODIGO_COLORES[DEFAULT]);
}

/*** Pre y post condiciones en funciones_generales.h ***/
int cant_espacios_4_datos(int caracteres_totales, int valor_1, int valor_2, char string_1[MAX_PALABRA], char string_2[MAX_PALABRA]){
	int digitos_valor_1, digitos_valor_2, largo_string_1, largo_string_2, espacios_sobrantes;
	
	largo_string_1 = cant_letras(string_1);
	digitos_valor_1 = cant_digitos(valor_1);
	digitos_valor_2 = cant_digitos(valor_2);
	largo_string_2 = cant_letras(string_2);
	espacios_sobrantes = caracteres_totales - (largo_string_1 + digitos_valor_1 + digitos_valor_2 + largo_string_2);
	
	return espacios_sobrantes;
}

/*** Pre y post condiciones en funciones_generales.h ***/
int cant_espacios_6_datos(int caracteres_totales, int valor_1, int valor_2, char string_1[MAX_PALABRA], char string_2[MAX_PALABRA], char string_3[MAX_PALABRA], char string_4[MAX_PALABRA]){
	int digitos_valor_1, digitos_valor_2, largo_string_1, largo_string_2, largo_string_3, largo_string_4, espacios_sobrantes;
	
	digitos_valor_1 = cant_digitos(valor_1);
	digitos_valor_2 = cant_digitos(valor_2);
	largo_string_1 = cant_letras(string_1);
	largo_string_2 = cant_letras(string_2);
	largo_string_3 = cant_letras(string_3);
	largo_string_4 = cant_letras(string_4);
	espacios_sobrantes = caracteres_totales - (digitos_valor_1 + digitos_valor_2 + largo_string_1 + largo_string_2 + largo_string_3 + largo_string_4);
	
	return espacios_sobrantes;
}

/*Pre-condiciones: 
    "pos" positivo - o cero - y menor a "cant_letras(palabra)".
Post-condiciones: 
    la función recursiva actualiza nueva_palabra a partir de palabra y vuelve a invocarse a si misma siempre y cuando "pos" sea mayor o igual a 0.*/
void palabra_invertida_aux(char palabra[MAX_PALABRA], int pos, char nueva_palabra[MAX_PALABRA]){
	int largo_original = cant_letras(palabra) - 1;

	if(pos >= 0){
		
		nueva_palabra[largo_original - pos] = palabra[pos];
		palabra_invertida_aux(palabra, (pos - 1), nueva_palabra);
	}
}

/*** Pre y post condiciones en funciones_generales.h ***/
void palabra_invertida(char palabra[MAX_PALABRA], char nueva_palabra[MAX_PALABRA]){
	int largo = cant_letras(palabra);
	
	palabra_invertida_aux(palabra, largo-1, nueva_palabra);
}