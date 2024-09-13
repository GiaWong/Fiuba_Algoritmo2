#include "hash.h"
#include "hash_iterador.h"
#include "lista.h"
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define ERROR -1
#define EXITO 0
#define MAXIMO_VALOR 100

const double LIMITE_UMBRAL = 0.5;
const size_t MINIMA_CAPACIDAD = 3;
const size_t FACTOR = 31;


typedef struct conjunto_datos{
    char clave[MAXIMO_VALOR];
	void* elemento;
}conjunto_datos_t; 

typedef struct campo{
    bool esta_lleno;
    lista_t* lista;
}campo_t;

struct hash{
	size_t tam;//es la capacidad que tiene
	size_t ocupado;
	hash_destruir_dato_t destructor;
	campo_t* tabla;
};

struct hash_iter{
	size_t tope_max;
	size_t cant_elementos;
	size_t pos;
    lista_iterador_t* lista_iterador;
	campo_t* tabla;	
};

bool es_primo(size_t num){
    size_t var = 2;
    while(var < num/2){
        if(num%var == 0){
            return false;
        }
        var++;
    }
    return true;
}

size_t siguiente_primo(size_t numero){
    if(es_primo(numero)){
        return numero;
    }
    return siguiente_primo(numero + 1);
}

size_t obtener_capacidad(size_t capacidad){

    if(capacidad < MINIMA_CAPACIDAD){
        return MINIMA_CAPACIDAD;
    }
    return siguiente_primo(capacidad);
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
  
    hash_t* hash = calloc(1,sizeof(hash_t));
    if(hash==NULL){
        return NULL;
    }

    hash->destructor = destruir_elemento;
    hash->tam = obtener_capacidad(capacidad);

    hash->tabla = calloc(1,(hash->tam)*sizeof(campo_t));
    if(hash->tabla==NULL){

        free(hash);
        return NULL;
    }
    return hash; 
}

/*
*Destruye cada lista que tiene la tabla, considerando que ya antes se haya liberado
*los datos que almacenaba cada lista respectiva.
*/
void destruir_cada_lista(campo_t* tabla, size_t tamanio){

    if(tabla == NULL){
        return;
    }
    for(size_t i = 0; i<tamanio; i++){
		if(tabla[i].esta_lleno){
			lista_destruir(tabla[i].lista);
		}
	}
}
//uso el iterador externo de la lista para liberar cada elemento almacenada en ella
void liberar_cada_elemento_lista(lista_t* lista,hash_destruir_dato_t destructor){
    
	lista_iterador_t* it = lista_iterador_crear(lista);
	if(!it){
		return;
	}
	conjunto_datos_t* aux;
	while(lista_iterador_tiene_siguiente(it)){
		aux = (conjunto_datos_t*)lista_iterador_siguiente(it);
		if(destructor){
			destructor(aux->elemento);
		}
		free(aux);
	}
	lista_iterador_destruir(it);
}

/* 
*Destruye todos los elementos insertados en la lista pero no destruye a la lista en sí
*sino al contenido que almacena la lista (los datos o elementos).
*/
void destruir_cada_elemento(campo_t* tabla, size_t tamanio, hash_destruir_dato_t destructor){
	
    if(tabla == NULL){
        return;
    } 
    //recorro cada posicion de la tabla
	for(size_t i = 0; i < tamanio; i++){

        liberar_cada_elemento_lista(tabla[i].lista,destructor);
	}
}

size_t multiplicar(size_t base, size_t aux){
    size_t rpta= base*aux;
    return rpta;
}

size_t hash_funcion(size_t tamanio_capacidad, char* clave){
    
    size_t longitud = strlen(clave);
    size_t var=0; 
	for (size_t i = 0; i<longitud; i++){
        var += (size_t)clave[i]*multiplicar(FACTOR,i);
		
	}
	return (var % tamanio_capacidad);   
}

