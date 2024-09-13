# Hash
El programa muestra por pantalla todas las pruebas que se realizan para saber
si lo que se ha implementado en hash.c no falla a la hora de testearlo.

La compilación del programa se realiza con el comando:
    
    gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -oo

Al ejecutar con el ./ el programa mostrará todas las pruebas que tiene, de tal forma que 
los clasifiqué  como:

    ==>PRUEBAS CREANDO HASH CON DESTRUCTOR NULO
    ==>PRUEBAS CREANDO HASH CON CAPACIDAD MENOR
    ==>PRUEBAS CREANDO HASH VALIDO  
    ==>PRUEBAS INSERTANDO NULOS
    ==>PRUEBAS INSERTANDO ALGO INEXISTENTE
    ==>PRUEBAS INSERTANDO UN VALOR VALIDO 
    ==>PRUEBAS INSERTANDO VARIOS VALORES VALIDO 
    ==>PRUEBAS OBTENIENDO CON HASH NULO
    ==>PRUEBAS OBTENIENDO HASH CON CLAVE INEXISTENTE
    ==>PRUEBAS OBTENIENDO HASH CON CLAVE EXISTENTE
    ==>PRUEBAS DE CONTENIDO CON HASH NULO
    ==>PRUEBAS DE CONTENIDO CLAVE INEXISTENTE CON HASH VALIDO
    ==>PRUEBAS DE CONTENIDO CLAVE VALIDA CON HASH VALIDO
    ==>PRUEBAS DE CANTIDAD CON HASH NULO
    ==>PRUEBAS DE CANTIDAD CON HASH SIN ELEMENTOS
    ==>PRUEBAS DE CANTIDAD CON VARIOS ELEMENTOS VALIDO Y HASH NO NULO
    ==>PRUEBAS DE QUITAR ELEMENTOS CON HASH NULO
    ==>PRUEBAS DE QUITAR ELEMENTOS CON CLAVE INEXISTENTE Y HASH VALIDO
    ==>PRUEBAS DE QUITAR ELEMENTOS VALIDOS CON HASH VALIDO
    ==>PRUEBAS DE ITERADOR INTERNO CON HASH NULO
    ==>PRUEBAS DE ITERADOR INTERNO CON FUNCION NULA
    ==>PRUEBAS DE ITERADOR INTERNO CON HASH VALIDO
    ==>PRUEBAS CON ITERADOR EXTERNO CREAR CON HASH VALIDO
    ==>PRUEBAS CON ITERADOR EXTERNO CREAR CON HASH NULO
    ==>PRUEBAS CON ITERADOR EXTERNO SIGUIENTE
    ==>PRUEBAS CON ITERADOR EXTERNO QUE SI TIENE SIGUIENTE 
    ==>PRUEBAS CON ITERADOR EXTERNO QUE NO TIENE SIGUIENTE 
    ==>PRUEBAS CON ITERADOR EXTERNO TIENE SIGUIENTE CON ITERADOR NULO
	
Todas las pruebas mostrará indicando si hubo éxito o si algo falla indica error,
al final de todas las pruebas se mostrará un mensaje de cuántas
pruebas exitosas hubo.


---

El planteo esquemático en cómo lo pensé para encarar la estructura del hash fue lo siguiente:
__Teniendo en cuenta que esto [o] es un puntero__, supongamos que


                                                                                                          ..
                                                                                                          ..           
    un tamaño inicial de 3                                                                              | [o] |
    casillas, dos de ellas                                                                              |-----|   
    estan ocupadas, por tanto              Nueva Tabla Hash                                             | [X] |  
    supera el umbral según                      |-----|                                                 |-----|
    el criterio que yo tomé,                    | [o] |                                                 | [X] |
    osea la mitad del tamaño                    |-----|                                                 |-----|
    actual.                                     | [X] |                                                 | [o] |
                                                |-----|                                                 |-----|
       Tabla Hash                               | [X] |                                                 | [X] |      
        |-----|                                 |-----|                                                 |-----|
        | [o] |                                 | [X] |                                                 | [X] |
        |-----|                                 |-----|                                                 |-----|
        | [o] |      --------------->           | [o] |          ----------------->                     | [X] |
        |-----|    Redimensiono a la Tabla      |-----|  Y así sucesivamente voy redimencionando        |-----|
        | [X] |    multiplicando el tamaño      | [X] |   el tamaño de la tabla cada vez que supera     | [o] |
        |-----|        actual por 3             |-----|   la mitad de sus casilla, le voy ampliando     |-----|
                   y reubico rehasheando        | [X] |   multiplicando el tamaño actual por 3          | [o] |
                    posición que estaba         |-----|                                                 |-----|
                        anteriormente           | [X] |                                                 | [X] |
                                                |-----|                                                 |-----|
                                                | [X] |                                                   ..
                                                |-----|                                                   ..
                                                                                                          ..



__Aclaración__: si cuando yo redimenciono a mi Tabla Hash y el tamaño que obtengo no es un número primo, entonces
mantengo el tamaño pero lo amplío un poco más hasta encontrar un próximo número primo. El esquema no es tan detallado
solo es un boceto para guiarme en la realización del el algoritmo.

