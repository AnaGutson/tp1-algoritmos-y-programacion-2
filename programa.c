#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "evento_pesca.h"
#include "funciones_generales.h"

#define NOMBRE_ARCHIVO_ARRECIFE 		"arrecife.txt"
#define NOMBRE_ARCHIVO_ACUARIO			"acuario.txt" 
#define MAX_FUNCIONES_SELECCIONABLES 	5
#define MAX_FUNCIONES_MOSTRAR		 	6
#define VALOR_INICIAL				 (MAX_FUNCIONES_MOSTRAR-1)

#define ESPACIO 		" "
#define CARACTER_VACIO  '\0'

#define COLOR_MAS_LINDO 			"azul"
#define SEGUNDO_COLOR_MAS_LINDO 	"verde"

#define COLOR_MAS_BRILLOSO 			"amarillo"//creo que no hay dorado
#define SEGUNDO_COLOR_MAS_BRILLOSO 	"plateado"
#define TERCER_COLOR_MAS_BRILLOSO 	"blanquirrojo"//no es brilloso pero suena cheto así que aplica

#define MIN_LETRAS_NOMBRE_LARGO		10 
#define MAX_PESO_FLACO				80
#define MIN_RAPIDO					60
#define MIN_MUCHO_PESO				200
#define MIN_MUCHA_VELOCIDAD			200
#define VELOCIDAD_LUZ				300
#define GRAVEDAD					10

#define CARACTERES_PRIMERA_PARTE_MOSTRAR_CONSONANTES 	53
#define CARACTERES_SEGUNDA_PARTE_MOSTRAR_CONSONANTES 	47
#define CARACTERES_MOSTRAR_CHETO						48

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

#define INICIO 			8

//-------------------------------------------------------------------------------------------VERIFICACIONES

/*Pre-condiciones: 
    "peso" debe ser positivo.
Post-condiciones: 
    la función retorna si "peso" es menor o igual a MAX_PESO_FLACO.*/
bool hace_ejercicio(int peso){

	return (peso <= MAX_PESO_FLACO);
}

/*Pre-condiciones: 
    "color" debe tener un tamaño positivo y menor a MAX_COLOR.
Post-condiciones: 
    la función retorna si "color" es igual a COLOR_MÁS_LINDO o a SEGUNDO_COLOR_MAS_LINDO.*/
bool es_lindo(char color[MAX_COLOR]){

	return ( (strcmp(color, COLOR_MAS_LINDO) == 0) || (strcmp(color, SEGUNDO_COLOR_MAS_LINDO) == 0) );
}

/*Pre-condiciones: 
    "velocidad" debe ser positivo.
Post-condiciones: 
    la función retorna si "velocidad" es mayor o igual a MIN_RAPIDO.*/
bool es_rapido(int velocidad){

	return (velocidad >= MIN_RAPIDO);
}

/*Pre-condiciones: 
    "peso" debe ser positivo.
Post-condiciones: 
    la función retorna si "peso" es mayor o igual a MIN_MUCHO_PESO.*/
bool es_grandote(int peso){

	return (peso >= MIN_MUCHO_PESO);
}

/*Pre-condiciones: 
    "color" debe tener un tamaño positivo y menor a MAX_COLOR.
Post-condiciones: 
    la función retorna si "color" es igual a COLOR_MAS_BRILLOSO, a SEGUNDO_COLOR_MAS_BRILLOSO o a TERCER_COLOR_MAS_BRILLOSO.*/
bool brilla(char color[MAX_COLOR]){

	return ( (strcmp(color, COLOR_MAS_BRILLOSO) == 0) || (strcmp(color, SEGUNDO_COLOR_MAS_BRILLOSO) == 0)
		|| (strcmp(color, TERCER_COLOR_MAS_BRILLOSO) == 0) );
}

//-------------------------------------------------------------------------------------------ES_SELECCIONABLE

/*Pre-condiciones: 
    "pokemon" debe estar con campos válidos:
    	pokemon->especie debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
Post-condiciones: 
    la función retorna si la cantidad de consonantes de pokemon->especie es mayor a MIN_LETRAS_NOMBRE_LARGO.*/
bool es_trabalenguas(pokemon_t* pokemon){

	return (cant_consonantes(pokemon->especie) >= MIN_LETRAS_NOMBRE_LARGO);
}