bool insertar_en_tabla(campo_t* tabla, size_t pos, conjunto_datos_t datos){
    
    if(tabla==NULL){
        return false;
    }
    if(!tabla[pos].esta_lleno){
        
        tabla[pos].lista=lista_crear();
        if(tabla[pos].lista==NULL){
            return false;
        }
        tabla[pos].esta_lleno=true;
    }
    conjunto_datos_t* aux = calloc(1, sizeof(conjunto_datos_t));
    if(aux==NULL){
        return false;
    }
    aux->elemento = datos.elemento;
    strcpy(aux->clave, datos.clave);
    
    if(lista_insertar(tabla[pos].lista, aux)==ERROR){
        free(aux);
        return false;
    }
    
    return true;
}

/*
*Reinserta en una nueva lista a los elementos contenidos en la tabla antigua.
*La lista ingresada por parametro debe contener los elementos a reubicar.
*devuelve true si se pudo reubicar correctamente los elementos o caso contrario
*devuelve false.
*/
bool reubicar_en_la_lista(campo_t* nueva_tabla, size_t capacidad, lista_t* lista){
    if(lista==NULL || nueva_tabla==NULL){
        return false;
    }
    //voy a recorrer a la lista usando el iterador externo
    lista_iterador_t* itera = lista_iterador_crear(lista);
	if(itera==NULL){
		return false;
	}

	conjunto_datos_t* conjunto_de_datos ;
	size_t posicion;	

	while(lista_iterador_tiene_siguiente(itera)){

		conjunto_de_datos = (conjunto_datos_t*)lista_iterador_siguiente(itera);
		posicion = hash_funcion(capacidad, conjunto_de_datos->clave);

		if(!insertar_en_tabla(nueva_tabla, posicion, *conjunto_de_datos)){
			lista_iterador_destruir(itera);
			return false;
		}
	}
	lista_iterador_destruir(itera);

	return true;
}

/*
*Redimensiona la capacidad del hash 
*/
bool hash_redimencionar(hash_t* hash){

    if(hash==NULL){
        return false;
    }
    size_t var=multiplicar(hash->tam,3);
    size_t nuevo_tam = siguiente_primo(var);
    //creo una nueva tabla con el nuevo tamaño
    campo_t* nueva_tabla = calloc(1,nuevo_tam*sizeof(campo_t));
    if(nueva_tabla==NULL){
        return false;
    }
    //recorro el hash antiguo
    for(size_t k=0; k<hash->tam; k++){

        if(hash->tabla[k].esta_lleno){

            if(reubicar_en_la_lista(nueva_tabla, nuevo_tam, hash->tabla[k].lista)==false){

                destruir_cada_elemento(nueva_tabla, nuevo_tam, NULL);
                free(nueva_tabla);
                return false;
            }
        }
    }

    destruir_cada_elemento(hash->tabla,hash->tam,NULL);
    destruir_cada_lista(hash->tabla, hash->tam);
    free(hash->tabla);
    hash->tabla = nueva_tabla;
    hash->tam = nuevo_tam;
    
    return true;
}

/*
*El limite umbral será la mitad de la capacidad total, osea si considero que 
*tanto los ocupados  dividido por el espacio total ---> 5/5 = 1 y su mitad 0,5 y este
*será su umbral limite.
*
*El tamaño del hash (capacidad)  no debe ser cero. Devuelve true si la cantidad de elementos
* en el hash supera al LIMITE DEL UMBRAL
*/
bool supera_umbral(hash_t* hash){
    double umbral = (double)hash->ocupado/((double)hash->tam);
    if(umbral > LIMITE_UMBRAL){
        return true;
    }
    return false;
}

