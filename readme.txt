------------------------------------------------Convenciones------------------------------------------------

Las convenciones que utilizo en el trabajo son con base en qué me parece más legible, siempre respetando el uso del ​snake_case​.

------------------------------------------------

Con respecto al código, lo separo en tres partes:

...{
	declaraciones​;

	código​;

	return​;
}

En caso de no haber una de las partes, hago lo siguiente:

○ Si no hay declaraciones:
...{
	código​;

	return​;
}

○ Si no hay return:
...{
	declaraciones​;

	código​;
}

○ Si solo hay código:
...{

	código​ ;
}

La razón por la que dejo un enter arriba del código pero no debajo es debido a que cuando minimizo el bloque, no me gusta que quede una línea en blanco, ya que si hubiera un enter abajo quedaría como:
...{​ __

}

Y prefiero que quede sin el espacio:

...{​ __
}

- esto es más entendible con colores y dibujos pero no se puede, para más información me podes consultar por privado-

Añado: Dentro de bloques de código suelo seguir la misma regla, es decir, dentro de funciones de control por ejemplo.

------------------------------------------------

Me gusta escribir sin corchetes si es posible, como

for(...)
    ...;

o

if(...)
    ...;

Tratando de respetar siempre que sea posible una acción por línea.

------------------------------------------------

Para escribir funciones de control, escribo la función y al lado los paréntesis, sin dejar espacio, por ejemplo:

while(...){
    ...;
}

------------------------------------------------

Para escribir un boooleano (ya sea función o variable) dentro de una condición, me gusta hacerlo sin el "==", sino que con el mero nombre de lo que estoy trabajando, y en caso de querer negarlo, un "!" antes del mismo. Por ejemplo:

while(es_rojo(tateti_suerte_pa_mi) || !termino){
    ...;
}

------------------------------------------------

Para escribir varias condiciones, trato de usar la siguiente convención:
En caso de no haber una de las partes, hago lo siguiente:

○ En caso de haber varias operaciones de comparación:
if((condicion_1 > 0) && (condicion_2 > 0))
-> respeto las buenas prácticas de cada comparación -acción- en un paréntesis, además no dejo espacios entre el primer y ultimo paréntesis. 

○ En caso de haber funciones booleanas y operaciones de comparación:
if(es_valido(condicion_1) && (condicion_2 > 0))
-> las funciones no las separo entre paréntesis, respeto las buenas prácticas de cada comparación -acción- en un paréntesis, además no dejo espacios entre el primer y ultimo paréntesis. 

○ En caso de haber funciones booleanas solamente:
if(es_valido(condicion_1) && es_valido(condicion_1))
-> las funciones no las separo entre paréntesis, además no dejo espacios entre el primer y ultimo paréntesis. 

○ En caso de que haya punteros con campos:
if(((condicion_1->tata) > 0) && ...)
-> toda la variable la pongo entre paréntesis, para evitar confusiones.

------------------------------------------------

- Los colores fueron elegidos con intención, y también con intención decidí solo colorear el texto, no resaltarlo. Esto último no me agrada visualmente.

- Para que el nombre del archivo de arrecife sea válido, debe tener extensión .TXT y tener algo escrito antes.

- El TP cuenta con un programa.c, que es el programa principal, el cuál utiliza la biblioteca evento_pesca.h y la biblioteca funciones_generales.h, la cual contiene funciones generales que suelo usar en todos los TPs.

------------------------Estructuras de control:

● Uso del​ ​do while​ :
Para el ingreso de datos me parece muy práctico que vuelva a preguntar exactamente lo mismo que siempre, en caso de haber ingresado algo inválido, además del
error cometido, y escribir la pregunta afuera del while y dentro del mismo me resulta repetitivo, es el por qué preferí usar do while en esos casos.

● Uso del ​if​ y del switch​ :
En caso de tener más de dos situaciones, utilizo el switch, sino el if: me resulta más cómodo.

------------------------Estructura del programa:

● Se exhorta usar el programa en pantalla completa, sino no se podrá asegurar la correcta visualización del mismo.

● Las constantes las tengo alineadas en grupos, así me organizo mejor. Es decir, los valores de cada una los tengo a la misma altura solo si son del mismo grupo. Por ejemplo:

#define LEER 						"r"
#define ESCRIBIR 					"w"

#define TODO_OK		0
#define ERROR		-1

------------------------------------------------Ejecución------------------------------------------------

Objetivo:

    El objetivo de mi programa es crear en memoria dinámica una simulación de un arrecife y de un acuario, obteniendo los datos del primero de un archivo, y mediante unos criterios internos (ante cuestiones relacionadas al por qué esos criterios, consultar con Misty, ella así lo quería) ir moviendo elementos hacia el acuario, es decir: eliminar de uno y colocarlo en el otro.

    Mi programa, a su vez, mostrará información sobre la ejecución al finalizar, mostrando datos que ayuden al usuario a entender qué sucedió.

Descripción breve del funcionamiento de mi programa y cómo compilarlo:

    Mi programa comienza al compilar todos los .c de la carpeta, y ejecutando lo compilado.
    
    La linea de compilación recomendada es: gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
    Es decir, quiero que compile todo los .c con todos los warnings posibles, leyendo estos como error, y mostrando todas las conversiones que pueden generar cambios en el valor de una variable, y que el ejecutable lo llame "evento_pesca".

    Para ver el uso de memoria, correr con valgrind. Recomiendo correr con: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca
    Antes de correr con valgrind, recordar que tenés que tener el ejecutable creado (en este caso "evento_pesca").
    
    Sino, ejecutar normal: ./evento_pesca

    Ahora, bien: ¿cómo funciona mi programa?

    Inicia en el main que se encuentra en programa.c, sin argumentos recibidos por consola. Hubiera podido recibirlos si quisiera, hubiera tenido que agregar dos parámetros al main, pero como me indicaste que no te gustaba, no lo hice, no cambia demasiado tampoco.

    Luego, declaro las variables que voy a utilizar, entre ellas inicializo una semilla para el random, así logro que se generen diferentes randoms cada vez que lo utilizo por primera vez. Entre las variables que declaro, declaro 4 punteros a funciones (ver sección: ¿Qué es un puntero a función?): 3 de ellos son para mostrar y 1 es un booleano para utilizar en el movimiento de pokemones.

    Procedo a mostrar un ascii art al inicio por consola, en el cual se puede leer "Pokémon".

    Lo primero que hago en cuanto al proceso, es crear un arrecife y un acuario.

    Para crear el arrecife, utilizo la función dada por consigna. En ella hago todas las declaraciones pertinentes, inicializo lo necesario (es vital que arrecife esté inicializado en NULL), y consulto si el parámetro recibido, el cual refiere al nombre del archivo del cuál obtendré el arrecife a simular, es válido: esto implica que contenga un ".txt" y que antes de eso tenga algo escrito: si eso no sucede se mostrará un mensaje de error, pero en caso de que eso sea válido, también valido que se pueda acceder al archivo en modo lectura. No es menor notar que hice las dos verificaciones juntas, ya que al tener un if(... && ...), al no cumplirse el primer requisito, ya no se entra al bloque de código del if, por lo que no se valida que el archivo se pueda abrir si es que no está bien su nombre. Esto podría haberse hecho con dos ifs pero así me parece mucho mejor. En caso de no cumplirse lo solicitado, saldría de la función con el arrecife, el cual se encuentra en NULL. Si entra al if, abro el archivo y solicito (para entender mejor, ir a "¿Qué es malloc y cómo se usa?") un bloque de memoria del tamaño de un arrecife_t (tipo de dato del arrecife, struct de dos campos, también obtenido por consigna), y digo que arrecife va a ser igual al puntero que me devuelve la solicitud realizada. Si la solicitud fue rechazada (devolvió NULL), muestro un mensaje de error. Sino, inicializo los campos del arrecife (la cantidad de pokemones en 0 y su puntero pokémon en NULL) y procedo a leer por primera vez el archivo: si se lee mal (no hay nada escrito, lo escrito está diferente a lo estipulado o los datos leídos no cumplen con las condiciones impuestas), se libera la memoria reservada para el arrecife y los pokemones, se cierra el archivo y se muestra un mensaje de error, además de devolver NULL. Si se lee bien, se agrega el pokémon leído al arrecife y se vuelve a leer, hasta que no se lea bien. Luego cierro el archivo y retorno mi arrecife.

    ¿Cómo agrego el pokémon al arrecife? Creo un nuevo puntero y lo inicializo en NULL. Solicito redimensionar el lugar en donde lo voy a guardar y asigno ese espacio a este nuevo puntero (para entender mejor, ir a "¿Qué es realloc y cómo se usa?"). Si la solicitud fallo (devolvió NULL), muestro un error, y retorno NULL. Sino, el lugar donde voy a guardar el pokémon leído lo igualo a mi nuevo puntero, guardo el pokémon leído y aumento la cantidad de pokemones del arrecife.
    
    Procedo a crear entonces, un acuario, se haya o no creado un arrecife, porque así está hecho según el flujo de mi programa: declaro un puntero, llamado acuario, el cual solicito que sea igual a un bloque de memoria dinámica del tamaño de un acuario_t (tipo de dato de mi acuario). Si la solicitud fue exitosa, inicializo sus valores, sino muestro error. Devuelvo el acuario ya que este es NULL o no según el éxito de la solicitud realizada.

    Volviendo al main (ya que estas funciones se encuentran en evento_pesca.c, condición impuesta por consigna), verifico si acuario y arrecife son diferentes a NULL -notar que AMBAS deben serlo- y sino, directamente llamo a las funciones liberar. Las opciones que tenemos ahora son:
	- Que arrecife sea null y que acuario sea null. -Que arrecife sea null y que acuario no lo sea. - Que arrecife no sea null pero acuario sí.
    
    Es por lo indicado arriba que tengo que liberar al menos uno de los dos punteros, con su respectivo puntero a pokémon. Por eso, dentro de cada liberar, valido que no sea NULL el puntero arrecife o el acuario, pero llamo a ambas funciones (liberar_arrecife(...) y liberar_acuario(...)) sin importar cuál sea el caso con el que se esté lidiando.

    Por el contrario, si ambos punteros son diferentes a NULL, empieza lo divertido. Lo primero que hago es mostrar el arrecife actual: sé que voy a estar mostrando algo porque sino la lectura del archivo hubiera mandado error, y lo voy a estar haciendo en forma de cuadro (recomiendo ver ANEXO 1: MOSTRAR): esto último es totalmente modificable, lo hago así porque Misty me lo indicó, pero podría cambiar el orden de las funciones para mostrar.
    
    Luego de mostrar, entro en un bucle para trasladar los pokemones del arrecife al acuario de ser posible: tiene que cumplirse que no haya realizado el ciclo 5 veces o más, y que la cantidad de pokemones de los que disponga en el arrecife sea mayor a 0.
    
    Para empezar, imprimo una linea de separación que dice "NEXT", porque me gusta y me parece estéticamente prolijo (y obvio a Misty también), no hay otra razón. Además, genero un número random entre 1 y la cantidad de pokemones que haya en el arrecife, que va a ser la cantidad de pokemones que se quieren trasladar al acuario -es vital recordar que en realidad estamos trabajando con punteros, es todo una simulación dentro de la memoria dinámica, pero para facilitar la explicación reduzco la denominación del puntero que apunta al acuario y del puntero que apunta al arrecife a "acuario" y "arrecife" respectivamente-. Invoco a la función para trasladar los pokemones segun el puntero a función que corresponda (recomiendo ver ANEXO 2: ES_SELECCIONABLE), marcado por la cantidad de veces que se cumplió el ciclo iterativo. En este primer caso, invocaría a trasladar pokemones, enviándole como parámetro un puntero a la función es_trabalenguas(), ya que es_seleccionable en i, este caso "i = 0" es esa; igualando lo que me devuelva mi trasladar pokemones a la variable numérica fracaso.
    
    ¿Qué hace trasladar pokemones? La función traslada la cantidad de pokemones indicada que cumplan con la condición recibida por parámetro como puntero a función, siempre y cuando haya esa cantidad en el arrecife. Si yo ya sé que, de por sí, hay menos pokemones en mi arrecife que los que quiero trasladar, devuelvo ERROR. Esto podría darse solamente si se invoca a la función desde otra parte que mi main, ya que en mi main la cantidad de pokemones que voy a trasladar es un numero que va entre 0 y dicha cantidad de pokemones. Pero prefiero prevenir que curar así que vuelvo a validarlo dentro de trasladar. Si la cantidad a trasladar es menor a la que poseo (está todo bien), entonces procedo a recorrer mi vector de pokemones - valga la repetición de que es un puntero a un vector de pokemones alojado en memoria dinámica- para verificar si tengo la cantidad requerida de pokemones que cumplan con la condición impuesta. Esto lo explico por las dudas, mejor que sobre a que falte: Tengo una función de control que itera mientras que que mi variable que marca la cantidad de iteraciones hechas (i, la cual inicialicé en 0) sea menor a la cantidad de pokemones que hay en el arrecife y que la cantidad de pokemones que detecté que puedo trasladar sea menor a la cantidad de pokemones que tengo que trasladar. Dentro de esta estructura de control, tengo un condicional de que si el pokémon en la posicion "i" del arrecife cumple con lo requerido por la función recibida por parámetro, me sume uno a la cantidad de pokemones que puedo trasladar (trasladados), recordando que esta la inicialicé en 0, y cumpla o no, por cada iteración incremento "i" en uno. Bien, al salir de mi estructura iterativa, tengo dos posibles casos:
    - Que haya salido de la estructura porque terminó de recorrer todo el vector de pokemones;
    - Que haya salido de la estructura porque ya detectó la cantidad requerida de pokemones a trasladar.
	Si se trata del primer caso, devuelvo ERROR. Sino, reinicio mis variables "i" y "trasladados" y vuelvo a iterar recorriendo todo el vector de pokemones de mi arrecife. Por cada vez que encuentre uno que cumpla con lo impuesto por la función recibida por parámetro, elimino el pokémon del arrecife y lo muevo al acuario. Sino, incremento i en uno.
    
    ¿Qué hace eliminar pokémon? Lo primero, es eliminar ordenadamente a partir de la posición indicada. También, reduzco la cantidad de pokemones que hay en el arrecife. Si la cantidad de pokemones que quedan en el arrecife es mayor a 0, solicito que se redimensione el lugar donde guardo los pokemones, achicandolo en una unidad. Si la solicitud falla, muestro un error y devuelvo NULL. Si la cantidad es 0, sé que saldrá del iterador de trasladar pokemones, luego saldrá del iterador del main, y por último realizará los free necesarios, evitando toda pérdida de memoria posible.
    
    Si pude eliminar el pokémon del arrecife, es decir, redimensionar el vector de pokemones del arrecife, agrego el pokémon elimnado al acuario, de la misma manera que lo agregaba antes al arrecife (ut supra en "¿Qué hace agregar pokémon?").

    Al salir del ciclo iterativo, salgo de la función devolviendo si pude trasladar según la cantidad indicada y la función impuesta. Vuelvo al main y muestro qué transferencia acabo de realizar y el resultado de la misma. Además, si quedan pokemones en el arrecife, muestro cuáles quedan con alguna temática, en este primer caso con "mostrar_consonante()".

    Itero tal cómo lo explique ut supra, y al terminar, guardo los datos del acuario en un archivo, por default en acuario.txt. Para finalizar, libero el arrecife y el acuario.

