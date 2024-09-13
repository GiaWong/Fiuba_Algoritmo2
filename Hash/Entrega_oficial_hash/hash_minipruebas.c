#include "hash.h"
#include "hash_iterador.h"
#include "doris.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0

char* duplicar_string(const char* s){
  if(!s)
    return NULL;
  
  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

void destruir_string(void* elemento){
  if(elemento){
    printf("\nLibero a las patentes:  %s\n", (char*)elemento);
    free(elemento);
  }
}

bool mostrar_patente(hash_t* hash, const char* clave, void* aux){
  if(!clave)
    return true;

  aux=aux;
  hash=hash;
  
  printf("******* %s\n", clave);

  return false;
}

/*
*************************************************************
              DISTINTAS PRUEBAS CON CREAR HASH
*************************************************************
*/
void probar_crear_hash_nulos(doris_t** doris){

  hash_t* hash=hash_crear(NULL,3);
  doris_asegurar((*doris), "Se crear un hash con destructor nulo", hash!=NULL); 
  hash_destruir(hash);

}

void probar_crear_hash_capacidad_menor(doris_t** doris){

  hash_t* hash=hash_crear(destruir_string,2);
  doris_asegurar((*doris), "Se crear un hash con capacidad menor a la indicada", hash!=NULL); 
  hash_destruir(hash);

}

void probar_crear_hash_completo(doris_t** doris){

  hash_t* hash=hash_crear(destruir_string,3);
  doris_asegurar((*doris), "Se crear un hash completo", hash!=NULL); 
  hash_destruir(hash);

}
/*
*************************************************************
              DISTINTAS PRUEBAS CON INSERTAR HASH
*************************************************************
*/
void probar_insertando_hash_nulo(doris_t** doris){

  char* descripcion = duplicar_string("El vendedor de mango no vende banana");
  doris_asegurar((*doris), "No se puede insertar elementos con hash nulo", hash_insertar(NULL,"ABC34", descripcion)==ERROR); 
  free(descripcion);

}

void probar_insertando_hash_inexistente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash==NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  char* descripcion = duplicar_string("El vendedor de mango no vende banana");
  doris_asegurar((*doris), "No se puede insertar elemento invalido en un hash creado", hash_insertar(hash,"", descripcion)==ERROR); 
  free(descripcion);
  hash_destruir(hash);

}

void probar_insertando_hash_uno_solo(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash==NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  hash_destruir(hash);
}

void probar_insertando_hash_varios(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el segundo elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el tercer elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el cuarto elemento en el hash correctamente", hash_insertar(hash,"PR214", duplicar_string("Patente de Vanessa"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el quinto elemento en el hash correctamente", hash_insertar(hash,"P42T1", duplicar_string("Patente de Franco"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el sexto elemento en el hash correctamente", hash_insertar(hash,"P00A2", duplicar_string("Patente de Ariel"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el septimo elemento en el hash correctamente", hash_insertar(hash,"SATURNO", duplicar_string("Patente de Terra"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el octavo elemento en el hash correctamente", hash_insertar(hash,"VENUS", duplicar_string("Patente de Asgard"))==EXITO);
  
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercer elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  doris_asegurar((*doris), "El cuarto elemento insertado coincide con lo que contiene", hash_contiene(hash, "PR214")==true );
  doris_asegurar((*doris), "El quinto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P42T1")==true );
  doris_asegurar((*doris), "El sexto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P00A2")==true );
  doris_asegurar((*doris), "El septimo elemento insertado coincide con lo que contiene", hash_contiene(hash, "SATURNO")==true );
  doris_asegurar((*doris), "El octavo elemento insertado coincide con lo que contiene", hash_contiene(hash, "VENUS")==true );

  hash_destruir(hash);
  
}

/*
*************************************************************
              DISTINTAS PRUEBAS CON OBTENER HASH
*************************************************************
*/
void probar_obteniendo_con_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No se puede obtener una clave con hash nulo", hash_obtener(NULL,"P00A2")==NULL);
}

void probar_obteniendo_con_hash_clave_inexistente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "No se puede obtener una clave inexistente", hash_obtener(hash,"OL976")==NULL);

  hash_destruir(hash);

}

