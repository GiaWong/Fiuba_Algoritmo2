#include "abb.h"
#include "doris.h"
#include <stdio.h>
#define ERROR -1
#define EXITO 0

typedef struct cosa {
	int clave;
	char contenido[10];
} cosa_t;

cosa_t* crear_cosa(int clave){
	cosa_t* c = (cosa_t*)malloc(sizeof(cosa_t));
	if(c)
		c->clave = clave;
	return c;
}

void destruir_cosa(cosa_t* c){
	if(c)
		free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
	if(!elemento1 || !elemento2)
		return 0;

	if(((cosa_t*)elemento1)->clave>((cosa_t*)elemento2)->clave)
		return 1;
	
	if(((cosa_t*)elemento1)->clave<((cosa_t*)elemento2)->clave)
		return -1;
	
	return 0;
}

void destructor_de_cosas(void* elemento){
	if(!elemento)
		return;
	
	destruir_cosa((cosa_t*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
	extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
	
	if(elemento)
		printf("%i ", ((cosa_t*)elemento)->clave);
	
	return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
	extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
	
	if(elemento){
		printf("%i ", ((cosa_t*)elemento)->clave);
		if(((cosa_t*)elemento)->clave == 5)
			return true;
	}

	return false;
}

bool mostrar_acumulado(void* elemento, void* extra){
	if(elemento && extra){
		*(int*)extra += ((cosa_t*)elemento)->clave;
		printf("%i ", *(int*)extra);
	}

	return false;
}

void probar_recorridos_con_iterador_interno(doris_t** doris){
	
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);

	cosa_t* c10= crear_cosa(10);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c15= crear_cosa(15);
	cosa_t* c0= crear_cosa(0);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c13= crear_cosa(13);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c18= crear_cosa(18);
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se inserta el elemento 10 al arbol", arbol_insertar(arbol, c10)==EXITO);
	auxiliar->clave=10;
	doris_asegurar((*doris), "Se busca el elemento 10 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==10);
	
	doris_asegurar((*doris), "Se inserta el elemento 3 al arbol", arbol_insertar(arbol, c3)==EXITO);
	auxiliar->clave=3;
	doris_asegurar((*doris), "Se busca el elemento 3 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==3);
	
	doris_asegurar((*doris), "Se inserta el elemento 0 al arbol", arbol_insertar(arbol, c0)==EXITO);
	auxiliar->clave=0;
	doris_asegurar((*doris), "Se busca el elemento 0 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==0);
	
	doris_asegurar((*doris), "Se inserta el elemento 5 al arbol", arbol_insertar(arbol, c5)==EXITO);
	auxiliar->clave=5;
	doris_asegurar((*doris), "Se busca el elemento 5 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==5);

	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	
	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se busca el elemento 4 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==4);

	doris_asegurar((*doris), "Se inserta el elemento 13 al arbol", arbol_insertar(arbol, c13)==EXITO);
	auxiliar->clave=13;
	doris_asegurar((*doris), "Se busca el elemento 13 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==13);
	
	doris_asegurar((*doris), "Se inserta el elemento 18 al arbol", arbol_insertar(arbol, c18)==EXITO);
	auxiliar->clave=18;
	doris_asegurar((*doris), "Se busca el elemento 18 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==18);
	
	doris_asegurar((*doris), "Se inserta el elemento 15 al arbol", arbol_insertar(arbol, c15)==EXITO);
	auxiliar->clave=15;
	doris_asegurar((*doris), "Se busca el elemento 15 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==15);
	

	printf("Recorrido inorden iterador interno (0 3 4 5 6 10 13 15 18): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido preorden iterador interno (10 3 0 5 4 6 13 18 15): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido postorden iterador interno (0 4 6 5 3 15 18 13 10): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("\nRecorrido inorden hasta encontrar el 5 (0 3 4 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	printf("Recorrido preorden hasta encontrar el 5 (10 3 0 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	printf("Recorrido postorden hasta encontrar el 5 (0 4 6 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	int acumulador=0;
	printf("\nRecorrido inorden acumulando los valores (0 3 7 12 18 28 41 56 74): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
	printf("\n");

	acumulador=0;
	printf("Recorrido preorden acumulando los valores (10 13 13 18 22 28 41 59 74): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
	printf("\n");

	acumulador=0;
	printf("Recorrido postorden acumulando los valores (0 4 10 15 18 33 51 64 74): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
	printf("\n");

	free(auxiliar);
	arbol_destruir(arbol);
}

void probar_recorridos_con_tamanio_insuficiente(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

	cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
	
	cosa_t* elementos[5];
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);

	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2)==EXITO);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	
	doris_asegurar((*doris), "Se inserta el elemento 1 al arbol", arbol_insertar(arbol, c1)==EXITO);
	auxiliar->clave=1;
	doris_asegurar((*doris), "Se busca el elemento 1 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==1);
	
	doris_asegurar((*doris), "Se inserta el elemento 3 al arbol", arbol_insertar(arbol, c3)==EXITO);
	auxiliar->clave=3;
	doris_asegurar((*doris), "Se busca el elemento 3 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==3);
	
	doris_asegurar((*doris), "Se inserta el elemento 5 al arbol", arbol_insertar(arbol, c5)==EXITO);
	auxiliar->clave=5;
	doris_asegurar((*doris), "Se busca el elemento 5 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==5);
	
	doris_asegurar((*doris), "Se inserta el elemento 7 al arbol", arbol_insertar(arbol, c7)==EXITO);
	auxiliar->clave=7;
	doris_asegurar((*doris), "Se busca el elemento 7 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==7);
	printf("\n");

	
	printf("Recorrido inorden deberian salir en orden 1 2 3 4 5 :  ");
	int vector[]={1,2,3,4,5};
	int contador=0;
	int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 5);
	for(int i=0;i<cantidad;i++){
		printf("%i ", elementos[i]->clave);
		if(vector[i]==elementos[i]->clave){
			contador++;
		}

	}
	doris_asegurar((*doris),"Recorrido inorden elementos esperados son iguales ", contador==5);
	printf("\n");

	printf("Recorrido preorden deberian salir en orden 4 2 1 3 6 :  ");
	int vecto[]={4,2,1,3,6};
	int contado=0;
	int cantida = arbol_recorrido_preorden(arbol, (void**)elementos, 5);
	for(int i=0;i<cantida;i++){
		printf("%i ", elementos[i]->clave);
		if(vecto[i]==elementos[i]->clave){
			contado++;
		}
	}
	doris_asegurar((*doris),"Recorrido preorden elementos esperados son iguales ", contado==5);
	printf("\n");

	printf("Recorrido postorden deberian salir en orden 1 3 2 5 7 :  ");
	int vec[]={1,3,2,5,7};
	int cont=0;
	int canti = arbol_recorrido_postorden(arbol, (void**)elementos, 5);
	for(int i=0;i<canti;i++){
		printf("%i ", elementos[i]->clave);
		if(vec[i]==elementos[i]->clave){
			cont++;
		}
	}
	doris_asegurar((*doris),"Recorrido postorden elementos esperados son iguales ", cont==5);
	printf("\n");

	free(auxiliar);
	arbol_destruir(arbol);

}

void probar_recorridos_con_tamanio_suficiente(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

	cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
	
	cosa_t* elementos[10];
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);

	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2)==EXITO);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	
	doris_asegurar((*doris), "Se inserta el elemento 1 al arbol", arbol_insertar(arbol, c1)==EXITO);
	auxiliar->clave=1;
	doris_asegurar((*doris), "Se busca el elemento 1 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==1);
	
	doris_asegurar((*doris), "Se inserta el elemento 3 al arbol", arbol_insertar(arbol, c3)==EXITO);
	auxiliar->clave=3;
	doris_asegurar((*doris), "Se busca el elemento 3 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==3);
	
	doris_asegurar((*doris), "Se inserta el elemento 5 al arbol", arbol_insertar(arbol, c5)==EXITO);
	auxiliar->clave=5;
	doris_asegurar((*doris), "Se busca el elemento 5 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==5);
	
	doris_asegurar((*doris), "Se inserta el elemento 7 al arbol", arbol_insertar(arbol, c7)==EXITO);
	auxiliar->clave=7;
	doris_asegurar((*doris), "Se busca el elemento 7 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==7);
	printf("\n");

	
	printf("Recorrido inorden deberian salir en orden 1 2 3 4 5 6 7 :  ");
	int vector[]={1,2,3,4,5,6,7};
	int contador=0;
	int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
	for(int i=0;i<cantidad;i++){
		printf("%i ", elementos[i]->clave);
		if(vector[i]==elementos[i]->clave){
			contador++;
		}

	}
	doris_asegurar((*doris),"Recorrido inorden elementos esperados son iguales ", contador==7);
	printf("\n");

	printf("Recorrido preorden deberian salir en orden 4 2 1 3 6 5 7 :  ");
	int vecto[]={4,2,1,3,6,5,7};
	int contado=0;
	int cantida = arbol_recorrido_preorden(arbol, (void**)elementos, 10);
	for(int i=0;i<cantida;i++){
		printf("%i ", elementos[i]->clave);
		if(vecto[i]==elementos[i]->clave){
			contado++;
		}
	}
	doris_asegurar((*doris),"Recorrido preorden elementos esperados son iguales ", contado==7);
	printf("\n");

	printf("Recorrido postorden deberian salir en orden 1 3 2 5 7 6 4 :  ");
	int vec[]={1,3,2,5,7,6,4};
	int cont=0;
	int canti = arbol_recorrido_postorden(arbol, (void**)elementos, 10);
	for(int i=0;i<canti;i++){
		printf("%i ", elementos[i]->clave);
		if(vec[i]==elementos[i]->clave){
			cont++;
		}
	}
	doris_asegurar((*doris),"Recorrido postorden elementos esperados son iguales ", cont==7);
	printf("\n");

	free(auxiliar);
	arbol_destruir(arbol);

}


void probar_muchos_nodos(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

	cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);

	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se busca el elemento 4 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==4);
	
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2)==EXITO);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	
	doris_asegurar((*doris), "Se inserta el elemento 1 al arbol", arbol_insertar(arbol, c1)==EXITO);
	auxiliar->clave=1;
	doris_asegurar((*doris), "Se busca el elemento 1 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==1);
	
	doris_asegurar((*doris), "Se inserta el elemento 3 al arbol", arbol_insertar(arbol, c3)==EXITO);
	auxiliar->clave=3;
	doris_asegurar((*doris), "Se busca el elemento 3 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==3);
	
	doris_asegurar((*doris), "Se inserta el elemento 5 al arbol", arbol_insertar(arbol, c5)==EXITO);
	auxiliar->clave=5;
	doris_asegurar((*doris), "Se busca el elemento 5 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==5);
	
	doris_asegurar((*doris), "Se inserta el elemento 7 al arbol", arbol_insertar(arbol, c7)==EXITO);
	auxiliar->clave=7;
	doris_asegurar((*doris), "Se busca el elemento 7 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==7);
	
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);


	auxiliar->clave = 7;
	doris_asegurar((*doris), "Se borra el elemento 7 (nodo hoja)", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 7 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);


	auxiliar->clave = 6;
	doris_asegurar((*doris), "Se borra el elemento 6 (nodo con un hijo)", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 6 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);

	auxiliar->clave = 2;
	doris_asegurar((*doris), "Se borra el elemento 2 (nodo con dos hijos)", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 2 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);


	auxiliar->clave = 4;
	doris_asegurar((*doris), "Se borra el elemento 4 (nodo raiz)", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 4 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);

	auxiliar->clave = 3;
	doris_asegurar((*doris), "Se busca el elemento 3 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==3);

	cosa_t* elementos[10];

	printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
	int vector[]={1,3,5};
	int cot=0;
	int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
	for(int i=0;i<cantidad;i++){
		printf("%i ", elementos[i]->clave);
		if(vector[i]==elementos[i]->clave){
			cot ++;
		}
    }	
	doris_asegurar((*doris),"Recorrido postorden elementos esperados son iguales ", cot==3);
	printf("\n");

	printf("\n\nInserto mas valores y pruebo el iterador interno\n\n");
	cosa_t* c15= crear_cosa(15);
	cosa_t* c0= crear_cosa(0);
	cosa_t* c9= crear_cosa(9);
	cosa_t* c7p= crear_cosa(7);
	cosa_t* c4p= crear_cosa(4);

	doris_asegurar((*doris), "Se inserta el elemento 15 al arbol", arbol_insertar(arbol, c15)==EXITO);
	auxiliar->clave=15;
	doris_asegurar((*doris), "Se busca el elemento 15 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==15);
	
	doris_asegurar((*doris), "Se inserta el elemento 0 al arbol", arbol_insertar(arbol, c0)==EXITO);
	auxiliar->clave=0;
	doris_asegurar((*doris), "Se busca el elemento 0 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==0);
	
	doris_asegurar((*doris), "Se inserta el elemento 9 al arbol", arbol_insertar(arbol, c9)==EXITO);
	auxiliar->clave=9;
	doris_asegurar((*doris), "Se busca el elemento 9 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==9);

	doris_asegurar((*doris), "Se inserta el elemento 7 al arbol", arbol_insertar(arbol, c7p)==EXITO);
	auxiliar->clave=7;
	doris_asegurar((*doris), "Se busca el elemento 7 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==7);

	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4p)==EXITO);
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se busca el elemento 4 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==4);


	printf("Recorrido inorden iterador interno (0 1 3 4 5 7 9 15): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido preorden iterador interno (3 1 0 5 4 15 9 7): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido postorden iterador interno (0 1 4 7 9 15 5 3): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("\nRecorrido inorden hasta encontrar el 5 (0 1 3 4 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	printf("Recorrido preorden hasta encontrar el 5 (3 1 0 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	printf("Recorrido postorden hasta encontrar el 5 (0 1 4 7 9 15 5): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
	printf("\n");

	int acumulador=0;
	printf("\nRecorrido inorden acumulando los valores (0 1 4 8 13 20 29 44): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
	printf("\n");

	acumulador=0;
	printf("Recorrido preorden acumulando los valores (3 4 4 9 13 28 37 44): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
	printf("\n");

	acumulador=0;
	printf("Recorrido postorden acumulando los valores (0 1 5 12 21 36 41 44): ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
	printf("\n");


	free(auxiliar);
	arbol_destruir(arbol);
}

void probar_tres_nodos(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c6= crear_cosa(6);
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);
	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2)==EXITO);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se borra el elemento 4", arbol_borrar(arbol, auxiliar)==EXITO);

	doris_asegurar((*doris), "Se busca al elemento 4 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser 2", ((cosa_t*)arbol_raiz(arbol))->clave==2);
	
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se borra el elemento 6", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 6 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser 2", ((cosa_t*)arbol_raiz(arbol))->clave==2);
	
	
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se borra el elemento 2", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 2 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser nulo", arbol_raiz(arbol)==NULL);
	cosa_t* c4y= crear_cosa(4);
	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4y)==EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	auxiliar->clave=2;
	cosa_t* c2y= crear_cosa(2);
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2y)==EXITO);
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi",((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	cosa_t* c6y= crear_cosa(6);
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6y)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	doris_asegurar((*doris), "Se borra el elemento 6", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 6 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	
	
	free(auxiliar);
	arbol_destruir(arbol);
}
void probar_dos_nodos(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* auxiliar = crear_cosa(0);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c6 = crear_cosa(6);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);
	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4)==EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	doris_asegurar((*doris), "Se inserta el elemento 2 al arbol", arbol_insertar(arbol, c2)==EXITO);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se busca el elemento 2 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==2);
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se borra el elemento 4", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 4 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser 2", ((cosa_t*)arbol_raiz(arbol))->clave==2 );
	doris_asegurar((*doris), "Se inserta el elemento 6 al arbol", arbol_insertar(arbol, c6)==EXITO);
	auxiliar->clave=6;
	doris_asegurar((*doris), "Se busca el elemento 6 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==6);
	auxiliar->clave=2;
	doris_asegurar((*doris), "Se borra el elemento 2", arbol_borrar(arbol, auxiliar)==EXITO);
	doris_asegurar((*doris), "Se busca al elemento 2 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser 6", ((cosa_t*)arbol_raiz(arbol))->clave==6);


	free(auxiliar);
	arbol_destruir(arbol);
}
void probar_un_nodo(doris_t** doris){

	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c4= crear_cosa(4);
	cosa_t* auxiliar = crear_cosa(0);

	doris_asegurar((*doris), "Se crea un nuevo arbol", arbol!=NULL);
	doris_asegurar((*doris), "Se inserta el elemento 4 al arbol", arbol_insertar(arbol, c4) == EXITO);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	
	auxiliar->clave=4;
	doris_asegurar((*doris), "Se busca el elemento 4 en el arbol y este debe estar ahi", ((cosa_t*)arbol_buscar(arbol, auxiliar))->clave==4);
	auxiliar->clave=5;
	doris_asegurar((*doris), "Se intenta borrar el elemento 5 y no se puede borrar porque no existe", arbol_borrar(arbol, auxiliar)==ERROR);
	doris_asegurar((*doris), "El nodo raiz deberia ser 4", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	auxiliar->clave=4;
	doris_asegurar((*doris), "Borro el elemento 4", arbol_borrar(arbol, auxiliar)==EXITO );
	doris_asegurar((*doris), "Busco al elemento 4 y este no debe estar en el arbol", arbol_buscar(arbol, auxiliar)==NULL);
	doris_asegurar((*doris), "El nodo raiz deberia ser nulo", arbol_raiz(arbol)==NULL);
	
	
	free(auxiliar);
	arbol_destruir(arbol);
	
	
}
void probar_con_nulos(doris_t** doris){

	abb_t* arbol = NULL;
	cosa_t* c4= crear_cosa(4);
	cosa_t* c1=NULL;
	cosa_t* auxiliar = crear_cosa(0);


	doris_asegurar((*doris), "El arbol es nulo y esta debe estar vacio", arbol_vacio(arbol)==true);
	doris_asegurar((*doris), "El arbol es nulo y no tiene nodo raiz", arbol_raiz(arbol)==NULL);
	doris_asegurar((*doris), "EL arbol es nulo y no se puede insertar elemento",  arbol_insertar(arbol, c4)==ERROR);
	doris_asegurar((*doris), "No se puede buscar un elemento en un arbol nulo", arbol_buscar(arbol, auxiliar)==NULL);
	auxiliar->clave =7;
	doris_asegurar((*doris), "EL arbol es nulo y no se puede borrar un elemento", arbol_borrar(arbol, auxiliar)==ERROR);

	abb_t* Arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	doris_asegurar((*doris), "Se crea un nuevo arbol", Arbol!=NULL); 
	doris_asegurar((*doris), "No se puede insertar un elemento nulo al arbol", arbol_insertar(arbol, c1)==ERROR);
	doris_asegurar((*doris), "No se puede buscar un elemento nulo en el arbol", arbol_buscar(arbol, c1)==NULL);
	doris_asegurar((*doris), "El nodo raiz es nulo", arbol_raiz(arbol)==NULL);
	doris_asegurar((*doris), "El arbol debe estar vacio por no tener elementos", arbol_vacio(arbol)==true);

	free(auxiliar); free(c4);
	arbol_destruir(Arbol);
	arbol_destruir(arbol);
	

}

int main(){
	doris_t* doris = doris_crear();
	
	printf("\n==>PRUEBAS CON ARBOLES NULOS Y DATOS INEXISTENTES\n");
	probar_con_nulos(&doris);
	printf("\n==>PRUEBAS CON UN SOLO NODO DEL ARBOL\n");
	probar_un_nodo(&doris);
	printf("\n==>PRUEBAS CON DOS NODOS DEL ARBOL\n");
	probar_dos_nodos(&doris);
	printf("\n==>PRUEBAS CON TRES NODOS DEL ARBOL\n");
	probar_tres_nodos(&doris);
	printf("\n==>PRUEBAS CON MUCHOS NODOS DEL ARBOL\n");
	probar_muchos_nodos(&doris);
	
	printf("\n==>PROBAR RECORRIDOS CON TAMANIO SUFICIENTE\n");
	probar_recorridos_con_tamanio_suficiente(&doris);
	printf("\n==>PROBAR RECORRIDOS CON TAMANIO INSUFICIENTE\n");
	probar_recorridos_con_tamanio_insuficiente(&doris);
	printf("\n==>PROBAR RECORRIDOS CON ITERADOR INTERNO\n");
	probar_recorridos_con_iterador_interno(&doris);
	

	doris_estadistica(doris);
	doris_destruir(doris);
	
	return 0;
}
