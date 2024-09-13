
# ABB
El programa muestra por pantalla todas las pruebas que se realizan para saber
si lo que se ha implementado en abb.c no falla a la hora de testearlo.

La compilación del programa se realiza con el comando:

    gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -oo

Al ejecutar con el ./ el programa mostrará todas las pruebas que tiene, de tal forma que 
los clasifiqué  como:

    ==>PRUEBAS CON ARBOLES NULOS Y DATOS INEXISTENTES
    ==>PRUEBAS CON UN SOLO NODO DEL ARBOL
    ==>PRUEBAS CON DOS NODOS DEL ARBOL
    ==>PRUEBAS CON TRES NODOS DEL ARBOL
    ==>PRUEBAS CON MUCHOS NODOS DEL ARBOL
    ==>PROBAR RECORRIDOS CON TAMANIO SUFICIENTE
    ==>PROBAR RECORRIDOS CON TAMANIO INSUFICIENTE
    ==>PROBAR RECORRIDOS CON ITERADOR INTERNO


Algunas de todas las pruebas mostrará por pantalla los elementos que va teniendo actualmente cada recorrido del arbol.

Al final de todas las pruebas se mostrará un mensaje de cuantas
pruebas exitosas hubo.

---
El planteo esquemático en cómo lo pensé para encarar la estructura del arbol fue lo siguiente:

Teniendo en cuenta que esto [o] es un puntero (una forma representativa). 

                                                                      cosa_t
                           abb_t                nodo_abb_t          |---------|
                                             |-------------|        |  clave  |
        arbol        |---------------|       |elemento [o] | ====>  |contenido|
         [o]  ====>  | nodo_raiz [o] | ====> | izq    der  |   |    |---------|  
                |    | comparador[o] |   |   | [o]    [o]  |   |
                |    | destructor[o] |   |   |--|------|---|   |
                |    |---------------|   |      Y      Y       |
                |                        |     NULL   NULL     |
                |                        |                     |
                Y                        Y                     Y
            arbol apunta          nodo_raiz apunta       elemento apunta


Basandome en ese esquema comencé a realizar el algoritmo.

*Algo que quiero aclarar*: En la funcion arbol_borrar() intenté realizarlo recursivamente, pero valgrind se quejaba mucho,
asi que opté por la parte iterativa esta vez me salió más fluido el codigo.

---

PREGUNTAS DEL PDF:

1. __Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.__
     
RPTA: Un arbol binario no es mas que un nodo que tiene como maximo dos divisiones (Binario de dos), y 
      siempre puede tener ceros hijos, un hijos o dos hijos, nada mas. 

                             nodo_raiz               nodo_raiz            nodo_raiz
                                / \                     / \                  / \
                               /   \                   /   \                /   \
                        nodo iz    nodo der      nodo iz   nulo           nulo  nulo
                
El ABB incorpora la idea de arbol binario y crece conforme se vaya insertando elementos o datos, dando aparciencia a un "arbol" estructurandose con muchos nodos, nodos padre, nodos hijos, nodo hoja, etc.
      
La idea de una busqueda binaria en un arrays toma mucha importancia para el arbol binario de busqueda, lo que permite el ABB es buscar elementos o datos distribuidos segun algun criterio, osea si al lado izquierdo del nodo raiz van los mayores o los menores, o si al lado derecho del nodo raiz van los mayores o los menores, la convencio dependerá de quien lo implemente.

                                                 nodo_raiz               
                                                    / \                   
                                                   /   \                   
                                            nodo_iz     nodo_der    
                                            / \            / \
                                         nodo nodo       nodo nodo   
                                          /\   /\         /\   /\
                                          ..   ..         ..   ..
                                          ..   ..         ..   ..
                                          ..   ..         ..   .. 
                            



2. __Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario
no tenerla.__

RPTA: Como estamos trabajando con memoria dinámica y estamos accediendo a una parte de eso, es de correcto uso 
      liberarlo para así tener mas espasio disponible despues de haberlo usado anteriormente, entonces para liberar memoria "prestada"
      la funcion destruir hace esa tarea, se encarga de hacerlo. Entonces si uno quiere implementar un TDA es de buena programacion
      brindarle al usuario una funcion que destruya toda las memorias reservadas antes y durante la ejecucion del programa, así evitamos
      desperdiciar espacio que ya no usamos o que ya no se usa en el programa.
      El usuario al tener la funcion destruir(suponiendo que esté bien implementada y que respete las condiciones que se requiere para usar dicha funcion) se
      puede asegurar de que él o ella no va a tener que preocuparse por implementar codigos de más para liberar memoria, ya que el usuario
      creo yo que debe abstraerse de esos temas porque el implementador o implementadora del TDA ya debe o debió considerar esa funcion.
      Es mayormente para no darle mas trabajo al usuario o al sistema operativo \(°<°)/, así se facilita y mejora la experiencia a la hora de usar el programa.



3. __¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.__

RPTA: Explicaré por parte:

===>Para la funcion arbol_crear() tiene complejidad O(1) pues:


    abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){  =====>O(1)

        if(comparador==NULL || destructor==NULL) return NULL;    =====>O(1)
        abb_t* arbol = calloc(1, sizeof(abb_t));                 =====>O(1)
        if(arbol)==NULL)  return NULL;                           =====>O(1)
        arbol->comparador=comparador;                            =====>O(1)
        arbol->destructor=destructor;                            =====>O(1)
        return arbol;                                            =====>O(1)
    }