------------------------------------------------TEORÍA------------------------------------------------
--------------------------------¿Qué es un puntero y cómo es su aritmética?
Básicamente, un puntero es una variable que contiene la dirección de memoria de otra variable, ambas del mismo tipo. Tiene una aritmética propia para así poder obtener lo que contiene (es decir, esta dirección de memoria), o a lo que apunta. Se suele utilizar para manipular estructuras de datos dinámicos (en memoria dinámica).
Para obtener la dirección de memoria de una variable se utiliza el operador "&" antes de la variable: operador de dirección.
Para obtener el contenido de lo que apunta un puntero se utiliza el operador "*" antes de la variable: operador de indirección.
Además, un puntero se puede utlizar como si fuera un array, haciendo "--" o "++". 
Desde C no es posible indicar una dirección de memoria, esto se hace mediante funciones.
Conviene inicializar los punteros en NULL, indicando que no apuntan a nada.

Veamos una muestra de lo recién dicho:
Imaginemos la variable numérica x. Esta es igual a 40. Si hacemos "&x", vemos su dirección de memoria: 1800. Ahora, tenemos también un puntero, puntero_1, de tipo numérico, al igual que la variable x - esto último es fundamental. El contenido de puntero_1, "*puntero_1", es igual a la dirección de x, "&x". Por eso, al declararlo hago "int *puntero_1 = &x": declaro un puntero llamado puntero_1 que contiene la dirección de memoria de x. A partir de la declaración, para referirme al puntero utilizaré "puntero_1" - sin el operador de indirección, el asterisco. Si quiero acceder a lo que representa este puntero, hago "*puntero_1", para acceder a lo que contiene (la dirección de memoria), hago "puntero" - sin asterisco. En caso de trabajar con estructuras (el puntero tiene campos dentro), podemos utilizar "(*puntero_1).campo" o "puntero_1->campo", son lo mismo, es notación.