void probar_obteniendo_con_hash_clave_valido(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO);
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );

  void* elemento=hash_obtener(hash,"A4214");
  doris_asegurar((*doris), "Se obtiene una clave valida", elemento!=NULL);
  if(elemento==NULL){
    hash_destruir(hash);
    return;
  }

  doris_asegurar((*doris), "Coincide la clave valida con la insertada", hash_contiene(hash,"A4214")==true);
  hash_destruir(hash);

}
/*
*************************************************************
              DISTINTAS PRUEBAS CON CONTENIDO HASH
*************************************************************
*/

void probar_contenido_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No hay el contenido de una clave con hash nulo", hash_contiene(NULL,"A98D7")==false);
}

void probar_contenido_clave_inexistente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
 
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "No hay el contenido de una clave inexistente con hash valido", hash_contiene(hash,"A952F")==false);
  
  hash_destruir(hash);

}

void probar_contenido_clave_y_hash_valido(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Existe el contenido de  un elemento con clave valida", hash_contiene(hash,"A4214")==true);
  
  hash_destruir(hash);

}
/*
*************************************************************
              DISTINTAS PRUEBAS CON CANTIDAD HASH
*************************************************************
*/
void probar_cantidad_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No hay cantidad con hash nulo", hash_cantidad(NULL)==0);
}

void probar_cantidad_hash_vacio(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  doris_asegurar((*doris), "No hay cantidad con un hash sin elementos", hash_cantidad(hash)==0);
  hash_destruir(hash);
}

void probar_cantidad_varios_elementos(doris_t** doris){
  
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 
  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"PR214", duplicar_string("Patente de Vanessa"))==EXITO); 

  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercer elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  doris_asegurar((*doris), "El cuarto elemento insertado coincide con lo que contiene", hash_contiene(hash, "PR214")==true );

  doris_asegurar((*doris), "La cantidad del hash coincide con la cantidad de elementos insertados", hash_cantidad(hash)==4);
  
  hash_destruir(hash);

}
/*
*************************************************************
              DISTINTAS PRUEBAS CON QUITAR HASH
*************************************************************
*/
void probar_quitar_elemento_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No se puede quitar un elemento con hash nulo", hash_quitar(NULL,"AB985")==ERROR);
}

void probar_quitar_elemento_inexistente(doris_t** doris){
  
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "No se puede quitar un elemento con clave inexistente", hash_quitar(hash,"AB862")==ERROR);

  hash_destruir(hash);

}

