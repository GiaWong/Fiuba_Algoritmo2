
# BREVE INTRODUCCION:

El torneo consta de las siguientes rondas:

1. En la primera ronda se evalúa  quién tiene mayor suma de fuerzas de todos los pokemones de cada entrenador, si hay un empate
se pasan a la función mayor_cant_vocales() que determina quien tiene mayor cantidad de vocales de todos los nombres de los pokemones por cada
entrenador.

2. En la segunda ronda se evalúa quien tiene mayor suma de agilidades de todos los pokemones de cada entrenador, si  hay un empate
se pasan a la función mayor_cant_vocales() que determina quien tiene mayor cantidad de vocales de todos los nombres de los pokemones por cada
entrenador.

3. En la tercera ronda se evalúa quien tiene mayor suma de inteligencias de todos los pokemones de cada entrenador, si hay un empate
se pasan a la función mayor_cant_vocales() que determina quien tiene mayor cantidad de vocales de todos los nombres de los pokemones por cada
entrenador.

4. En la cuarta ronda se evalúa quien tiene mayor suma de longitud de los nombres de todos los pokemones de cada entrenador,
si hay un empate se pasan a la función mayor_cant_vocales() que determina quien tiene mayor cantidad de vocales de todos los nombres de los pokemones por cada
entrenador.

5. En la quinta ronda se cuenta todas las veces en las que cada fuerza de los pokemones son numeros pares, gana el que tiene mayor valor,
si hay un empate se pasan a la función mayor_cant_vocales() que determina quien tiene mayor cantidad de vocales de todos los nombres de los 
pokemones por cada entrenador.

Si en caso hubiese un solo participante, este será el ganador porque no tiene con quien competir.


## EXPLICACION DE COMPILACION:

Se compila siguiendo los mismos pasos que indica en la descripción del enunciado del tp.


## EXPLICACION DE EJECUTACION:

El programa solo va a interactuar con el usuario para avanzar a la siguiente  ronda, inicialmente se muestra por pantalla toda la lista
de los participantes a competir junto con sus respectivos pokemones y datos de sus habilidades.


Cuando el usuario de enter para pasar a la siguiente ronda, el programa va a mostrar una lista del historial de personajes que se fueron
eliminando, seguidamente aparecerá otra lista de quienes pasan a la siguiente ronda.


El programa termina cuando muestra al ganador junto con la descripción de sus pokemones o un mensaje que avisa si algo salió mal.


## EXPLICACION DE CONCEPTOS y EJEMPLOS EN DONDE LO USÉ, COMO:

- **PUNTEROS**:

    Son un tipo de dato que apuntan a direcciones de memoria, usando punteros se evita estar constantemente haciendo garabatos con variables comunes porque en cierto modo son más flexibles  a la hora de acceder a ciertas posiciones de memoria.

    Los usé mucho para reservar memoria dinámica y para abrir archivos. 

- **ARITMETICA DE PUNTEROS**: 
	
    La aritmética de punteros  me permitió moverme  entre  las casillas del vector y poder acceder a las posiciones de los punteros y modificar el contenido, 
    los usé para llenar datos que obtuve al leer el archivo, también los usé para acceder a sus contenidos y hacer comparaciones directas, así como también para guardar su contenido en otras variables.


- **PUNTEROS A FUNCIONES**:

    Entiendo que permite que usemos funciones que no necesariamente deben estar implementadas en el main, sino que directamente se puede manipular a esa funcion y trabajarlo en otro espacio para implementarlo, osea en otro .c , así se hace más fácil no tener una función cuyo código sea demasiado largo, y directamente lo llevamos como parámetro en la biblioteca .h y se manda nombre de funciones que uno quiere usar.


    Punteros a funciones lo usé para determinar que función va a requerir cada ronda, así desde el main mando el nombre de la funcion que quiero usar y en el otro .c donde implementé a la funcion con ese nombre reconoce la dirección que le mandé y se comienza a trabajar con ello.

    
- **MALLOC Y REALLOC**:

    Con malloc y realloc son funciones que me permite reservar memoria en el heap, con Realloc usé más para modificar el tamaño de mi vector ya sea para extenderlo o para reducirlo, en el caso de extender el tamaño lo usé en la funcion "torneo_crear()" ya que a medida que iba leyendo el archivo de texto necesitaba guardar  los datos en un vector cuyo tamaño no sabía a priori, y en el caso de reducirlo lo usé en la funcion "torneo_jugar_ronda()" para eliminar posiciones de algunos  entrenadores.
    
    Ahora con Malloc usé mucho para reservar memoria con tamaño fijo que sabía por ejemplo para los pokemones, y también los usé porque era necesario acceder algún contenido que el código requería para poder trabajar con ciertas cosas. 