/*Pre-condiciones: 
    "pokemon" debe estar con campos válidos:
	    pokemon->peso debe ser positivo;
    	pokemon->color debe tener un tamaño menor a MAX_COLOR y mayor a 0;
    	pokemon->velocidad debe ser positivo.
Post-condiciones: 
    la función retorna si "pokemon" cumple con las condiciones.*/
bool es_farandu(pokemon_t* pokemon){

	return ((hace_ejercicio(pokemon->peso)) && es_lindo(pokemon->color) && es_rapido(pokemon->velocidad));
}

/*Pre-condiciones: 
    "pokemon" debe estar con campos válidos:
	    pokemon->peso debe ser positivo;
    	pokemon->velocidad debe ser positivo;
Post-condiciones: 
    la función retorna si "pokemon" cumple con las condiciones.*/
bool momento_lineal_al_tope(pokemon_t* pokemon){

	return (es_grandote(pokemon->peso) && es_rapido(pokemon->velocidad));
}

/*Pre-condiciones: 
    "pokemon" debe estar con campos válidos:
    	pokemon->especie debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	pokemon->color debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función retorna si "pokemon" cumple con las condiciones.*/
bool parece_acaudalado(pokemon_t* pokemon){

	return ((cant_letras(pokemon->especie) >= MIN_LETRAS_NOMBRE_LARGO) && brilla(pokemon->color));
}

/*Pre-condiciones: 
    "pokemon" debe estar con campos válidos:
    	pokemon->velocidad debe ser positivo.
Post-condiciones: 
    la función retorna si "pokemon->velocidad" es mayor a VELOCIDAD_LUZ.*/
bool no_curso_fisica(pokemon_t* pokemon){

	return ((pokemon->velocidad) > VELOCIDAD_LUZ);
}

//-------------------------------------------------------------------------------------------BELLEZA

/*Pre-condiciones: 
	-.
Post-condiciones: 
    la función muestra una linea negra que en el medio dice NEXT.*/
void imprimir_linea(){

	printf(NEGRO"\t\t\t____________________NEXT_____________________\n"FIN);
}

/*Pre-condiciones: 
	-.
Post-condiciones: 
    la función muestra un ascii art, en el que se puede leer "Pokémon".*/