void probar_quitar_todo_elemento_existente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el segundo elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el tercer elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el cuarto elemento en el hash correctamente", hash_insertar(hash,"PR214", duplicar_string("Patente de Vanessa"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el quinto elemento en el hash correctamente", hash_insertar(hash,"P42T1", duplicar_string("Patente de Franco"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el sexto elemento en el hash correctamente", hash_insertar(hash,"P00A2", duplicar_string("Patente de Ariel"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el septimo elemento en el hash correctamente", hash_insertar(hash,"SATURNO", duplicar_string("Patente de Terra"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el octavo elemento en el hash correctamente", hash_insertar(hash,"VENUS", duplicar_string("Patente de Asgard"))==EXITO);

  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercero elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  doris_asegurar((*doris), "El cuarto elemento insertado coincide con lo que contiene", hash_contiene(hash, "PR214")==true );
  doris_asegurar((*doris), "El quinto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P42T1")==true );
  doris_asegurar((*doris), "El sexto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P00A2")==true );
  doris_asegurar((*doris), "El septimo elemento insertado coincide con lo que contiene", hash_contiene(hash, "SATURNO")==true );
  doris_asegurar((*doris), "El octavo elemento insertado coincide con lo que contiene", hash_contiene(hash, "VENUS")==true );

  doris_asegurar((*doris), "Se pudo quitar el primer elemento insertado ", hash_quitar(hash,"A4214")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el segundo elemento insertado ", hash_quitar(hash,"PQ452")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el tercer elemento insertado ", hash_quitar(hash,"FO523")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el cuarto elemento insertado ", hash_quitar(hash,"PR214")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el quinto elemento insertado ", hash_quitar(hash,"P42T1")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el sexto elemento insertado ", hash_quitar(hash,"P00A2")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el septimo elemento insertado ", hash_quitar(hash,"SATURNO")==EXITO);
  doris_asegurar((*doris), "Se pudo quitar el octavo elemento insertado ", hash_quitar(hash,"VENUS")==EXITO);
  
  doris_asegurar((*doris), "El primer elemento insertado no se encuentra en el hash", hash_contiene(hash, "A4214")==false );
  doris_asegurar((*doris), "El segundo elemento insertado no se encuentra en el hash", hash_contiene(hash, "PQ452")==false );
  doris_asegurar((*doris), "El tercer elemento insertado no se encuentra en el hash", hash_contiene(hash, "FO523")==false );
  doris_asegurar((*doris), "El cuarto elemento insertado no se encuentra en el hash", hash_contiene(hash, "PR214")==false );
  doris_asegurar((*doris), "El quinto elemento insertado no se encuentra en el hash", hash_contiene(hash, "P42T1")==false );
  doris_asegurar((*doris), "El sexto elemento insertado no se encuentra en el hash", hash_contiene(hash, "P00A2")==false );
  doris_asegurar((*doris), "El septimo elemento insertado no se encuentra en el hash", hash_contiene(hash, "SATURNO")==false );
  doris_asegurar((*doris), "El octavo elemento insertado no se encuentra en el hash", hash_contiene(hash, "VENUS")==false );

  hash_destruir(hash);
}
/*
*************************************************************
            DISTINTAS PRUEBAS CON ITERADOR INTERNO
*************************************************************
*/
void probar_iterador_interno_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No se puede iterar con un hash nulo", hash_con_cada_clave(NULL,mostrar_patente,NULL)==0);
}

void probar_iterador_interno_funcion_nula(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta un elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO);
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true ); 
  doris_asegurar((*doris), "No se puede iterar con funcion nula", hash_con_cada_clave(hash,NULL,NULL)==0);

  hash_destruir(hash);

}