int buscar_posicion_de_coincidencia(lista_t* lista, char* clave){
    
    if(lista == NULL){
        return ERROR;
    } 
	lista_iterador_t* itera = lista_iterador_crear(lista);
	if(itera == NULL){
		return ERROR;
	}
    conjunto_datos_t* aux;
	int posicion = 0;

	while(lista_iterador_tiene_siguiente(itera)){

		aux = (conjunto_datos_t*)lista_iterador_siguiente(itera);
		if(strcmp(aux->clave,clave) == 0){
			lista_iterador_destruir(itera);
			return posicion;
		}
		posicion++;	
	}
	lista_iterador_destruir(itera);
	return ERROR;
}

int hash_quitar(hash_t* hash, const char* clave){
    
    if(hash == NULL || clave == NULL){
        return ERROR;
    } 

	size_t pos = hash_funcion(hash->tam, (char*)clave);
    if(!hash->tabla[pos].esta_lleno){
        return ERROR;
    }
   
    //busca en la lista si coinciden
    int posicion = buscar_posicion_de_coincidencia(hash->tabla[pos].lista, (char*)clave);
    if(posicion==ERROR){
        return ERROR;
    }
    //guardo los datos de una de las posiciones de la lista en el AUX
    conjunto_datos_t* aux = (conjunto_datos_t*)lista_elemento_en_posicion(hash->tabla[pos].lista,(size_t)posicion);	
	if(aux == NULL){
        return ERROR;
    } 
    //Borro en esa posicion dentro de la lista
    if(lista_borrar_de_posicion(hash->tabla[pos].lista,(size_t)posicion) == ERROR){
		return ERROR;
	}

    //libero al elemento que se guardó antes en el AUX
    if(hash->destructor){
		hash->destructor(aux->elemento);
	}
	free(aux);
	hash->ocupado--;
    
	return EXITO;
}

bool hash_contiene(hash_t* hash, const char* clave){
    
    if(hash == NULL || clave == NULL){
        return false;
    } 

    size_t pos = hash_funcion(hash->tam, (char*)clave);
    if(!hash->tabla[pos].esta_lleno){
        return false;
    }
    //busca en la lista si coinciden y devuelve la posicion en donde está
    int posicion = buscar_posicion_de_coincidencia(hash->tabla[pos].lista, (char*)clave);
    if(posicion==ERROR){
        return false;
    }
    return true;
}


/*
*Si hay clave repetida este elimina a la que estaba anteriormente en la lista y despues
*se vuelve a insertar en la tabla
*/
int hash_insertar(hash_t* hash, const char* clave, void* elemento){
    
    if(hash == NULL || clave == NULL){
        return ERROR;
    }
    if(*clave=='\0'){
        return ERROR;
    }
    if(supera_umbral(hash)==true){
        if(hash_redimencionar(hash)==false){
            return ERROR;
        }
    }
    size_t pos = hash_funcion(hash->tam, (char*)clave);
    
    if(hash_contiene(hash,(char*)clave)){
        hash_quitar(hash,(char*)clave);
    }

    conjunto_datos_t aux;
    strcpy(aux.clave,(char*)clave);
    aux.elemento=elemento;
   
    if(!insertar_en_tabla(hash->tabla, pos, aux)){
        return ERROR;
    }
    hash->ocupado ++;
    return EXITO;

}

/*
*Devuelve el elemento correspondiente a la clave recibida.
*/
void* buscar_posicion(campo_t tabla, char*clave){

    if(tabla.esta_lleno){
        int pos = buscar_posicion_de_coincidencia(tabla.lista, clave);
        if(pos==ERROR){
            return NULL;
        } 
        conjunto_datos_t* aux = (conjunto_datos_t*)lista_elemento_en_posicion(tabla.lista,(size_t)pos);	
        if(aux==NULL){
            return NULL;
        } 
        return aux->elemento;
    }
    return NULL;
}

void* hash_obtener(hash_t* hash, const char* clave){
    if(hash == NULL || clave == NULL){
        return NULL;
    } 
	size_t pos = hash_funcion(hash->tam, (char*)clave);
    return buscar_posicion(hash->tabla[pos], (char*)clave); 
}