===>Para la funcion arbol_insertar() tiene complejidad O(n) pues:


    nodo_abb_t* insertar_nodo(nodo_abb_t** nodo, void* elemento, abb_comparador comparador ){ ========>T(n)=O(n)
    
        if((*nodo)==NULL){
            return crear_nodo(nodo, elemento);                                               ========>O(1)
        }
    
        if(comparador(elemento, (*nodo)->elemento)<0){
            (*nodo)->izquierda = insertar_nodo(&(*nodo)->izquierda, elemento, comparador);  ========>O(n), pues en el peor de los casos puede llamarse n veces a insertar_nodo(). por la profundidad del arbol
        }else{
            (*nodo)->derecha = insertar_nodo(&(*nodo)->derecha, elemento, comparador);      ========>O(n), pues en el peor de los casos puede llamarse n veces a insertar_nodo(). por la profundidad del arbol
        }
        return (*nodo);                                                                     ========>O(1)
    }



    int arbol_insertar(abb_t* arbol, void* elemento){                                           ========>T(n)=max(O(1),O(n),O(1),O(1))  = O(n)
        if(arbol==NULL|| elemento == NULL) return ERROR;                                    ========>O(1)
        nodo_abb_t* nodo = insertar_nodo(&arbol->nodo_raiz, elemento, arbol->comparador);   ========>O(n)
        if(nodo==NULL) return ERROR;                                                        ========>O(1)
        return EXITO;                                                                       ========>O(1)
    }



===>Para la funcion arbol_borrar() tiene complejidad O(n) pues:

En este caso voy a reducir un poco el codigo si veo que su complejidad es O(1).

    void borrar_un_nodo(nodo_abb_t** nodo_p, datos_t* datos, abb_comparador comparador, abb_liberar_elemento destructor ){

        nodo_abb_t** nodo_padre = NULL;    ---|
        nodo_abb_t** nodo_actual;             |
        nodo_abb_t** nodo=NULL;               |>>>>>>>> La asignacion es O(1)
        void* aux;                            |
        nodo_actual = &(*nodo_p);          ---|
        :
        :
        :    

    }



    int arbol_borrar(abb_t* arbol, void* elemento){===========>T(n)=max(O(1),O(1),O(1),O(1),O(n),O(1)) ==> T(n)=O(n)

        if(arbol_vacio(arbol)==true || elemento==NULL) return ERROR;===========>O(1)
        datos_t dato;           ===========>O(1)
        dato.elemento=elemento; ===========>O(1)
        dato.estado=ERROR; ===========>O(1)
        borrar_un_nodo(&arbol->nodo_raiz, &dato, arbol->comparador, arbol->destructor); ===========>O(n) 
        return dato.estado;===========>O(1)
    }



===>Para la funcion arbol_raiz() tiene complejidad O(1) pues:


    void* arbol_raiz(abb_t* arbol){                                 =======>O(1)
        if(arbol==NULL) return NULL;                                =======>O(1)
        return  arbol->nodo_raiz?arbol->nodo_raiz->elemento:NULL;   =======>O(1)
    }



===>Para la funcion arbol_vacio() tiene complejidad O() pues:

    bool arbol_vacio(abb_t* arbol){  ============>T(n)=O(1)

        if(arbol==NULL) return true;               =======>O(1)
        if(arbol->nodo_raiz==NULL) return true     ========>O(1)
        return false;                              =======>O(1)
    }



===>Para la funcion arbol_destruir() tiene complejidad O(n) pues:


    void borrar_todo_nodo(nodo_abb_t** nodo, abb_liberar_elemento destructor){============>T(n) = O(n)
        if((*nodo)!=NULL){                                          
        
            borrar_todo_nodo(&(*nodo)->izquierda, destructor);                ============>O(n), pues en el peor de los casos este se va a llamar tantas veces hasta que el nodo sea nulo 
            borrar_todo_nodo(&(*nodo)->derecha, destructor);                  ============>O(n), pues en el peor de los casos este se va a llamar tantas veces hasta que el nodo sea nulo
            destructor((*nodo)->elemento);                                    ============>O(1)
            (*nodo)->elemento=NULL;                                           ============>O(1)
            free((*nodo));                                                    ============>O(1)
            (*nodo)=NULL;                                                     ============>O(1)
        }
    }

    void arbol_destruir(abb_t* arbol){                              ============>T(n)=max(O(n),O(1))  = O(n)
        if(arbol_vacio(arbol)==false){                              
            borrar_todo_nodo(&arbol->nodo_raiz, arbol->destructor); ============>O(n)
            free(arbol);                               ============>O(1)
        }
    }





===>Para la funcion abb_con_cada_elemento() tiene complejidad O(n) pues:


    void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){ ============>T(n)=max(O(1), O(1), O(1), O(n), O(n), O(n)) = O(n)
    
        if(arbol_vacio(arbol)==true) return;         ============>O(1)

        bool entra=false;                              ============>O(1)

        if(recorrido==ABB_RECORRER_INORDEN)  recorrer_inorden(arbol->nodo_raiz, funcion, extra, &entra);         ============>O(n)
    
        if(recorrido==ABB_RECORRER_PREORDEN) recorrer_preorden(arbol->nodo_raiz, funcion, extra, &entra);          ============>O(n)
    
        if(recorrido==ABB_RECORRER_POSTORDEN) recorrer_postorden(arbol->nodo_raiz, funcion, extra, &entra);          ============>O(n)

    }

En conclusión:

En el ABB va depender mucho su complejidad con el tema de cuan largo es o cuan profundo está, no es lo mismo tener:


                    esto               nodo_raiz                 que esto        nodo_raiz
                                        /      \                                      /\
                                       /        \                                    /  \
                                    n             n                                 n    n
                                  /   \          / \                              /  \  /  \
                                 /     \        /   \                            x    x x   x
                                n       n      x     x
                              /   \    /  \    
                            n      n  x    x
                           / \    / \  
                          n    n x   x     
                        /  \  / \  
                      n     n x  x
                      /\    /\
                      ..    ..
                      ..    ..