### Preguntas del pdf


1. Una explicación de los diferentes tipos de hashes que conoce y cómo se resuelven las colisiones.

    - Existe varias __funciones hash__, funciones ya predeterminadas que es de uso común, pero también pueden existir nuevas funciones de Hasheo propias de cada implementador/a, algunos que conozco son estas:

        - __Aritmética Modular__:  Siempre se usa al final de toda función Hash sea cual sea la implementación,
    es recomendable aplicar el módulo porque así te garantiza de que la asignación de las posiciones esten netamente en el rango de la capacidad o tamaño que tiene el Hash.
    
        También existe el de __Mitad cuadrado__, __Los exponenciales__, __El truncamiento__, una infinidad de funciones; por ejemplo mi implementación de función hash es una mezcla de contar la longitud de mi clave y mediante una iteración voy haciendo una operación de suma por cada posición de la clave multiplicandole por un __FACTOR__ con la posición de la clave que saqué anteriormente, al final devuelvo el valor incorporando aritmética modular.

        En sí los diferentes tipos de hashes que existen para implementar va a criterio de cada programador/a no hay una regla extricta que limite la imaginación del implementador/a pero solo es necesario que siempre se debe sacar el módulo del resultado de la función hash.
       

    - Para __evitar las colisiones__ la cantidad de posiciones de la tabla hash debe ser un número primo
    (transformarle a un número primo), así se favorece más la dispersión de poder ubicar las claves a otras casillas
    y no colisionar en una misma casilla. 
    
        El concepto de hash en sí mismo se basa en no caracterizarse por tener muchas colisiones, sino no se consideraría un Hash bien implementado (en la función hash).

        Pero en el peor de los casos si presentamos colisiones, existen maneras de reubicar, por ejemplo:
        - Si consideramos un Hash Cerrado:
            Se puede crear una funcion auxiliar que permite reubicar al elemento que pisa , enviandole un casillero posterior a la actual, si en caso este esté ocupado, seguirá recorriendo hasta encontrar una casilla disponible, pero
            la desventaja de hacer esta maniobra es que ténes un alto riesgo de que la busqueda de un casillero libre sea O(n), y en consecuencia no se consideraría un Hash porque también el Hasheo no esta dispersando las ubicaciones.
        
        - Si consideramos un Hash Abierto:
            Es más fácil trabajar con Tablas a punteros lista, cuando el caso presenta colisión el elemento se puede almacenar
            en el siguiente nodo de la lista, pero suponiendo en el peor de los casos que el hash mande otro elemento al mismo casillero ocupado, cada casillero deberá tener un límite de ocupación (Factor de ocupación), este límite indicará que la lista está cada vez llenandose y si supera el límite hay riesgo de que la lista sea tan larga y para recorrer a cierto elemento tardaríamos un O(n) en el peor de los casos. Por eso está el límite de ocupación que te avisa el máximo de lementos que tu lista puede tener.

        __(Aclaración: la resolucion de colisiones es variado, solo destaqué lo que más me acuerdo)__


---


2) Qué entiende por rehash y por qué es importante.

    - El rehasheo es importante para redimendionar una Tabla hash anterior,ya que como en toda función hash siempre se usa la aritmética modular
     y esta operación te tira valores entre ciertos límites, en este caso entre el rango del tamaño actual de la tabla, entonces cuando vos querés extender
     la capacidad del hash ténes que rehashear pero considerando un nuevo tamaño a la ahora de aplicar el módulo, por ejemplo:


        Tengo una tabla de 3 casillas         sino hasheo es muy probable que tenga colisión                  si rehasheo con un nuevo tamaño, el
        y están casi  llenas                      porque me tirará la misma posición                        módulo me dará posiciones entre los nuevos rangos   


            |------|                                     
            |------|                     |------|
            |  A   |                     | A C  | ---->COLISIONAN           |      |
            |------|                     |------|                           |------|
            |  B   |    ------------>    |   B  |       ------------->      |      |            
            |------|   quiero insertar C |------|       quiero insertar C   |------| 
            |      |                     |      |                           |   A  |
            |------|                     |------|                           |------|
                                                                            |   C  |
                                                                            |------|
                                                                            |      |
                                                                            |------|
                                                                            |   B  |
                                                                            |------|



    - Otro caso también sería cuando solo expandes el tamaño del hash y aplicas la misma funcion sin modificar su tamaño actual, esto ocasionará que todos los elementos que van a ingresar estarán ocupando la misma posición que la tabla anterior, osea:


                                                            |------|
            |------|                                        |   A  |---------|
            |  A   |                                        |------|         |
            |------|                                        |      |         |------> [**]
            |      |    ----------------->                  |------|         |           
            |------|     quiero insertar D                  |  C   |---------|           
            |  C   |                                        |------|                     
            |------|                                        |      |
                                                            |------|
                                                            |      |
                                                            |------|
                                                            |      |
                                                            |------|

        [**] Se debe tener cuidado a la hora de __rehashear__, para evitar este problema hay que __rehashear__ al vector o tabla actual o inicial con el tamaño que uno quiere la idea no es solo agrandar el hash sino cuando agarramos al vector o tabla inicial se tiene que rehashearlo a ese vector.