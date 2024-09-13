# Lista

El programa muestra por pantalla todas las pruebas que se realizan para saber
si lo que se ha implementado en lista.c no falla a la hora de testearlo.

La compilación del programa se realiza con el mismo comando que indicaron
en el pdf de TDA lista.

Al ejecutar con el __./__ el programa mostrará una de las primeras partes de las pruebas,
hasta llegar a la ultima linea donde se deberá ingresar un enter para continuar 
con la siguiente prueba, en ese caso es opcional si se desea quitar de las minipruebas
a la funcion guiar() se puede hacer libremente, lo puse mas que nada para poder detenerme
en cada bloque de prueba y poder leerlo sin perderme.

En sí consta de tres pruebas generales y cada una de las pruebas tienen subpruebas,
las pruebas generales estan indicadas de color verde y las subpruebas estan señaladas
con la flecha __"==>"__ de color verde y cada subprueba está enumerada de acuerdo a cuantas
pruebas tenga cada prueba general, como por ejemplo:

    ==>Prueba que la lista se comporte como lista:
        ==>[1/5] Prueba con lista nula
        ==>[2/5] Prueba con lista vacia
        ==>[3/5] Prueba con lista no vacia
        ==>[4/5] Prueba usando el iterador externo
        ==>[5/5] Prueba usando el iterador interno

    ==>Prueba el comportamiento de cola:
        ==>[1/2]Prueba Encolando
        ==>[2/2]Prueba Desencolando

    ==>Prueba el comportamiento de pila:
        ==>[1/2] Prueba Apilando
        ==>[2/2] Prueba Desapilando

---

Algunas de todas las pruebas mostrará por pantalla los elemntos que va
teniendo actualmente la lista.
Al final de todas las pruebas se mostrará un mensaje de cuantas
pruebas exitosas hubo, todas las pruebas exitosas estan indicadas con color 
amarillo y las de falla estan de color rojo.

El funcionamiento particular de la implementacion en lista.c fueron por ejemplo:

1. Para la pila, lo pensé de la siguiente forma:


        Insertando: 1
                    1 2
                    1 2 3
                    1 2 3 4 
                    1 2 3 4 5

        Desapilando:1 2 3 4 5
                    1 2 3 4
                    1 2 3
                    1 2
                    1
                    (vacio)



2. Para la cola, lo pensé de la siguiente forma:


        Insertando:   1
                      1 2
                      1 2 3
                      1 2 3 4
                      1 2 3 4 5
    
        Desencolando: 1 2 3 4 5
                      2 3 4 5
                      3 4 5
                      4 5
                      5
                      (vacio)

En la funcion __lista_encolar()__, ví conveniente reutilizar codigo de la funcion
lista_apilar() ya que como se vé en la piramide tiene el mismo comportamiento de insertación.

Otro dato importante es que también pensé  a mi estructura de lista como:

        lista  apunta    lista_t   inicial apunta         sig apunta a otro nodo
         ___            _________                 ________
        |_°_|   --->   | inicial |     --->      |  datos | --->elemnto
                       |  tope   |               |  sig   | --->     _______
                       -----------               ----------         |  datos | --->NULL
                                                   nodo             |  sig   | --->NULL
                                                                    ----------
                                                                       nodo


Por lo que en la función lista_vacia() yo realizo dos comprobaciones, si lista es igual a NULL o
si lista->inicial es igual a NULL.

---

### CONCEPTOS TEORICOS:

1. ¿Qué es lo que entendés por una lista?¿Cuáles son las diferencias entre ser simple o doblemente enlazada?

    - Entiendo a una lista como una especie de agrupamiento de elementos seguidos continuamente, y 
      la diferencia entre una lista simplemente enlazada y doblemente enlazadas es que en la simple
      se puede conectar una sola vez a un nodo proximo independientemente si está dirigido hacia adelante
      o hacia atras, sólo posee un solo enlace o puntero.
      En cambio una lista de doble enlace puede conectarse a su nodo antecesor y sucesor, o dependiendo del enfoque
      que el programador le dá, en sí tiene dos enlaces o punteros. 


2. ¿Cuáles son las características fundamentales de las pilas?¿Y de las colas?

    - Puede ser a la hora de quitar elementos de una lista, una pila se desapila siempre cuando
      el ultimo elemento insertado es el primero en salir, y para una cola se desencola siempre y cuando
      cumpla que el primer elemento insertado es el primero en salir.


3. ¿Qué es un iterador?¿Cuál es su función?

    - Es un puntero que te permite recorrer los elementos ya sea de un array, de una lista, etc.
       te facilita tener un control sobre el recorrido de los datos y evitar mucho tiempo de complejidad.


4. ¿En qué se diferencia un iterador interno de uno externo?

    - El iterador externo permite que cualquier usuario pueda construirse una iteracion pero ya no se preocuparía por ciertas implementaciones ya que para su uso está más simplificada y mejorada, en cambio un iterador interno no está a disposicion del
      usuario manipular el como esta implementado,simplemente lo usa confiando en que está bien implementada.