Si quisiera crear un puntero que contenga la dirección de memoria que contiene otro puntero (un puntero a un puntero) el cual apunta a una variable no puntero, debo utilizar los múltiples "*" para su declaración. A continuación ejemplificaré lo dicho:

Imaginemos ahora que queremos hacer un puntero a "puntero_1", entonces tendremos que declararlo como "int **puntero_2 = &puntero_1", y así sucesivamente, con todos los ordenes que queramos. Es decir, un puntero a puntero_2 sería "int ***puntero_3 = &puntero_2".

--------------------------------¿Qué es un puntero a función?
Un puntero a función es basicamente como un puntero normal pero contiene la dirección de memoria de una función, en vez de el de una variable. Esto es sumamente util ya que pueden ser utilizados como "variables": ser elementos de un array, ser parámetros de funciones y ser retornos de funciones.

La diferencia con punteros es que no apuntan a "datos" sino que a "código", y no debe reservarse memoria para su uso, y por ende, tampoco debe liberarse memoria.
Su declaración es así:
void (*función_puntero)(tipo_dato_parametro_1*, tipo_dato_parametro_2, ...);

Si quiero podría hacer un vector:
void (*función_puntero[MAX_TAMANIO])(tipo_dato_parametro_1*, tipo_dato_parametro_2, ...) = {la_funcion_1, la_funcion_2};