void probar_iterador_interno_hash_valido(doris_t** doris){
  
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el segundo elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el tercero elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el cuarto elemento en el hash correctamente", hash_insertar(hash,"PR214", duplicar_string("Patente de Vanessa"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el quinto elemento en el hash correctamente", hash_insertar(hash,"P42T1", duplicar_string("Patente de Franco"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el sexto elemento en el hash correctamente", hash_insertar(hash,"P00A2", duplicar_string("Patente de Ariel"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el septimoelemento en el hash correctamente", hash_insertar(hash,"SATURNO", duplicar_string("Patente de Terra"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el octavo elemento en el hash correctamente", hash_insertar(hash,"VENUS", duplicar_string("Patente de Asgard"))==EXITO);

  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercero elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  doris_asegurar((*doris), "El cuarto elemento insertado coincide con lo que contiene", hash_contiene(hash, "PR214")==true );
  doris_asegurar((*doris), "El quinto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P42T1")==true );
  doris_asegurar((*doris), "El sexto elemento insertado coincide con lo que contiene", hash_contiene(hash, "P00A2")==true );
  doris_asegurar((*doris), "El septimo elemento insertado coincide con lo que contiene", hash_contiene(hash, "SATURNO")==true );
  doris_asegurar((*doris), "El octavo elemento insertado coincide con lo que contiene", hash_contiene(hash, "VENUS")==true );
  
  doris_asegurar((*doris), "Se iteró todos los elementos insertados", hash_con_cada_clave(hash,mostrar_patente,NULL)==8);
  hash_destruir(hash);

}
/*
*************************************************************
            DISTINTAS PRUEBAS CON ITERADOR EXTERNO
*************************************************************
*/
void probar_iterador_externo_crear_hash_valido(doris_t** doris){
  
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  
  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  doris_asegurar((*doris), "Se crea un iterador con hash valido", iterador!=NULL);
  if(iterador == NULL){
    printf("\nError al crear el iterador\n");
    hash_destruir(hash);
    return;
  }
  hash_iterador_destruir(iterador);
  hash_destruir(hash);

}

void probar_iterador_externo_crear_hash_nulo(doris_t** doris){
  doris_asegurar((*doris), "No se crea el iterador con hash nulo", hash_iterador_crear(NULL)==NULL);
}

void probar_iterador_externo_siguiente(doris_t** doris){
  
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el segundo elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el tercero elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 

  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercero elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  doris_asegurar((*doris), "Se crea un iterador con hash valido", iterador!=NULL);
  if(iterador == NULL){
    printf("\nError al crear el iterador\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return;
  }

  doris_asegurar((*doris), "Se itera con iterador valido y tiene siguiente valido", hash_iterador_siguiente(iterador)!=NULL);
  hash_iterador_destruir(iterador);
  hash_destruir(hash);

}

void probar_iterador_externo_tiene_siguiente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }

  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el segundo elemento en el hash correctamente", hash_insertar(hash,"PQ452", duplicar_string("Patente de Kevin"))==EXITO); 
  doris_asegurar((*doris), "Se inserta el tercer elemento en el hash correctamente", hash_insertar(hash,"FO523", duplicar_string("Patente de Maria"))==EXITO); 

  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  doris_asegurar((*doris), "El segundo elemento insertado coincide con lo que contiene", hash_contiene(hash, "PQ452")==true );
  doris_asegurar((*doris), "El tercero elemento insertado coincide con lo que contiene", hash_contiene(hash, "FO523")==true );
  
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  doris_asegurar((*doris), "Se crea un iterador con hash valido", iterador!=NULL);
  if(iterador == NULL){
    printf("\nError al crear el iterador\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return;
  }

  doris_asegurar((*doris), "El iterador_tiene_siguiente SI tiene siguiente", hash_iterador_tiene_siguiente(iterador)==true);
  hash_iterador_destruir(iterador);
  hash_destruir(hash);

}

void probar_iterador_externo_no_tiene_siguiente(doris_t** doris){

  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf("\nERROR AL CREAR EL HASH\n");
    return;
  }
 
  doris_asegurar((*doris), "Se inserta el primer elemento en el hash correctamente", hash_insertar(hash,"A4214", duplicar_string("Patente de Laura"))==EXITO); 
  doris_asegurar((*doris), "El primer elemento insertado coincide con lo que contiene", hash_contiene(hash, "A4214")==true );
  
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  doris_asegurar((*doris), "Se crea un iterador con hash valido", iterador!=NULL);
  if(iterador == NULL){
    printf("\nError al crear el iterador\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return;
  }

  doris_asegurar((*doris), "Se itera con iterador valido y  tiene siguiente valido", hash_iterador_siguiente(iterador)!=NULL);
  doris_asegurar((*doris), "La proxima iteracion NO tiene siguiente", hash_iterador_tiene_siguiente(iterador)==false);
  hash_iterador_destruir(iterador);
  hash_destruir(hash);
  
}

void probar_iterador_externo_iterador_nulo(doris_t** doris){
  doris_asegurar((*doris), "No se puede iterar con iterador nulo", hash_iterador_tiene_siguiente(NULL)==false);
}


int main(){

	doris_t* doris = doris_crear();
	
  printf("\n==>PRUEBAS CREANDO HASH CON DESTRUCTOR NULO\n");
	probar_crear_hash_nulos(&doris);
  printf("\n==>PRUEBAS CREANDO HASH CON CAPACIDAD MENOR\n");
	probar_crear_hash_capacidad_menor(&doris);
  printf("\n==>PRUEBAS CREANDO HASH VALIDO\n");
	probar_crear_hash_completo(&doris);
  
  printf("\n==>PRUEBAS INSERTANDO NULOS\n");
	probar_insertando_hash_nulo(&doris);
	printf("\n==>PRUEBAS INSERTANDO ALGO INEXISTENTE\n");
	probar_insertando_hash_inexistente(&doris);
	printf("\n==>PRUEBAS INSERTANDO UN VALOR VALIDO \n");
	probar_insertando_hash_uno_solo(&doris);
  printf("\n==>PRUEBAS INSERTANDO VARIOS VALORES VALIDO \n");
	probar_insertando_hash_varios(&doris);
  
	printf("\n==>PRUEBAS OBTENIENDO CON HASH NULO\n");
	probar_obteniendo_con_hash_nulo(&doris);
	printf("\n==>PRUEBAS OBTENIENDO HASH CON CLAVE INEXISTENTE\n");
	probar_obteniendo_con_hash_clave_inexistente(&doris);
	printf("\n==>PRUEBAS OBTENIENDO HASH CON CLAVE EXISTENTE\n");
	probar_obteniendo_con_hash_clave_valido(&doris);
  
  printf("\n==>PRUEBAS  DE CONTENIDO CON HASH NULO\n");
	probar_contenido_hash_nulo(&doris);
	printf("\n==>PRUEBAS DE CONTENIDO CLAVE INEXISTENTE CON HASH VALIDO\n");
	probar_contenido_clave_inexistente(&doris);
	printf("\n==>PRUEBAS DE CONTENIDO CLAVE VALIDA CON HASH VALIDO\n");
	probar_contenido_clave_y_hash_valido(&doris);
	
  printf("\n==>PRUEBAS DE CANTIDAD CON HASH NULO\n");
	probar_cantidad_hash_nulo(&doris);
	printf("\n==>PRUEBAS DE CANTIDAD CON HASH SIN ELEMENTOS\n");
	probar_cantidad_hash_vacio(&doris);
	printf("\n==>PRUEBAS DE CANTIDAD CON VARIOS ELEMENTOS VALIDO Y HASH NO NULO\n");
	probar_cantidad_varios_elementos(&doris);
  
  printf("\n==>PRUEBAS DE QUITAR ELEMENTOS CON HASH NULO\n");
	probar_quitar_elemento_hash_nulo(&doris);
	printf("\n==>PRUEBAS DE QUITAR ELEMENTOS CON CLAVE INEXISTENTE Y HASH VALIDO\n");
	probar_quitar_elemento_inexistente(&doris);
	printf("\n==>PRUEBAS DE QUITAR ELEMENTOS VALIDOS CON HASH VALIDO\n");
	probar_quitar_todo_elemento_existente(&doris);
  
  printf("\n==>PRUEBAS DE ITERADOR INTERNO CON HASH NULO\n");
	probar_iterador_interno_hash_nulo(&doris);
	printf("\n==>PRUEBAS DE ITERADOR INTERNO CON FUNCION NULA\n");
	probar_iterador_interno_funcion_nula(&doris);
	printf("\n==>PRUEBAS DE ITERADOR INTERNO CON HASH VALIDO\n");
	probar_iterador_interno_hash_valido(&doris);
  
  printf("\n==>PRUEBAS CON ITERADOR EXTERNO CREAR CON HASH VALIDO\n");
	probar_iterador_externo_crear_hash_valido(&doris);
  printf("\n==>PRUEBAS CON ITERADOR EXTERNO CREAR CON HASH NULO\n");
	probar_iterador_externo_crear_hash_nulo(&doris);
	printf("\n==>PRUEBAS CON ITERADOR EXTERNO SIGUIENTE\n");
	probar_iterador_externo_siguiente(&doris);
	printf("\n==>PRUEBAS CON ITERADOR EXTERNO QUE SI TIENE SIGUIENTE \n");
	probar_iterador_externo_tiene_siguiente(&doris);
  printf("\n==>PRUEBAS CON ITERADOR EXTERNO QUE NO TIENE SIGUIENTE \n");
	probar_iterador_externo_no_tiene_siguiente(&doris);
  printf("\n==>PRUEBAS CON ITERADOR EXTERNO TIENE SIGUIENTE CON ITERADOR NULO\n");
	probar_iterador_externo_iterador_nulo(&doris);
  
  doris_estadistica(doris);
	doris_destruir(doris);
	
	return 0;
}

