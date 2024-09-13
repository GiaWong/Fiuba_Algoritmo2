#include "lista.h"
#include "colores.h"
#include "telis.h"
#include <stdbool.h>
#include <stdio.h>

#define ERROR -1
#define EXITO 0

void guiar(){
  printf("\n"COLOR_BLANCO"==>"COLOR_NORMAL" Presione enter para continuar a la siguiente prueba...");
  getchar();
}

void mostar_elementos_caracteres(lista_t** lista){

  printf("\nElementos en la lista: \n");
  for(size_t i=0;i<lista_elementos((*lista));i++){
    printf("%c ", *(char*)lista_elemento_en_posicion((*lista), i));
  }
  printf("\n\n");
}

void mostar_elementos_enteros(lista_t** lista){
  printf("\nElementos en la lista: \n");
  for(size_t i=0;i<lista_elementos((*lista));i++){
    printf("%i ", *(int*)lista_elemento_en_posicion((*lista), i));
  }
  printf("\n\n");
}

void probar_con_mas_elementos(telis_t* telis, lista_t** lista, char* d, char* w, char* s){

  int respuesta;

  respuesta = lista_insertar((*lista), d);
  telis_asegurar(telis, "Inserto el elemnto 'd' y debe estar 'd' en la lista", respuesta == EXITO);
  
  respuesta = lista_insertar((*lista), w);
  telis_asegurar(telis, "Inserto el elemnto 'w' y debe estar 'w' en la lista", respuesta == EXITO);
 

  respuesta = lista_insertar((*lista), s);
  telis_asegurar(telis, "Inserto el elemnto 's' y debe estar 's' en la lista", respuesta == EXITO);

}

void probar_dos_elementos(telis_t* telis, lista_t** lista, char* b, char* c){

  int respuesta;

  respuesta = lista_insertar((*lista), b);
  telis_asegurar(telis, "Inserto el elemnto 'b' y debe estar 'b' en la lista", respuesta == EXITO);
  
  respuesta = lista_insertar((*lista), c);
  telis_asegurar(telis, "Inserto el elemnto 'c' y debe estar 'c' en la lista", respuesta == EXITO);

}

void probar_un_solo_elemento(telis_t* telis, lista_t** lista, char* a){

  int respuesta = lista_insertar((*lista), a);
  telis_asegurar(telis, "Inserto el elemnto 'a' y debe estar 'a' en la lista", respuesta == EXITO);

}
void mostar_ultimo_elemento(lista_t** lista, telis_t* telis){

  void* respuesta = lista_ultimo((*lista));
  telis_asegurar(telis, "Devuelve el ultimo elemento de la lista", respuesta != NULL);
  if(respuesta != NULL){
    printf("\nEl ultimo elemento de la lista es: %c\n ", *(char*)lista_ultimo((*lista)));
  }
  
}

void mostrar_elemento(void* elemento, void* contador){

  if(elemento && contador)
    printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
  
}

void prueba_iterador_externo(lista_t* lista, telis_t* telis){

  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[4/5] Prueba usando el iterador externo: \n\n");
  
  lista_iterador_t* ite = lista_iterador_crear(lista);
  for(size_t i=0;i<lista_elementos(lista);i++){
    telis_asegurar(telis, "El elemento  de la lista coinciden con el iterador externo" ,*(char*)lista_elemento_en_posicion(lista, i) == *(char*)lista_iterador_siguiente(ite));
  }
  lista_iterador_destruir(ite);


  lista_iterador_t* it = lista_iterador_crear(lista);
  printf("\nEl iterador externo muestra a los siguientes elementos: ");
  while(lista_iterador_tiene_siguiente(it))
    printf("%c ", *(char*)lista_iterador_siguiente(it));
    
  printf("\n\n");
  lista_iterador_destruir(it);


  lista_iterador_t* itera = NULL;
  telis_asegurar(telis,"Iterador NULL no tiene siguiente",lista_iterador_tiene_siguiente(itera) == false);
  telis_asegurar(telis,"Iterador NULL no devuelve el proximo elemento", lista_iterador_siguiente(itera) == NULL);
}