Importante: en caso de declararla como: void *función_puntero (tipo_dato_parametro_1*, tipo_dato_parametro_2, ...); -sin parentesis- estaría escribiendo la firma de una función que se llama funcion_puntero, cuyos parámetros son los colocados ut supra y que devuelve un *void. Así que ojo con confundirse

Volviendo al primer caso, un uso podría ser el siguiente:
funcion_puntero = &la_funcion_1;
funcion_con_parametros_raros(..., funcion_puntero, ...);
funcion_puntero = &la_funcion_2;
funcion_con_parametros_raros(..., funcion_puntero, ...);

Puedo acceder a la dirección de memoria de la función con su aritmética.

--------------------------------¿Qué es malloc y cómo se usa?
Malloc es una función para trabajar con punteros, la cual, básicamente, solicita un nuevo bloque de memoria libre para usar durante el programa y devuelve la dirección de memoria del bloque. En caso de rechazar la solicitud, devuelve NULL. Como parámetro se le envía la longitud del bloque de memoria que se está solicitando, la cual está en bytes, por lo que se suele enviar sizeof(tipo_de_dato).

Normalmente se lo iguala al puntero que vamos a estar utilizando, así este se guarda en memoria dinámica y no en el stack.

Un ejemplo:

int* puntero;

/*Reservo espacio para mil int y se lo asigno a puntero. Si fue exitoso, ahora puntero contiene la dirección de memoria que malloc reservo del heap*/
puntero = malloc(sizeof(int)*1000);
if(puntero){ //si fue exitoso
    for(int i = 0; i < 1000, i++){
        puntero[i] = NUMERO_DEFAULT;
    }
    ...;
    free(puntero); //no olvidarme de liberar lo que tengo en memoria dinámica.
}