void mostrar_inicio(){

	printf(CELESTE"                                          ,'\\\n");
	printf("            _.----.        ____         ,'  _\\   ___    ___     ____\n");
	printf("        _,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
	printf("        \\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
	printf("         \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
	printf("          \\     \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
	printf("           \\     ,-' /  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
	printf("            \\    \\  |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
	printf("             \\    \\  \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
	printf("              \\    \\  `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
	printf("               \\_.-'        |__|    `-._ |              '-.|     '-.| |   |\n");
	printf("                                                                      '-._|\n"FIN);
}

/*Pre-condiciones: 
	-.
Post-condiciones: 
    la función muestra un mensaje, el cual depende del parámetro "fracaso", recibido.*/
void mostrar_exito_transferencia(int fracaso){

	printf(BLANCO "Resultado: ");
	if(fracaso)
		printf(ROJO_CLARO"Fracaso");
	else
		printf(VERDE_OSCURO"Exitoso");

	printf(BLANCO".\n\n"FIN);
}

/*Pre-condiciones: 
	"cantidad_transferir" es positivo y menor a "arrecife->cantidad_pokemon";
	"numero" idealmente es un valor entre 0 y 4. - puede ser mayor pero no cumpliría su cometido.
Post-condiciones: 
    la función muestra un mensaje, el cual depende de los parámetros recibidos.*/
void mostrar_transferencia_actual(int cantidad_trasferir, int numero, int fracaso){
	int momento_lineal;

	switch(numero){
		case 0:
			printf(BLANCO"\nPrimera transferencia: \n");
			printf(VERDE_OSCURO"+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
 		    printf("|T|R|A|B|A|L|E|N|G|U|A|S| \n");
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
			printf("REQUISITO: Cantidad de consonantes del nombre de la especie >= %i\n", MIN_LETRAS_NOMBRE_LARGO);
			break;
		case 1:
			momento_lineal = (MIN_MUCHO_PESO/GRAVEDAD)*MIN_MUCHA_VELOCIDAD;
			printf(BLANCO"\nSegunda transferencia \n");
 			printf(AZUL"+-+-+-+-+ +-+-+-+-+-+-+-+ +-+-+-+-+-+-+\n");
 			printf("|A|L|T|O| |M|O|M|E|N|T|O| |L|I|N|E|A|L|\n");
 			printf("+-+-+-+-+ +-+-+-+-+-+-+-+ +-+-+-+-+-+-+\n");
 			printf("REQUISITO: p >= %i\n", momento_lineal);
			break;
		case 2:
			printf(BLANCO"\nTercera transferencia \n");
			printf(CELESTE"+-+-+-+-+-+-+-+ \n");
			printf("|F|A|R|A|N|D|U| \n");
 			printf("+-+-+-+-+-+-+-+ \n");
			printf("REQUISITOS: \n\t■ Colores: '"COLOR_MAS_LINDO"' ó '"SEGUNDO_COLOR_MAS_LINDO"'\n\t■ Velocidad >= %i\n\t■ Peso <= %i\n", MIN_MUCHA_VELOCIDAD, MAX_PESO_FLACO);
			break;
		case 3:
			printf(BLANCO"\nCuarta transferencia \n");
			printf(AMARILLO"+-+-+-+-+-+ +-+-+-+-+-+\n");
			printf("|$|U|E|N|A| |C|H|E|T|O|\n");
 			printf("+-+-+-+-+-+ +-+-+-+-+-+\n");
			printf("REQUISITOS: \n\t■ Cantidad letras nombre especie > %i \n\t■ Colores: '"COLOR_MAS_BRILLOSO"' ó '"SEGUNDO_COLOR_MAS_BRILLOSO"' ó '"TERCER_COLOR_MAS_BRILLOSO"'\n", MIN_LETRAS_NOMBRE_LARGO);
			break;
		default:
			printf(BLANCO"\nQuinta transferencia \n");
			printf(MAGENTA"+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+\n");
 			printf("|F|I|S|I|C|A| |N|O| |E|X|I|S|T|E|\n");
 			printf("+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+\n");
 			printf("REQUISITO: velocidad >= %i\n", VELOCIDAD_LUZ);
			break;
	}
	printf("MOVER: %i\n\n"FIN, cantidad_trasferir);
	mostrar_exito_transferencia(fracaso);
}

/*Pre-condiciones: 
    "cant_espacios" positivo.
Post-condiciones: 
    la función muestra "cant_espacios" espacios.*/
void mostrar_espacio(int cant_espacios){
	
	for(int i = 0; i < cant_espacios; i++)
		printf(ESPACIO);
}

//------------------------------------FUNCIÓN_MOSTRAR

//-------------------------------/*0*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_encabezado_consonantes(){

	printf(MARRON"                                                               .---.\n");
	printf("                                                              /  .  \\ \n");
	printf("                                                             |\\_/|   |\n");
	printf("                                                             |   |  /|\n");
	printf("  .----------------------------------------------------------------' |\n");
	printf(" /  .-.                                                              |\n");
	printf("|  /   \\                                                             |\n");
	printf("| |\\_.  |                                                            |\n");
	printf("|\\|  | /|                                                            |\n");
	printf("| `---' |                                                            |\n");	
}

/*Pre-condiciones: 
    "especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0.
Post-condiciones: 
    la función muestra la primera parte de la información de un pokemon - su especie -junto a la cantidad de consonantes que hay en ella.*/
void mostrar_primera_parte_consonantes(char especie[MAX_ESPECIE]){
	char primera_frase[MAX_PALABRA];
	int espacios, consonantes_especie;

	strcpy(primera_frase, especie);
	strcat(primera_frase, "; cantidad de consonantes = ");
	consonantes_especie = cant_consonantes(especie);
	
	espacios = CARACTERES_PRIMERA_PARTE_MOSTRAR_CONSONANTES - (cant_letras(primera_frase) + cant_digitos(consonantes_especie));
	printf(MARRON"|       |\t%s%i", primera_frase, consonantes_especie);
	mostrar_espacio(espacios);
	printf("|\n");
}

/*Pre-condiciones: 
    "peso" debe ser positivo;
    "velocidad" debe ser positivo;
	"color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la segunda parte de la información de un pokemon - su velocidad, peso y color.*/
void mostrar_segunda_parte_consonantes(int velocidad, int peso, char color[MAX_COLOR]){
	char segunda_frase[MAX_PALABRA] = "■ Vel:", tercera_frase[MAX_PALABRA] = "■ Peso:", cuarta_frase[MAX_PALABRA] = "■ Color:";
	int espacios;
	
	espacios = cant_espacios_6_datos(CARACTERES_SEGUNDA_PARTE_MOSTRAR_CONSONANTES, velocidad, peso, segunda_frase, tercera_frase, cuarta_frase, color);  
	printf("|       |\t\t"NEGRO"%s"MARRON"%i  "NEGRO"%s"MARRON"%i  "NEGRO"%s"MARRON"%s", segunda_frase, velocidad, tercera_frase, peso, cuarta_frase, color);
	mostrar_espacio(espacios);
	printf(MARRON"|\n");
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon".*/
void mostrar_consonantes(pokemon_t* pokemon){

	mostrar_primera_parte_consonantes(pokemon->especie);
	mostrar_segunda_parte_consonantes(pokemon->velocidad, pokemon->peso, pokemon->color);
	printf("|       |                                                            |\n");//Hago una separación porque sino queda re juntito
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_pie_consonantes(){

	printf("|       |                                                           /\n");
	printf("|       |----------------------------------------------------------'\n");
	printf("\\       |\n");
	printf(" \\     /\n");
	printf("  `---'\n"VERDE_CLARO);
}

//-------------------------------/*1*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_encabezado_momento_lineal(){

	printf(AMARILLO"                          ___             ___  \n");
	printf("                         ("CELESTE"o o"AMARILLO")  "NEGRO"_     _"AMARILLO"  ("CELESTE"o o"AMARILLO") \n");
	printf("                        (  "MARRON"V"AMARILLO"  ) "NEGRO"p = m.v"AMARILLO" (  "MARRON"V"AMARILLO"  )\n");
	printf(MARRON"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"AMARILLO"m"MARRON"▀"AMARILLO"m"MARRON"▀▀▀▀▀▀▀▀▀▀▀▀▀"AMARILLO"m"MARRON"▀"AMARILLO"m"MARRON"▀▀▀\n"FIN);
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon".*/
void mostrar_momento_lineal(pokemon_t* pokemon){
	int momento_lineal = (pokemon->peso)*(pokemon->velocidad)/GRAVEDAD;

	printf(MARRON"█"MAGENTA" ■"BLANCO" %s: p = %i\n", pokemon->especie, momento_lineal);
	printf(MARRON"█\t"CELESTE"¤ "BLANCO"v =%4i\t"CELESTE"¤ "BLANCO"m.g = %i\t"CELESTE"¤ "BLANCO"%s\n"MARRON"█\n"FIN, pokemon->velocidad, pokemon->peso, pokemon->color);
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_pie_momento_lineal(){

	printf(MARRON"█"VERDE_CLARO"',´',´''.,´',´''.,´',´´;'-.'.,´',´-.-''.,´',´''.,´','´','''.,´',''.\n\n"VERDE_CLARO);
}

//-------------------------------/*2*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_encabezado_farandu(){

	printf(BLANCO"    _______________________________________________________________________________________\n");
	printf("  / \\                                                                                      \\.\n");
	printf(" |   |              ESPECIE            VELOCIDAD                 PESO                COLOR |.\n");
	printf("  \\_ |                                                                                     |.\n"FIN);
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon" junto con un diseño que muestra "pokemon->color" en el color que dice o en DEFAULT.*/
void mostrar_farandu(pokemon_t* pokemon){
	char color_asumido[MAX_COLOR];
	asumo_color(pokemon->color, color_asumido);

	printf(BLANCO"     |%21s%21i%21i%s%21s "BLANCO"|.\n"FIN, pokemon->especie, pokemon->velocidad, pokemon->peso, color_asumido, pokemon->color);
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forma un dibujo.*/
void mostrar_pie_farandu(){
	
	printf(BLANCO"     |   __________________________________________________________________________________|___\n");
    printf("     |  /                                                                                      /.\n");
    printf("     \\_/______________________________________________________________________________________/.\n\n"VERDE_CLARO);
}

//-------------------------------/*3*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forma un ascci art de una Macbook Pro.*/
void mostrar_encabezado_cheto(){

	printf(BLANCO"             _______________________________________________________________\n");
	printf("            /                                                                \\ \n");
	printf("           |    _________________________________________________________     |\n");
	printf("           |   |                                                         |    |\n");
	printf("           |   |      "ROJO_CLARO"for"BLANCO"("CELESTE"int"BLANCO" i = 0; i < cant_pokemones; i++)"BLANCO"            |    |\n");
	printf("           |   |  	     "CELESTE"mostrar_todos"BLANCO"();"BLANCO"                            |    |\n");
	printf("           |   |      "GRIS"//ESPECIE;VELOCIDAD;PESO;COLOR"BLANCO"                     |    |\n");
	printf("           |   |      "VERDE_OSCURO"C:"AZUL"\\> _"BLANCO"                                             |    |\n");
	printf("           |   |                                                         |    |\n");
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon".*/
void mostrar_cheto(pokemon_t* pokemon){
	int espacios_sobrantes;
	
	espacios_sobrantes = cant_espacios_4_datos(CARACTERES_MOSTRAR_CHETO, pokemon->velocidad, pokemon->peso, pokemon->especie, pokemon->color);

	printf(BLANCO"           |   |      "NEGRO"%s;%i;%i;%s"BLANCO, pokemon->especie, pokemon->velocidad, pokemon->peso,pokemon->color);
	mostrar_espacio(espacios_sobrantes);
	printf("|    |\n");
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forma un ascci art de una Macbook Pro.*/
void mostrar_pie_cheto(){

	printf("           |   |_________________________________________________________|    |\n");
	printf("           |                          MACBOOK PRO                             |\n");
	printf("            \\___________________________APPLE_©_______________________________/ \n");
	printf("                     \\_______________________________________________/\n");
	printf("                        ___________________________________________\n");
	printf("                     _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n");
	printf("                  _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n");
	printf("               _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n");
	printf("            _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n");
	printf("         _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_\n");
	printf("        :-------------------------------------------------------------------------:\n");
	printf("        `---._.-------------------------------------------------------------._.---'	\n\n"VERDE_CLARO);
}

//-------------------------------/*4*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forma un ascci art de una explosión.*/
void mostrar_encabezado_fisica(){
	printf(ROJO_CLARO"                              _.-^^---....,,--       \n");
	printf("                          _-/                 '--_  \n");
	printf("                         <                        >)\n");
	printf("                        |                         | \n");
	printf("                         \\._                   _./  \n");
	printf("                            ```--. . , ; .--'''       \n");
	printf(BLANCO" Mrs física"ROJO_CLARO"                       | |   |             \n");
	printf(BLANCO" no esta feliz."ROJO_CLARO"                .-=||  | |=-.   \n");
	printf(BLANCO" Del enojo decidio"ROJO_CLARO"            `-=#$%%&%%$#=-'   \n");
	printf(BLANCO" mostrar las palabras"ROJO_CLARO"             | ;  :|     \n");
	printf(BLANCO" al reves!!!!"ROJO_CLARO"                     | ;  :|     \n");
	printf(" _____________________________.,-#%%&$@%%#&#~,._________________________\n");
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon" junto con un diseño que muestra "pokemon->especie" y "pokemon->color" al revés.*/
void mostrar_fisica(pokemon_t* pokemon){	
	char especie_invertida[MAX_PALABRA] = {CARACTER_VACIO}, color_invertido[MAX_PALABRA]= {CARACTER_VACIO};

	palabra_invertida(pokemon->color, color_invertido);
	palabra_invertida(pokemon->especie, especie_invertida);

	printf(ROJO_CLARO"» CoLor: "BLANCO"%15s"ROJO_CLARO"\t» (masa)*(gravedad de la Tierra):"BLANCO"%4i"ROJO_CLARO"\t» EspEcIE: "BLANCO"%15s"ROJO_CLARO"\t» |VecToR VelOciDAD|:"BLANCO"%4i\n", color_invertido, pokemon->peso, especie_invertida, pokemon->velocidad);
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forma un ascci art de un dragón enojado.*/
void mostrar_pie_fisica(){

	printf(ROJO_CLARO"\t\t                 .'-,.__ \n");
	printf("\t\t                 `.     `.  , \n");
	printf("\t\t              .--'  .._,''-' `. \n");
	printf("\t\t             .    .'         `' \n");
	printf("\t\t             `.   /          ,' \n");
	printf("\t\t               `  '--.   ,-' \n");
	printf("\t\t                `'`   |  \\ \n");
	printf("\t\t                   -. \\, | \n");
	printf("\t\t                    `--Y.'     "MAGENTA" ___.\n");
	printf("\t\t                        "ROJO_CLARO" \\ "MAGENTA"    L._, \\ \n");
	printf("\t\t               _.,       "ROJO_CLARO" `. "MAGENTA"  <  <\\                _\n");
	printf("\t\t             ,' '         "ROJO_CLARO"  `, "MAGENTA"`.   | \\            ( ` \n");
	printf("\t\t          ../, `.            "ROJO_CLARO"`"MAGENTA"  |    .\\`.           \\ \\_ \n");
	printf("\t\t         ,' ,..  .           _.,'    ||\\l            )  ''. \n");
	printf("\t\t        , ,'   \\           ,'.-.`-._,'  |           .  _._`. \n");
	printf("\t\t      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\ \n");
	printf("\t\t    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`. \n");
	printf("\t\t    |  '          ..         `-...-'  |  `-'      / /        . `. \n");
	printf("\t\t    | /           |L__           |    |          / /          `. `. \n");
	printf("\t\t   , /            .   .          |    |         / /             ` ` \n");
	printf("\t\t  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\ \n");
	printf("\t\t / .           \\'`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    \\`. \n");
	printf("\t\t.  '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\ \n");
	printf("\t\t' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L` \n");
	printf("\t\t|'      _.-''` `.    \\ _,'  `            \\ `.___`.''`-.  , |   |    | \\ \n");
	printf("\t\t||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .| \n");
	printf("\t\t||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n");
	printf("\t\t|| '              V      / /           `   | `   ,'   ,' '.    !  `. || \n");
	printf("\t\t||/            _,-------7 '              . |  `-'    l         /    `|| \n");
	printf("\t\t. |          ,' .-   ,' ||               | .-.        `.      .'     || \n");
	printf("\t\t `'        ,'    `'.'    |               |    `.        '. -.'       `'\n");
	printf("\t\t          /      ,'      |               |,'    \\-.._,.'/' \n");
	printf("\t\t          .     /        .               .       \\    .'' \n");
	printf("\t\t        .`.    |         `.             /         :_,'.'\n");
	printf("\t\t          \\ `...\\   _     ,'-.        .'         /_.-' \n");
	printf("\t\t           `-.__ `,  `'   .  _.>----''.  _  __  /\n");
	printf("\t\t                .'        /''          |  ''   '_ \n");
	printf("\t\t               /_|.-'\\ ,'.             '.'`__'-( \\ \n");
	printf("\t\t                 / ,'''\\,'               `/  `-.|'AGutson \n"VERDE_CLARO);
}

//-------------------------------/*5*/

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte superior de un conjunto de caracteres que forman un cuadro.*/
void mostrar_encabezado_todos(){

	printf(BLANCO" ┌─────────────────────┬─────────────────────┬─────────────────────┬─────────────────────┐\n");
	printf(" |%21s|%21s|%21s|%21s|\n", "ESPECIE", "VELOCIDAD", "PESO","COLOR");
	printf(" ├─────────────────────┼─────────────────────┼─────────────────────┼─────────────────────┤\n"FIN);
}

/*Pre-condiciones: 
    "*pokemon" tiene todos sus campos válidos:
    	"pokemon->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    	"pokemon->peso" debe ser positivo;
    	"pokemon->velocidad" debe ser positivo;
		"pokemon->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
Post-condiciones: 
    la función muestra la información que contienen los campos de "*pokemon" junto con un diseño que muestra "pokemon->color" en el color que dice o en DEFAULT.*/
void mostrar_todos(pokemon_t* pokemon){
	char color_asumido[MAX_COLOR];
	asumo_color(pokemon->color, color_asumido);

	printf(BLANCO" |%21s|%21i|%21i|%s%21s"BLANCO"|\n"FIN, pokemon->especie, pokemon->velocidad, pokemon->peso, color_asumido, pokemon->color);
}

/*Pre-condiciones: 
    -.
Post-condiciones: 
    la función muestra la parte inferior de un conjunto de caracteres que forman un cuadro.*/
void mostrar_pie_todos(){

	printf(BLANCO" └─────────────────────┴─────────────────────┴─────────────────────┴─────────────────────┘ \n\n"VERDE_CLARO);
}

//------------------------------------EJECUCION

/*Pre-condiciones: 
    "*arrecife" tiene todos sus campos válidos:
    	"arrecife->pokemon" debe tener todos sus campos válidos;
    		"(arrecife->pokemon)->especie" debe tener un tamaño menor a MAX_ESPECIE y mayor a 0;
    		"(arrecife->pokemon)->peso" debe ser positivo;
    		"(arrecife->pokemon)->velocidad" debe ser positivo;
			"(arrecife->pokemon)->color" debe tener un tamaño menor a MAX_COLOR y mayor a 0.
    	"arrecife->cant_pokemon" debe ser positivo.
    "mostrar_encabezado" debe ser igual a: "mostrar_encabezado_consonantes", "mostrar_encabezado_momento_lineal",
    	"mostrar_encabezado_farandu", "mostrar_encabezado_cheto", "mostrar_encabezado_fisica" o "mostrar_encabezado_todos";
	"mostrar_pokemon" debe ser igual a: "mostrar_consonantes", "mostrar_momento_lineal", "mostrar_farandu", "mostrar_cheto",
		"mostrar_fisica" o mostrar_todos";
	"mostrar_pie" debe ser igual a: "mostrar_pie_consonantes", "mostrar_pie_momento_lineal", "mostrar_pie_farandu", "mostrar_pie_cheto", "mostrar_pie_fisica", "mostrar_pie_todos".
Post-condiciones: 
    la función muestra la información contenida en *arrecife, a partir de las funciones recibidas por parámetro.*/
void mostrar_arrecife_actual(arrecife_t* arrecife, void (*mostrar_encabezado)(), void (*mostrar_pokemon)(pokemon_t*), void (*mostrar_pie)()){

	printf(BLANCO"En el arrecife se encuentran los siguientes %i pokemones:\n"FIN, arrecife->cantidad_pokemon);
	mostrar_encabezado();
	censar_arrecife(arrecife, mostrar_pokemon);
	mostrar_pie();
}

/*Pre-condiciones: 
	.-
Post-condiciones: 
    la función muestra información de la ejecución al intentar crear un arrecife y un acuario, trasladar pokemones del primero al segundo, y guarda el acuario obtenido en el archivo "NOMBRE_ARCHIVO_ACUARIO".*/
int main(){
	arrecife_t *arrecife;
	acuario_t *acuario;
	int i = 0, cantidad_trasferir, fracaso;
	srand ((unsigned)time(NULL));
	bool(*es_seleccionable[MAX_FUNCIONES_SELECCIONABLES])(pokemon_t*) = {es_trabalenguas, momento_lineal_al_tope, es_farandu, parece_acaudalado, no_curso_fisica};
	void(*funcion_encabezado[MAX_FUNCIONES_MOSTRAR])(pokemon_t*) = {mostrar_encabezado_consonantes, mostrar_encabezado_momento_lineal, mostrar_encabezado_farandu, mostrar_encabezado_cheto, mostrar_encabezado_fisica, mostrar_encabezado_todos};
	void(*funcion_mostrar[MAX_FUNCIONES_MOSTRAR])(pokemon_t*) = {mostrar_consonantes, mostrar_momento_lineal, mostrar_farandu, mostrar_cheto, mostrar_fisica, mostrar_todos};
	void(*funcion_pie[MAX_FUNCIONES_MOSTRAR])(pokemon_t*) = {mostrar_pie_consonantes, mostrar_pie_momento_lineal, mostrar_pie_farandu, mostrar_pie_cheto, mostrar_pie_fisica, mostrar_pie_todos};
	
	mostrar_inicio();
	arrecife = crear_arrecife(NOMBRE_ARCHIVO_ARRECIFE);
	acuario = crear_acuario();
	if(acuario && arrecife){

		mostrar_arrecife_actual(arrecife, funcion_encabezado[VALOR_INICIAL], funcion_mostrar[VALOR_INICIAL], funcion_pie[VALOR_INICIAL]);	
		while((i < MAX_FUNCIONES_SELECCIONABLES) && (arrecife->cantidad_pokemon > 0)){

			imprimir_linea();
			cantidad_trasferir = numero_random(arrecife->cantidad_pokemon);
			fracaso = trasladar_pokemon(arrecife, acuario, es_seleccionable[i], cantidad_trasferir);
			mostrar_transferencia_actual(cantidad_trasferir, i, fracaso);
			if(arrecife->cantidad_pokemon > 0) //VALIDO ESTO SOLO SI NO ES LA PRIMERA VEZ, LA PRIMERA VEZ YA SÉ QUE NO ESTÁ VACÍO
				mostrar_arrecife_actual(arrecife, funcion_encabezado[i], funcion_mostrar[i], funcion_pie[i]);
			i++;
		}
		guardar_datos_acuario(acuario, NOMBRE_ARCHIVO_ACUARIO);
	}
	liberar_acuario(acuario);
	liberar_arrecife(arrecife);

	return 0;
}
