#include "abb.h"
#define EXITO 0
#define ERROR -1

typedef struct datos{
    void* elemento;
    int estado;
}datos_t;

bool arbol_vacio(abb_t* arbol){

    if(arbol==NULL) return true;
    if(arbol->nodo_raiz==NULL) return true;
    return false;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

    if(comparador==NULL || destructor==NULL) return NULL;
    abb_t* arbol = calloc(1, sizeof(abb_t));
    if(arbol==NULL)  return NULL;
    arbol->comparador=comparador;
    arbol->destructor=destructor;
    return arbol;
}

nodo_abb_t* crear_nodo(nodo_abb_t** nodo, void* elemento){
   
    nodo_abb_t* nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
    if(nuevo_nodo==NULL)  return NULL;
    nuevo_nodo->elemento=elemento;
    (*nodo)=nuevo_nodo;
    return (*nodo);

}

nodo_abb_t* insertar_nodo(nodo_abb_t** nodo, void* elemento, abb_comparador comparador ){
    
    if((*nodo)==NULL){
       return crear_nodo(nodo, elemento);
    }
  
    if(comparador(elemento, (*nodo)->elemento)<0){
        (*nodo)->izquierda = insertar_nodo(&(*nodo)->izquierda, elemento, comparador);
    }else{
        (*nodo)->derecha = insertar_nodo(&(*nodo)->derecha, elemento, comparador);
    }
    return (*nodo);
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(arbol==NULL|| elemento == NULL) return ERROR;
    nodo_abb_t* nodo = insertar_nodo(&arbol->nodo_raiz, elemento, arbol->comparador);
    if(nodo==NULL)  return ERROR;
    return EXITO;
}

void* arbol_raiz(abb_t* arbol){
    
    if(arbol==NULL) return NULL;
    return arbol->nodo_raiz?arbol->nodo_raiz->elemento:NULL;

}


void* buscar_nodo(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){

    if(nodo!=NULL && nodo->elemento!=NULL){

        if(comparador(elemento,  nodo->elemento)==0){
            return  nodo->elemento;
        }else if(comparador(elemento,  nodo->elemento)<0){//va a la izquierda
            return buscar_nodo(nodo->izquierda, elemento, comparador);
        }else if(comparador(elemento,  nodo->elemento)>0){//va a la derecha
            return buscar_nodo(nodo->derecha, elemento, comparador);
        }
       return  nodo->elemento;
    }
    return NULL;
    
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(arbol==NULL || elemento==NULL)  return NULL;
    return buscar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
}

void borrar_todo_nodo(nodo_abb_t** nodo, abb_liberar_elemento destructor){
    if((*nodo)!=NULL){
        
        borrar_todo_nodo(&(*nodo)->izquierda, destructor);
        borrar_todo_nodo(&(*nodo)->derecha, destructor);
        destructor((*nodo)->elemento); 
        (*nodo)->elemento=NULL;    
        free(*nodo);
        (*nodo)=NULL;
    }
}

void arbol_destruir(abb_t* arbol){
    if(arbol!=NULL){
        borrar_todo_nodo(&arbol->nodo_raiz, arbol->destructor);
        free(arbol);
    }
}



void borrar_un_nodo(nodo_abb_t** nodo_p, datos_t* datos, abb_comparador comparador, abb_liberar_elemento destructor ){

    nodo_abb_t** nodo_padre = NULL;
    nodo_abb_t** nodo_actual;
    nodo_abb_t** nodo=NULL;
    void* aux;
    nodo_actual = &(*nodo_p);
  
    while((*nodo_actual)!=NULL){
       
        if(comparador(datos->elemento,(*nodo_actual)->elemento)==0){ 

            if((*nodo_actual)->izquierda==NULL && (*nodo_actual)->derecha==NULL) { 
                if(nodo_padre !=NULL){ //Si tiene padre (no es el nodo raiz) 
                    if((*nodo_padre)->derecha != NULL){
                        if(comparador((*nodo_padre)->derecha->elemento, (*nodo_actual)->elemento)==0){
                            
                            destructor((*nodo_actual)->elemento);
                            (*nodo_actual)->elemento=NULL;
                            free(*nodo_actual);
                            (*nodo_actual) = NULL;
                            datos->estado = EXITO;
                            (*nodo_padre)->derecha = NULL;
                            return;
                        }
                    }
                    if((*nodo_padre)->izquierda != NULL){
                        if(comparador((*nodo_padre)->izquierda->elemento, (*nodo_actual)->elemento)==0){
                            destructor((*nodo_actual)->elemento);
                            (*nodo_actual)->elemento=NULL;
                            free(*nodo_actual);
                            (*nodo_actual) = NULL;
                            datos->estado = EXITO;
                            (*nodo_padre)->izquierda = NULL;
                            return;
                        } 
                    }
                }
                
                destructor((*nodo_actual)->elemento);
                (*nodo_actual)->elemento=NULL;
                free(*nodo_actual);
                (*nodo_actual) = NULL;
                datos->estado = EXITO;
                return;

            }else{
                nodo_padre = &(*nodo_actual);
                 
                if((*nodo_actual)->izquierda!=NULL) {
                    nodo = &(*nodo_actual)->izquierda;
                    while((*nodo)->derecha!=NULL) {
                        nodo_padre = &(*nodo);
                        nodo = &(*nodo)->derecha;
                    }
                }else{
                    nodo = &(*nodo_actual)->derecha;
                    while((*nodo)->izquierda!=NULL) {
                        nodo_padre = &(*nodo);
                        nodo = &(*nodo)->izquierda;
                    }
                }
                aux = (*nodo_actual)->elemento;
                (*nodo_actual)->elemento = (*nodo)->elemento;
                (*nodo)->elemento = aux;
                nodo_actual = &(*nodo);
            }
        }else { 
            nodo_padre = &(*nodo_actual);
            if(comparador(datos->elemento,(*nodo_actual)->elemento) > 0){
                nodo_actual = &(*nodo_actual)->derecha;
            }else if(comparador(datos->elemento,(*nodo_actual)->elemento) < 0){
                nodo_actual = &(*nodo_actual)->izquierda;
            } 
        }
    }

}

