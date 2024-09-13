#include "lista.h"
#include <stdlib.h>

#define ERROR -1
#define EXITO 0

typedef struct nodo{
    void* datos;
    struct nodo *sig;

}nodo_t;

struct lista{
    nodo_t* inicial;
    size_t tope;
};

struct lista_iterador{
    size_t indice;
    lista_t lista;
};


lista_t* lista_crear(){
    lista_t* lista = calloc(1, sizeof(lista_t));
    if(lista == NULL)
        return NULL;
    
    return lista;
}

bool lista_vacia(lista_t* lista){
    if(lista == NULL || lista->inicial==NULL)
       return true;
    return false;
}

size_t lista_elementos(lista_t* lista){
    if(lista==NULL ){
        return 0;
    }
    return lista->tope;
}

int lista_insertar(lista_t* lista, void* elemento){
    
    if(lista==NULL){
        return ERROR;
    }

    if(lista_vacia(lista) == true){

        lista->inicial = calloc(1, sizeof(nodo_t));
        if(lista->inicial == NULL){
            return ERROR;
        }
        lista->inicial->datos = elemento;
        lista->tope ++; 
        return EXITO;
    }
    nodo_t* tmp = NULL;

    tmp = lista->inicial;
    while(tmp->sig != NULL){
        tmp = tmp->sig;
    }
    tmp->sig= calloc(1, sizeof(nodo_t));
    if(tmp->sig == NULL){
        return ERROR;
    }

    tmp->sig->datos = elemento;
    lista->tope ++;
    return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

    if(lista_vacia(lista)== true ){
        return NULL;
    }


    int contador=0;
    nodo_t* aux = lista->inicial;
    while(aux != NULL && posicion<lista->tope){
        
        if(contador == posicion){
            return aux->datos;
        }   
        aux = aux->sig;
        contador++;
        
    }
    return NULL;
}

void* lista_ultimo(lista_t* lista){
    if(lista_vacia(lista)==true){
        return NULL;
    }

    nodo_t* aux = lista->inicial;
    while(aux->sig != NULL){
        aux= aux->sig;
    }
    return aux->datos;

}


int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

    if(lista==NULL){
       return ERROR;
    }
    // En caso de no existir la posicion indicada, lo inserta al final.
    if(posicion >= lista->tope){
        return lista_insertar(lista, elemento);
    }
  
    if(posicion == 0 && lista_vacia(lista) == false){
        nodo_t* temp = lista->inicial;
        lista->inicial = calloc(1,sizeof(nodo_t));
        if(lista->inicial == NULL){
            return ERROR;
        }
        lista->inicial->datos=elemento;
        lista->inicial->sig = temp;
   
        lista->tope ++;

        return EXITO;
    }

    nodo_t* actual = lista->inicial; 
    int contador=0; 

    while(actual->sig != NULL && contador != (posicion-1)){
        actual = actual->sig;
        contador++;
    }
    nodo_t* aux = calloc(1,sizeof(nodo_t));
    if(aux== NULL){
        return ERROR;
    }

    aux->datos = elemento;
    aux->sig=actual->sig;
    actual->sig = aux;
    lista->tope++;

    return EXITO;
 
}

int lista_borrar(lista_t* lista){
    if(lista_vacia(lista) == true){
        return ERROR;
    }
    nodo_t* tmp = lista->inicial;
    if(tmp->sig != NULL){//significa que hay más de un nodo en la lista
        while((tmp->sig)->sig != NULL){
            tmp=tmp->sig;
        }
        free(tmp->sig);
        tmp->sig = NULL;
        lista->tope --;
    }else{
        free(lista->inicial);
        lista->inicial = NULL;
        lista->tope --;
    }
    return EXITO;

}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(lista_vacia(lista)==true){
       return ERROR;
    }
    // En caso de no existir la posicion indicada, elimina el final.
    if(posicion >= lista->tope){
        return lista_borrar(lista);
    }
    int contador =0;
    
    nodo_t* temp = lista->inicial;

    if(posicion == 0){
        
        lista->inicial=lista->inicial->sig;
        lista->tope --;
        free(temp);
        return EXITO;
    }
    
    while(contador + 1 != posicion){
        temp=temp->sig;
        contador++;
    }
    nodo_t* temp2 = temp->sig;
    temp->sig=(temp->sig)->sig;
    free(temp2);
    lista->tope --;
    return EXITO;
}



void lista_destruir(lista_t* lista){

    while( lista_vacia(lista) == false){
        
        nodo_t* tmp = lista->inicial;
        lista->inicial=lista->inicial->sig;
        lista->tope --;
        free(tmp);
    }
    
    free(lista);
}


int lista_apilar(lista_t* lista, void* elemento){

    if(lista==NULL){
        return ERROR;
    }
    return lista_insertar(lista, elemento);

}


int lista_desapilar(lista_t* lista){
    if(lista==NULL){
        return ERROR;
    }
    return lista_borrar(lista);

}

void* lista_tope(lista_t* lista){
    if(lista==NULL){
        return NULL;
    }
    return lista_ultimo(lista);

}

void* lista_primero(lista_t* lista){
    if(lista_vacia(lista)==true){
        return NULL;
    }
    return lista->inicial->datos;
}

int lista_encolar(lista_t* lista, void* elemento){

    return lista_apilar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    if(lista_vacia(lista)==true){
        return ERROR;
    }
    
    if(lista->inicial->sig == NULL){
        return lista_borrar(lista);
    }
    
    nodo_t* tmp = lista->inicial;
    lista->inicial=lista->inicial->sig;
    free(tmp);
    lista->tope --;
    return EXITO;

}


lista_iterador_t* lista_iterador_crear(lista_t* lista){

    if(lista_vacia(lista)==true){
        return NULL;
    }
    lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
    if(iterador==NULL){
        return NULL;
    }
    iterador->lista = (*lista);
    return iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(iterador==NULL){
        return false;
    }

    return iterador->indice < lista_elementos(&iterador->lista);
}


void* lista_iterador_siguiente(lista_iterador_t* iterador){
    if(iterador==NULL || lista_iterador_tiene_siguiente(iterador) == false){
        return NULL;
    }
    
    void* elemento = iterador->lista.inicial->datos;
    iterador->lista.inicial=iterador->lista.inicial->sig;
    iterador->indice ++;
    
    return elemento;
}


void lista_iterador_destruir(lista_iterador_t* iterador){
    if(iterador==NULL){
        return;
    }
    free(iterador);
}


void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto){
   
    if(lista_vacia(lista)==true){
        return;
    }
    lista_t tmp = (*lista);
    
    for(size_t j=0; j<lista_elementos(lista);j++){
        
        void* elemento = tmp.inicial->datos;
        tmp.inicial = tmp.inicial->sig;
        funcion(elemento, contexto);
      
        
    }
    
}