void prueba_iterador_interno(lista_t* lista, telis_t* telis){
  
  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[5/5] Prueba usando el iterador interno: \n\n");
  
  int contador=0;
  lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
  telis_asegurar(telis,"La cantidad de elementos del iterador es igual a la lista", contador==lista_elementos(lista));
  printf("\n");

}
void probar_lista_vacia(telis_t** telis){


  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[2/5] Prueba con lista vacia:\n\n");
  int contador=0;
  size_t pos=4;
  lista_t* lista = lista_crear();
  telis_asegurar((*telis), "Se pudo reservar memoria para la lista vacia", lista!=NULL);
  telis_asegurar((*telis),"La lista empieza sin elementos", lista_elementos(lista)==0);
  lista_con_cada_elemento(lista,mostrar_elemento,(void*)&contador);
  telis_asegurar((*telis),"No hay elementos en toda la lista",lista_elementos(lista) == contador);
  telis_asegurar((*telis),"El ultimo elemento de la lista es NULL",lista_ultimo(lista)==NULL);
  telis_asegurar((*telis),"No se puede borrar el ultimo elemento de una lista porque está vacia",lista_borrar(lista)==ERROR);
  telis_asegurar((*telis),"No se puede borrar en posicion porque la lista está vacia",lista_borrar_de_posicion(lista,pos)==ERROR);
  telis_asegurar((*telis),"No se puede mostrar el elemento de una posicion porque la lista está vacia",lista_elemento_en_posicion(lista, pos) == NULL);
  telis_asegurar((*telis),"La lista está vacia", lista_vacia(lista)==true);
  lista_destruir(lista);
  telis_avisar("Se liberó la memoria reservada de la lista");

}

void probar_lista_nula(telis_t** telis){

  lista_t* aux = NULL;
  int elemento = 2;
  size_t pos = 3;

  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[1/5] Prueba con lista nula:\n\n");
  telis_asegurar((*telis), "Inserto un elemento a una lista nula y el elemento no se debe insertar", lista_insertar(aux, &elemento) == ERROR);
  telis_asegurar((*telis), "Inserto un elemento en una posicion de una lista nula y el elemento no se debe insertar", lista_insertar_en_posicion(aux, &elemento, pos) == ERROR);
  telis_asegurar((*telis), "No se puede borrar el ultimo elemento de una lista nula porque es nula", lista_borrar(aux) == ERROR);
  telis_asegurar((*telis), "No se puede borrar un elemento en una posicion porque la lista es nula", lista_borrar_de_posicion(aux, pos) == ERROR);
  telis_asegurar((*telis), "No puede devolver un elemento de una posicion indicada porque la lista es nula", lista_elemento_en_posicion(aux, pos) == NULL);
  telis_asegurar((*telis), "No puede devolver el ultimo elemento de la lista porque la lista es nula", lista_ultimo(aux) == NULL);
  telis_asegurar((*telis), "La lista es nula", lista_vacia(aux)==true);
  telis_asegurar((*telis), "No devuelve la cantidad de elementos que tiene la lista porque es nula", lista_elementos(aux) == EXITO);
  telis_asegurar((*telis), "No se puede apilar porque la lista es nula", lista_apilar(aux, &elemento) == ERROR);
  telis_asegurar((*telis), "No se puede desapilar porque la lista es nula", lista_desapilar(aux) == ERROR);
  telis_asegurar((*telis), "No hay tope porque la lista es nula", lista_tope(aux) == NULL );
  telis_asegurar((*telis), "No se puede encolar porque la lista es nula", lista_encolar(aux, &elemento) == ERROR );
  telis_asegurar((*telis), "No se puede desencolar porque la lista es nula", lista_desencolar(aux) == ERROR );
  telis_asegurar((*telis), "No devuelve el primer elemento de la cola porque la lista es nula", lista_primero(aux) == NULL );

}

void probar_operaciones_lista(telis_t* telis){

  probar_lista_nula(&telis);
  probar_lista_vacia(&telis);
  
  char  q='q', r='r', t='t', g='g';
  char a='a', b='b', c='c', d='d', w='w', s='s';
  int respuesta;


  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[3/5] Prueba con lista no vacia:\n\n");
  lista_t* lista = lista_crear();
  telis_asegurar(telis, "Se pudo reservar memoria para la lista", lista!=NULL);
 
  probar_un_solo_elemento(telis,  &lista, &a);
  mostar_elementos_caracteres(&lista);
  probar_dos_elementos(telis, &lista, &b, &c);
  mostar_elementos_caracteres(&lista);
  probar_con_mas_elementos(telis,&lista, &d,&w,&s);
  mostar_elementos_caracteres(&lista);
  

  respuesta = lista_insertar_en_posicion(lista, &g, 100);
  telis_asegurar(telis, "Inserto g en posicion que no existe, este tiene que estar insertado al final de la lista", respuesta == EXITO);
  mostar_elementos_caracteres(&lista);
  respuesta =lista_insertar_en_posicion(lista, &q, 1);
  telis_asegurar(telis, "Inserto q en la segunda posicion de la lista y esta debe estar en la segunda posicion de la lista", respuesta == EXITO);
  mostar_elementos_caracteres(&lista);
  respuesta =lista_insertar_en_posicion(lista, &r, 0);
  telis_asegurar(telis, "Inserto  r en la primera posicion de la lista y esta debe estar en la primera posicion de la lista", respuesta == EXITO);
  mostar_elementos_caracteres(&lista);
  respuesta =lista_insertar_en_posicion(lista, &t, 3);
  telis_asegurar(telis, "Inserto  t en la cuarta posicion de la lista y esta debe estar en la cuarta posicion de la lista", respuesta == EXITO);
  mostar_elementos_caracteres(&lista);

  mostar_ultimo_elemento(&lista, telis);

  respuesta =lista_borrar(lista);
  telis_asegurar(telis,"Elimina de la lista al elemento de la ultima posicion",respuesta == EXITO );
  mostar_elementos_caracteres(&lista);
  

  respuesta=lista_borrar_de_posicion(lista, 0);
  telis_asegurar(telis,"Se elimina el primer elemento de la lista",respuesta == EXITO );
  mostar_elementos_caracteres(&lista);
  respuesta=lista_borrar_de_posicion(lista, 1);
  telis_asegurar(telis,"Se elimina el segundo elemento de la lista",respuesta == EXITO );
  mostar_elementos_caracteres(&lista);
  respuesta=lista_borrar_de_posicion(lista, 2);
  telis_asegurar(telis,"Se elimina el tercer elemento de la  lista",respuesta == EXITO );
  mostar_elementos_caracteres(&lista);
  respuesta=lista_borrar_de_posicion(lista, 13);
  telis_asegurar(telis,"Se elimina el ultimo elemento  de la lista",respuesta == EXITO );
  mostar_elementos_caracteres(&lista);
  
  
  prueba_iterador_externo(lista, telis);
  prueba_iterador_interno(lista, telis);
  
  lista_destruir(lista);
  telis_avisar("Se liberó la memoria reservada de la lista");
}