int arbol_borrar(abb_t* arbol, void* elemento){

    if(arbol_vacio(arbol)==true || elemento==NULL) return ERROR;
    datos_t dato;
    dato.elemento=elemento;
    dato.estado=ERROR;
    borrar_un_nodo(&arbol->nodo_raiz, &dato, arbol->comparador, arbol->destructor);
    return dato.estado;
}

void llenar_array_en_inorden(int* cantidad_llenado, nodo_abb_t* nodo, void** vector, int tope){

    if(nodo->izquierda !=NULL){
        llenar_array_en_inorden(cantidad_llenado, nodo->izquierda, vector, tope);
    } 
    if((*cantidad_llenado)==tope){
        return;
    }
  
    vector[(*cantidad_llenado)]=nodo->elemento;
    (*cantidad_llenado) ++;

    if(nodo->derecha != NULL){
        llenar_array_en_inorden(cantidad_llenado, nodo->derecha, vector, tope);
    }

}
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol)==true || array==NULL || tamanio_array==0) return 0;
    int cantidad_llenado=0;
    llenar_array_en_inorden(&cantidad_llenado,arbol->nodo_raiz,array,tamanio_array);
    return cantidad_llenado;

}

void llenar_array_en_preorden(int* cantidad_llenado, nodo_abb_t* nodo, void** vector, int tope){
    if((*cantidad_llenado)==tope){
        return;
    }

    vector[(*cantidad_llenado)]=nodo->elemento;
    (*cantidad_llenado) ++;

    if(nodo->izquierda !=NULL){
        llenar_array_en_preorden(cantidad_llenado, nodo->izquierda, vector, tope);
    } 
    if(nodo->derecha != NULL){
        llenar_array_en_preorden(cantidad_llenado, nodo->derecha, vector, tope);
    }
}
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol)==true || array==NULL || tamanio_array==0) return 0;
    int cantidad_llenado=0;
    llenar_array_en_preorden(&cantidad_llenado,arbol->nodo_raiz,array,tamanio_array);
    return cantidad_llenado;
}

void llenar_array_en_postorden(int* cantidad_llenado, nodo_abb_t* nodo, void** vector, int tope){
    
    if(nodo->izquierda !=NULL){
        llenar_array_en_postorden(cantidad_llenado, nodo->izquierda, vector, tope);
    } 
    if(nodo->derecha != NULL){
        llenar_array_en_postorden(cantidad_llenado, nodo->derecha, vector, tope);
    }
    
    if((*cantidad_llenado)==tope){
        return;
    }
   
    vector[(*cantidad_llenado)]=nodo->elemento;
    (*cantidad_llenado) ++;

}
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol)==true || array==NULL || tamanio_array==0) return 0;
    int cantidad_llenado=0;
    llenar_array_en_postorden(&cantidad_llenado,arbol->nodo_raiz,array,tamanio_array);
    return cantidad_llenado;
}


void recorrer_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* entra){
    
    if(nodo->izquierda!=NULL && (*entra) ==false){
        recorrer_inorden(nodo->izquierda, funcion, extra, entra);
    }
    if((*entra)==false){
        
        if(funcion(nodo->elemento, extra)!=false){
            (*entra)=true;
            return;
        }
    }
 
    if(nodo->derecha!=NULL && (*entra)==false){
        recorrer_inorden(nodo->derecha, funcion, extra, entra);
    }

}
void recorrer_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* entra){
    
    
    if(funcion(nodo->elemento, extra)!=false){
        (*entra)=true;
        return;
    }
    if(nodo->izquierda!=NULL && (*entra)==false){
        recorrer_preorden(nodo->izquierda, funcion, extra, entra);
    }
    if(nodo->derecha!=NULL && (*entra)==false){
        recorrer_preorden(nodo->derecha, funcion, extra, entra);
    }

}
void recorrer_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* entra){
    
    
    if(nodo->izquierda!=NULL && (*entra)==false){
        recorrer_postorden(nodo->izquierda, funcion, extra, entra);
    }
    if(nodo->derecha!=NULL && (*entra)==false){
        recorrer_postorden(nodo->derecha, funcion, extra, entra);
    }
    if((*entra)==false){
        if(funcion(nodo->elemento, extra)!=false){
            (*entra)=true;
            return;
        }
    }

}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    
    if(arbol_vacio(arbol)==true) return;

    bool entra=false;

    if(recorrido==ABB_RECORRER_INORDEN)  recorrer_inorden(arbol->nodo_raiz, funcion, extra, &entra);    
    
    if(recorrido==ABB_RECORRER_PREORDEN) recorrer_preorden(arbol->nodo_raiz, funcion, extra, &entra);
    
    if(recorrido==ABB_RECORRER_POSTORDEN) recorrer_postorden(arbol->nodo_raiz, funcion, extra, &entra);


}



