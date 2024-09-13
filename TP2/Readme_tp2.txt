El programa interactúa constantemente con el usuario, indicando pasos a seguir, como un mensaje de advertencia o de recomendación.
Por cada comando ingresado mostrará siempre algún mensaje en relación a ese comando. Al iniciar el programa este limpia la pantalla para que
así ocupe más espacio. muestra un mensaje de bienvenida y una pequeña sugerencia a la hora de iniciar. La pantalla de la consola siempre se va a resfrescar automaticamente
esto para evitar tener mucho historial sin usar, osea lo que ya viste y usaste se limpia. Cada vez que se desea salir del programa este muestra una advertencia recordando al usuario
que cosa debió considerar antes. 

Para compilarlo usé el comando gcc *.c -Wall -Werror -Wconversion -std=c99 -o pokedex  y seguido de este  valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pokedex 
Escribiendo esas lineas de comandos ya se puede interactuar con el programa.

Considerando todos las precondiciones de la biblioteca pokedex.h debo resaltar que la funcion pokedex_avistar() sólo si se llama a este comando 'A' se va a poder visualizar
a todos los pokemones almacenados en la pila o en la cola cuando se ingresa el comando 'C' o 'V', si antes de ver lo que hay en la pila o cola no se puso el comando 'A' el programa
mostrará un mensaje de que estan vacios cuando se desea poner el 'C' o 'V'.
También recalco que no se modificó nada de la implementacion del tda abb ni del tda lista.



La estructura de la pokedex  en forma general (no tan exactamente detallada sino un panorama general) fue pensada de la siguiente forma:






                                                                                                            especie y particular pokemones
                                                                                                        |-------------------------------------|
                                                                            (solo pokemon) ---->        |numero, especie, descripcion         |
                                                                                     nodo_t       |¬¬¬¬>|nombre pokemon,nivel y capturado[si] |
                            pokedex_t                           lista_t            |---------|    |     |-------------------------------------|
                |---------------------------------|          |------------|        |datos[o]¬¬¬¬¬¬|
                |                   |-----------| |  |¬¬¬¬¬> |inicial[o]¬¬¬¬¬¬¬¬¬>>|sig[o]   |            especie y particular pokemones
  pokedex       | nombre_entrenador |   pepe    | |  |       |tope        |        |---------|          |-----------------------------------------|
                |                   |-----------| |  |       |------------|                             |numero, especie, descripcion             |
    [o] ====>   |                                 |  |                               nodo_t       |¬¬¬¬>|nombre pokemon, nivel y capturado[si/no] |
                |          ultimos_capturados [o]¬¬¬¬|          lista_t            |---------|    |     |-----------------------------------------|
                |        ultimos_vistos [o]       |          |------------|        |datos[o]¬¬¬¬¬¬|
                |  pokemones [o]         |        |      |¬¬>|inicial[o]¬¬¬¬¬¬¬¬¬>>|sig[o]   |
                |-------------|----------|--------|      |   |tope        |        |---------|
                              |          |               |   |------------|
                              |          |¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬|
                              |                              
                              |                              
                              |
                              |                                        
                              Y                                              especie_pokemon_t
                            abb_t                nodo_abb_t           |-----------------------------|
                    |--------------------|     |-------------|        |numero[ 25 ]                 |                                           particular_pokemon_t
                    |   nodo_raiz  [o]¬¬¬¬¬¬¬¬>| elemento[o]¬¬¬¬¬¬¬¬¬>|nombre  [ pikachu  ]         |                                          |---------------------|
                    |   comparador       |     |             |        |descripcion [bla,bla,bla...] |                                          |nombre[     ]        |
                    |   destructor       |     |izq      der |        |pokemones[o]                 |        lista_t               nodo_t      |nivel [     ]        |
                    |--------------------|     |[o]      [o] |        |----------|------------------|      |------------|       |---------|    |capturado[si/no]     |
                                               |-|--------|--|                   |¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬>>>|inicial [o]¬¬¬¬¬¬¬>>|datos[o]¬¬¬¬>>|---------------------|
                                                 |        |                                                |  tope      |       |sig[o]   |
             especie_pokemon_t                   Y        Y                  especie_pokemon_t             |------------|       |----|----|    nodo_t        particular_pokemon_t
            |-----------------|        |-------------| |--------------|    |------------------|                                      |       |---------|    |-------------------|
            |    etc...       |<¬¬¬¬¬¬¬¬ [o]elemento | |elemento[o]¬¬¬¬¬¬>>|     etc....      |                                      |¬¬¬¬¬>>|datos[o]¬¬¬¬>>|   etc...          |
            |-----------------|        |             | |              |    |------------------|                                              |sig[o]   |    |-------------------|
                                       |izq      der | |izq       der |                                                                      |----|----|
                                       |[o]      [o] | |[o]       [o] |                                                                           |        nodo_t
                                       |-|--------|--| |-|---------|--|                                                                           |¬¬¬¬¬>>|-------|
                                         Y        Y      Y         Y                                                                                      |etc... |
                                        nulo     nulo   nulo      nulo                                                                                    |-------|


        <<< Esquema ilustrativa de cómo lo pensé incorporando el abb, lista y datos del tp2  para guiarme en la implementacion del pokedex >>>