void prueba_pila_con_caracteres(telis_t** telis, lista_t** pila){
  
  char* algo="ABEJA";
  
  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[1/2] Pruebo Apilando:\n\n");
  for(int i=0;algo[i]!= 0;i++){

    printf("\nApilo: %c", algo[i]);
    telis_asegurar((*telis),"La letra tiene que estar en la pila",lista_apilar((*pila), &algo[i]) == EXITO );
    mostar_elementos_caracteres(pila);
  }

  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[2/2] Pruebo Desapilando:\n\n");
  while(!lista_vacia((*pila))){
    printf("\nDesapilo: %c", *(char*)lista_tope((*pila)));
    telis_asegurar((*telis),"La ultima letra se tiene que desapilar",lista_desapilar((*pila)) == EXITO );
    mostar_elementos_caracteres(pila);
  }
  printf("\n");

}

void probar_operaciones_pila(telis_t* telis){
  
  lista_t* pila = lista_crear();
  telis_asegurar(telis, "Se pudo reservar memoria para la pila", pila!=NULL);
  prueba_pila_con_caracteres(&telis, &pila);
  lista_destruir(pila);
  telis_avisar("Se liberó la memoria reservada de la lista");

}

void prueba_cola_con_enteros(telis_t**telis, lista_t** cola){
  
  int numeros[]={1,2,3,4,5,6};

  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[1/2]Pruebo Encolando:\n\n");
  for(size_t i=0;i<sizeof(numeros)/sizeof(int);i++){

    printf("\nEncolo %i\t", numeros[i]);
    telis_asegurar((*telis),"Encolo en la primera fila de la lista", lista_encolar((*cola), &numeros[i])==EXITO);
    mostar_elementos_enteros(cola);

  }
  printf("\n\n"COLOR_VERDE"==>"COLOR_NORMAL"[2/2] Pruebo Desencolando:\n\n");
  while(!lista_vacia((*cola))){
    printf("\nDesencolo: %i \t", *(int*)lista_primero((*cola)));
    telis_asegurar((*telis),"Desencolo la primera fila de la lista", lista_desencolar((*cola))==EXITO);
    mostar_elementos_enteros(cola);
  }
  printf("\n");
}

void probar_operaciones_cola(telis_t* telis){
  
  lista_t* cola = lista_crear();
  telis_asegurar(telis, "Se pudo reservar memoria para la cola", cola!=NULL);
  prueba_cola_con_enteros(&telis, &cola);
  lista_destruir(cola);
  telis_avisar("Se liberó la memoria reservada de la lista");

}


int main(){
  
  telis_t telis;
  telis.pruebas_exitosas =0;
  telis.pruebas_totales =0;

  printf(COLOR_NORMAL"\n"COLOR_VERDE"==> Pruebo que la lista se comporte como lista"COLOR_NORMAL"\n");
  probar_operaciones_lista(&telis);
  guiar();
  
  printf(COLOR_NORMAL"\n"COLOR_VERDE"==> Pruebo el comportamiento de cola"COLOR_NORMAL"\n");
  probar_operaciones_cola(&telis);
  guiar();

  printf(COLOR_NORMAL"\n"COLOR_VERDE"==> Pruebo el comportamiento de pila"COLOR_NORMAL"\n");
  probar_operaciones_pila(&telis);

  telis_mostrar_estadistica(&telis);

  return 0;
}