--------------------------------¿Qué es realloc y cómo se usa?
Realloc es una función para trabajar con punteros, la cual modifica el tamaño de un bloque de memoria que está apuntado por un puntero. Si puede hacerlo, la función copia el principio del bloque nuevo de memoria al contenido del viejo, y libera la memoria ocupada por el bloque viejo, devolviendo la dirección del nuevo bloque. Sino, como en malloc, devolverá "NULL".

Sus parámetros son el puntero y el nuevo tamaño a tener, considerando que si este puntero es NULL, realloc se comportará como un malloc(), y si size es "0", se comportará como un free(). 

Ejemplo:

//Actualizo el tamaño del bloque de memoria al que apunta puntero de 1000 (lo original con malloc ut supra) a 900 con realloc()
puntero = malloc(puntero, sizeof(int)*900);
if(puntero){ //si fue exitoso
    for(int i = 0; i < 1000, i++){
        puntero[i] = NUMERO_CORRECTO;
    }
    ...;
    free(puntero); //no olvidarme de liberar lo que tengo en memoria dinámica.
}

------------------------------------------------ANEXOS------------------------------------------------
--------------------------------ANEXO 1: MOSTRAR

Las funciones mostrar tienen temáticas, es por esto que decidí agregarles un encabezado y un pie:
● todos: Muestro en un cuadro toda la información recibida, sin nada raro, para tenerlo como referencia luego de las transacciones. Es la primera función utilizada.
● consonantes: Muestro en un pergamino, centrándome en la cantidad de consonantes que posee el nombre de la especie del pokémon. Esta puesto después de la transacción de eliminar pokemones segun la cantidad de consonantes, para poder comparar con los que había antes.
● momento lineal: Muestro al costado de un tronco, información de los pokemones, mostrando también el modulo de su momento lineal, el cual es producto de su masa (peso/gravedad) y su velocidad. Lo hago justo después de transferir según cantidad de momento lineal.
● farandu: Muestro en un pergamino, diferente al de "consonantes" información de los pokemones.
● cheto: Muestro en una MacBook Pro, una consola en la que se lista la información de los pokemones.
● fisica: Luego de retirar los pokemones que desafiaron a la física y tienen velocidad mayor a la velocidad de la luz, Mrs física se enojó y lo muestro con el dibujo de un dragón incendiando y desordenando la información de los pokemones.

- Tanto en "farandu" como en "todos" trato de imprimir los colores de los pokemones con el respectivo color. 
- Cada mostrar está con colores adrede al ascii art.
- Al final del printf de cada mostrar pie, puse el color VERDE para que parezca que lo que compila valgrind está super bien, es un efecto visual. No te lo iba a decir, por eso lo hice camuflado, pero aclaro por las dudas. No lo puse aparte en un solo printf al final para que esté más camuflado.
- Para mostrar asumo que la velocidad y el peso no van a tener más de 4 dígitos, y que el nombre de la especie y el color del pokemon va a tener máximo 15 letras.
Lo asumo porque son POKEMONES y leí en internet que así resulta.

-----------------------ANEXO 2: ES_SELECCIONABLE

Las funciones para seleccionar no tienen razón alguna, son las elegidas por Misty:
● trabalenguas: el pokémon debe tener una cantidad mínima de consonantes en el nombre de la especie.
● momento lineal: el pokémon debe tener una cantidad mínima de momento lineal ((peso/gravedad) * velocidad).
● farandu: el pokémon debe estar fuerte, ser rápido y tener uno de los mejores colores.
● acaudalado: el pokémon debe tener el nombre de la especie con un mínimo de letras y que su color sea uno brillante.
● no curso fisica: el pokémon debe tener una velocidad mayor a la de la luz.

- ninguna de las funciones fueron hechas con ánimos de ofender, sino que busqué colores y pesos de pokemones gordos en internet y utilicé esos datos.

-----------------------BIBLIOGRAFÍA

- https://www.asciiart.eu
- https://www.pokemon.com/el/pokedex
- https://www.algoritmos7541mendez.com.ar
- https://www.pokemon.fandom.com/es/wiki