size_t hash_cantidad(hash_t* hash){
    if(hash == NULL){
        return 0;
    }
    return hash->ocupado;
}

void hash_destruir(hash_t* hash){
    if(hash == NULL){
        return;
    } 
    //libero memoria de los elementos que contine cada lista
	destruir_cada_elemento(hash->tabla,hash->tam,hash->destructor);
    //libero memoria de cada casilla de la tabla que apuntan a una lista inicial
	destruir_cada_lista(hash->tabla,hash->tam);
    //libero la tabla en sí
	free(hash->tabla);
    //y luego al hash mismo
	free(hash);
}

/*
--------------------------------------------------------------------------------------------
                             <<< HASH ITERADOR INTERNO >>>
---------------------------------------------------------------------------------------------
*/
size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
   
    if(hash==NULL ||! funcion){
        return 0;
    } 
	size_t cont = 0;
	for(size_t i = 0; i< hash->tam;i++){

		if(hash->tabla[i].esta_lleno==true){
            //uso el iterador externo de la lista
            lista_iterador_t* itera = lista_iterador_crear(hash->tabla[i].lista);
            if(!itera){
                return 0;
            }
            conjunto_datos_t* var;
            while(lista_iterador_tiene_siguiente(itera)){

                var = (conjunto_datos_t*)lista_iterador_siguiente(itera);
                cont ++;
                if(funcion(hash,var->clave,aux)==true){

                    lista_iterador_destruir(itera);
                    return cont;
                }
            }
            lista_iterador_destruir(itera);
		}	
	}
	return cont;
}

/*
--------------------------------------------------------------------------------------------
                             <<< HASH ITERADOR EXTERNO >>>
---------------------------------------------------------------------------------------------
*/

hash_iterador_t* hash_iterador_crear(hash_t* hash){

    if(hash==NULL){
        return NULL;
    } 
	hash_iterador_t* itera = calloc(1,sizeof(hash_iterador_t));
	if(itera==NULL){
        return NULL;
    } 
	itera->tabla = hash->tabla;
	itera->tope_max = hash->tam;
	itera->cant_elementos = hash->ocupado;
	return itera;
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
    if(iterador==NULL){
        return false;
    } 
    if(iterador->cant_elementos > 0){
        return true;
    }
	return false;
}

const char* hash_iterador_siguiente(hash_iterador_t* iterador){

    if(iterador == NULL){ 
        return NULL;
    }

    if(iterador->lista_iterador == NULL){//si la lista iterador no fue creada
    
        for(size_t i = iterador->pos; i < iterador->tope_max; i++){

            if(iterador->tabla[i].esta_lleno && !lista_vacia(iterador->tabla[i].lista)){
            
                iterador->pos = i;
                lista_iterador_t* itera = lista_iterador_crear(iterador->tabla[i].lista);
                if(itera==NULL){
                    return NULL;
                } 

                iterador->lista_iterador = itera;
                conjunto_datos_t* var = (conjunto_datos_t*)lista_iterador_siguiente(iterador->lista_iterador);
                if(var==NULL){
                    return NULL;
                }
                iterador->cant_elementos --;
                return var->clave;
            }
        }
    }

    if(iterador->lista_iterador != NULL){//si la lista_iterador fue creada

        if(lista_iterador_tiene_siguiente(iterador->lista_iterador) == true){
           
            conjunto_datos_t* aux = (conjunto_datos_t*)lista_iterador_siguiente(iterador->lista_iterador);
            if(aux==NULL){
                return NULL;
            }
            iterador->cant_elementos --;
            return aux->clave;
        }
        lista_iterador_destruir(iterador->lista_iterador);
        iterador->lista_iterador = NULL;
    }
	return NULL;
}

void hash_iterador_destruir(hash_iterador_t* iterador){

    if(iterador==NULL){
        return;
    }
	lista_iterador_destruir(iterador->lista_iterador);
	free(iterador);
}
