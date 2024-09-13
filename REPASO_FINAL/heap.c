#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ERROR -1
#define OK 0
#define MAX_POSICION 100

void mostrar_arbol(int* buffer, int n){
  printf("\n");
  int niveles = 0;
  for(int restantes=n;restantes>0;restantes>>=1)
    niveles++;
  
  int n_nodo=0;
  for(int nivel=0;nivel<niveles;nivel++){
    int posicion = 1<<(niveles-nivel-1);
    
    for(int nodo=0;nodo<(1<<nivel);nodo++){
      for(int i=1;i<posicion;i++){
	if(i<=posicion/2-1 || buffer[2*n_nodo+1]==0)
	  printf("  ");
	else{
	  if(i == posicion/2)
	    printf(" ┌");
	  else printf("――");
	}
      }
      
      if(buffer[n_nodo]!=0){
	int valor = buffer[n_nodo]<100?buffer[n_nodo]:99;
	printf("%2d", valor);
      }
      else{
	printf("  ");
      }
      
      for(int i=0;i<posicion;i++){
	if(i>=posicion/2 || buffer[2*n_nodo+2]==0)
	  printf("  ");
	else{
	  if(i == posicion/2-1)
	    printf("―┐");
	  else printf("――");
	}
      }
      n_nodo++;
    }
    printf("\n");
  }
}


typedef struct{
    int* vector;
    int tope;
}heap_t;

/*
*
*
*/
heap_t* heap_crear(){
    heap_t* heap=calloc(1, sizeof(heap_t));
    heap->vector=malloc(MAX_POSICION);
    return heap;
}
/*
*
*
*/
heap_t* heap_crear_desde_vector(int* vector, int n){
    heap_t* heap = calloc(1, sizeof(heap_t));
    heap->vector=vector;
    heap->tope=n;
    return heap;
}
/*
*
*
*/
int posicion_padre(int n){
    return (n-1)/2;
}
/*
*
*
*/
int posicion_hijo_derecho(int n){
    return (2*n)+2;
}
/*
*
*
*/
int posicion_hijo_izquierdo(int n){
    return (2*n)+1;
}
/*
*
*
*/
void swap(int* vector, int i, int j){
    int aux=vector[i];
    vector[i]=vector[j];
    vector[j]=aux;
}
/*
*
*
*/
void sift_up(heap_t* heap, int n){
    if(n==0 || heap==NULL){
        return;
    }
    int padre=posicion_padre(n);
    if(heap->vector[n] > heap->vector[padre]){
  
        swap(heap->vector, n, padre);
        sift_up(heap, padre);
    }
}
/*
*
*
*/
int heap_insertar(heap_t* heap, int elemento){
    if(heap==NULL){
        return ERROR;
    }
    heap->vector[heap->tope]=elemento;
    heap->tope++;
    sift_up(heap, heap->tope-1);
    return OK;
}
/*
*
*
*/
void sift_down(heap_t* heap, int n){
    int pos_derecha = posicion_hijo_derecho(n);
    int pos_izquierda = posicion_hijo_izquierdo(n);
    int pos_candidata = -1;
    if(heap->tope-1 < pos_izquierda){
        return;
    }
    if(heap->tope-1 >= pos_derecha && heap->vector[pos_derecha] > heap->vector[pos_izquierda]){
        pos_candidata = pos_derecha;
    }else{
        pos_candidata = pos_izquierda;
    }
    if(heap->vector[pos_candidata] > heap->vector[n]){
        
        swap(heap->vector, n, pos_candidata);
        sift_down(heap, pos_candidata);
    }
}
/*
*
*
*/
int heap_extraer_raiz(heap_t* heap){
    int aux = heap->vector[0];
    swap( heap->vector, 0, heap->tope-1);
    heap->tope --;
    sift_down(heap,0);
    return aux;
}
/*
*
*
*/
void heap_destruir(heap_t* heap){
    if(heap==NULL){
        return;
    }
    free(heap->vector);
    free(heap);
}
/*
*
*
*/
heap_t* heapify(int* vector, int n){
    heap_t* heap = heap_crear_desde_vector(vector, n);
    
    for(int i=posicion_padre(n); i>=0; i--){
        sift_down(heap, i);
    }
    return heap;
}
/*
*
*
*/
void heap_sort(int* vector, int n){
    heap_t* heap = heapify(vector, n);

    while(heap->tope > 0){
        heap_extraer_raiz(heap);
        
    }
    free(heap);
    
    
}

int main(){

    heap_t* heap= heap_crear();

    heap_insertar(heap,1);
    heap_insertar(heap,10);
    heap_insertar(heap,25);
    heap_insertar(heap,6);
    heap_insertar(heap,45);
    heap_insertar(heap,89);
    heap_insertar(heap,3);
    mostrar_arbol(heap->vector, heap->tope);
    printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
    mostrar_arbol(heap->vector, heap->tope);

    heap_destruir(heap);

    int vector[] = {6,1,3,2,9,7,15,24};
    int cantidad= sizeof(vector)/sizeof(int);
    heap_sort(vector, cantidad);
    for(int i=0; i<cantidad; i++){
        printf("%i ", vector[i]);
    }



    return 0;
}