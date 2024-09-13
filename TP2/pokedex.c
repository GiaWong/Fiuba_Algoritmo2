#include "pokedex.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define EXITO 0

typedef struct pomum{
    bool se_encontro_especie;
    bool se_encontro_pokemon;
    int especie_a_buscar;
    char pokemon_a_encontrar[MAX_NOMBRE];
}pomum_t;

typedef struct auxiliar{
    particular_pokemon_t individual;
    int indicativo_especie;
}aux_t;

typedef struct poke{ 
    bool se_elimina;
    especie_pokemon_t especie_antigua;
    int nivel_poke;
    bool capturado_poke;
}poke_t;

void destruir_cosa(especie_pokemon_t* c){
	if(c){
        free(c);
    }	
}

int comparar_cosas(void* elemento1, void* elemento2){
	if(!elemento1 || !elemento2){
        return 0;
    }
	if((*(especie_pokemon_t*)elemento1).numero > ((especie_pokemon_t*)elemento2)->numero){
        return 1;
    }
	if((*(especie_pokemon_t*)elemento1).numero < ((especie_pokemon_t*)elemento2)->numero){
        return -1;
    }
	return 0;
}

void destructor_de_cosas(void* elemento){
	if(!elemento){
        return;
    }
	destruir_cosa((especie_pokemon_t*)elemento);
}

especie_pokemon_t* crear_memoria_especie(especie_pokemon_t especie_lleno){
	especie_pokemon_t* var = (especie_pokemon_t*)malloc(sizeof(especie_pokemon_t));
	if(var!=NULL){
        *var = especie_lleno;
    }	
	return var;
}

aux_t* transformar_pokemon(aux_t individual){
    aux_t* p =(aux_t*)malloc(sizeof(aux_t));
    if(p != NULL){
        *p=individual;
    }
    return p;
}

pokedex_t* pokedex_crear(char entrenador[MAX_NOMBRE]){

    pokedex_t* pokedex = calloc(1, sizeof(pokedex_t));
    if(pokedex==NULL) return NULL;
    printf("Creando la base pokedex...\n");

    if(strlen(entrenador)=='\0'){
       char no_hay_nombre[]={'A','n','o','n','i','m','u','s','\0'};
      strcpy(entrenador, no_hay_nombre);
    }
    strcpy(pokedex->nombre_entrenador, entrenador);

    pokedex->ultimos_capturados = lista_crear();
    if(pokedex->ultimos_capturados==NULL){
        free(pokedex);
        return NULL;
    }

    pokedex->ultimos_vistos = lista_crear();
    if(pokedex->ultimos_vistos==NULL){
        lista_destruir(pokedex->ultimos_capturados);
        free(pokedex);
        return NULL;
    }

    pokedex->pokemones = arbol_crear(comparar_cosas, destructor_de_cosas);
    if(pokedex->pokemones==NULL){
        lista_destruir(pokedex->ultimos_vistos);
        lista_destruir(pokedex->ultimos_capturados);
        free(pokedex);
        return NULL;
    }
    return pokedex;
}

int insertar_en_lista_pila_y_cola(pokedex_t** pokedex, especie_pokemon_t** p, particular_pokemon_t* pokemon_a_insertar ){
    
    if(lista_insertar( (*p)->pokemones, (void*)pokemon_a_insertar)==EXITO){
                            
        if(pokemon_a_insertar->capturado == true){
            if(lista_apilar((*pokedex)->ultimos_capturados, (void*)(pokemon_a_insertar))==ERROR){
                return ERROR;
            }  
        }
        if(lista_encolar((*pokedex)->ultimos_vistos, (void*)(pokemon_a_insertar))==ERROR){
            return ERROR;
        } 
        return EXITO;
    }else{
      return ERROR;
    }
}

bool incorporar_en_lista(void* elemento, void* extra){
    if(elemento!=NULL){
        if((*(aux_t*)extra).indicativo_especie == ((especie_pokemon_t*)elemento)->numero){
            aux_t* aux = (aux_t*)extra;
            if( lista_insertar(((especie_pokemon_t*)elemento)->pokemones, (void*)&aux->individual)==EXITO){
                return true;
            } 
        }
    }
    return false;
}

bool abrir_lista_elemento(void* elemento, void* extra){
    if(elemento!=NULL){
        if(*(int*)extra == (*(especie_pokemon_t*)elemento).numero){

           (*(especie_pokemon_t*)elemento).pokemones = lista_crear();
            return true;
        }
    }
    return false;  
}

int pokedex_avistar(pokedex_t* pokedex, char ruta_archivo[MAX_RUTA]){

    if(pokedex==NULL || strlen(ruta_archivo)=='\0') return ERROR;
    
    FILE* archivo = fopen(ruta_archivo,"r");
    if(archivo==NULL){
        printf("\nRuta de archivo no encontrada\n");
        return ERROR;
    }

    int leidos=0;
    char capturado;
    bool hay_repetido=false;
    especie_pokemon_t especie;
    aux_t pokemon;
    
    
    do{ 
        leidos=fscanf(archivo," %i;%[^;];%[^;];%[^;];%i;%c\n ", &especie.numero, especie.nombre, especie.descripcion, pokemon.individual.nombre, &pokemon.individual.nivel, &capturado);
        if(capturado=='S'){
            pokemon.individual.capturado=true;
        }else{
            pokemon.individual.capturado=false;
        }

        if(leidos==6){

            especie_pokemon_t* nuevo_especie = crear_memoria_especie(especie);
            aux_t* nuevo_pokemon = transformar_pokemon(pokemon);
            especie_pokemon_t* actual_especie=(especie_pokemon_t*)arbol_buscar(pokedex->pokemones, (void*)&nuevo_especie->numero);
            
            if(actual_especie!=NULL){//es porque hay la misma especie
               
                for(size_t i=0;i<lista_elementos( actual_especie->pokemones );i++){//tengo que buscar en la lista si no hay pokemon repetido
                    
                    if( strcmp(nuevo_pokemon->individual.nombre, (((particular_pokemon_t*)lista_elemento_en_posicion(actual_especie->pokemones, i))->nombre))==0){
                        hay_repetido=true;
                    } 
                }

                if(hay_repetido==false){
                    
                    if(insertar_en_lista_pila_y_cola(&pokedex, &actual_especie, &nuevo_pokemon->individual)==ERROR){
                        fclose(archivo);
                        return ERROR;
                    }  
                }else{
                    //libero aquellos datos que no serán utilizados y fueron reservados previamente
                    free(nuevo_pokemon);
                    free(nuevo_especie);
                }
               
            }else{//es porque no hay la especie

                if(arbol_insertar(pokedex->pokemones, nuevo_especie)==EXITO){

                    abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, abrir_lista_elemento,(void*)&nuevo_especie->numero);
                            
                    if(nuevo_especie->pokemones==NULL){
                        fclose(archivo);
                        return ERROR;
                    }
                    
                    especie_pokemon_t* aux=(especie_pokemon_t*)arbol_buscar(pokedex->pokemones, (void*)&nuevo_especie->numero);
                    if(insertar_en_lista_pila_y_cola(&pokedex, &aux, &nuevo_pokemon->individual)==ERROR){
                       fclose(archivo);
                        return ERROR;
                    }
                  
                }else{
                    fclose(archivo);
                    return ERROR;  
                }   
            }    
        }else if(leidos!=6 && leidos!=EOF){
            fclose(archivo);
            return ERROR;
        }

    }while(leidos == 6);

    fclose(archivo);
    return EXITO;
}


bool remover_pokemon_a_evolucionar(void* elemento, void* pokemus){
   
    if(elemento !=NULL){
        //si son la misma especie
		if(((especie_pokemon_t*)elemento)->numero == ((poke_t*)pokemus)->especie_antigua.numero){
            //recorro la lista hasta hallar al pokemon
            for(size_t i=0; i<lista_elementos(((especie_pokemon_t*)elemento)->pokemones);i++){
                //si el pokemon es hallado
                if(strcmp(((poke_t*)pokemus)->especie_antigua.nombre, ((particular_pokemon_t*)lista_elemento_en_posicion(((especie_pokemon_t*)elemento)->pokemones, i))->nombre)==0){
                    //si es capturado
                    particular_pokemon_t* p =  (particular_pokemon_t*)lista_elemento_en_posicion( ((especie_pokemon_t*)elemento)->pokemones, i);
                    if( p->capturado == true){
                       
                        ((poke_t*)pokemus)->nivel_poke = p->nivel;
                        ((poke_t*)pokemus)->capturado_poke = p->capturado;
                        free(p);
                        if(lista_borrar_de_posicion(((especie_pokemon_t*)elemento)->pokemones, i)==EXITO){
                            ((poke_t*)pokemus)->se_elimina=true;
                            return true;
                        }
                    }else{
                        return true;
                    }
                }
            }
            return true;
        }	
	}
	return false;
}


int pokedex_evolucionar(pokedex_t* pokedex, char ruta_archivo[MAX_RUTA]){
    
    if(pokedex==NULL || strlen(ruta_archivo)=='\0') return ERROR;

    FILE* archivo = fopen(ruta_archivo,"r");
    if(archivo==NULL){
        return ERROR;
    }

    int leidos=0;
    especie_pokemon_t nueva_especie;
    aux_t nueva_pokemon;
    poke_t pokemus;
    pokemus.se_elimina=false;
 

    //el pokemus.especie_antigua.nombre= el nombre actual del pokemon OJO CON ESTO!
    do{
        leidos=fscanf(archivo,"%i;%[^;];%i;%[^;];%[^\n]\n", &pokemus.especie_antigua.numero, pokemus.especie_antigua.nombre , &nueva_especie.numero, nueva_especie.nombre, nueva_especie.descripcion);
       
        if(leidos==5){
            //borro al pokemon antiguo
            abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, remover_pokemon_a_evolucionar, (void*)&pokemus);
            if(pokemus.se_elimina==true){
                
                //busco si ya existe tal especie nueva 
                especie_pokemon_t* espe =  (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, (void*)&nueva_especie.numero);
                if(espe !=NULL){ 
                    //va como pokemon particular   
                    strcpy(nueva_pokemon.individual.nombre, nueva_especie.nombre);
                    nueva_pokemon.individual.nivel=pokemus.nivel_poke;
                    nueva_pokemon.individual.capturado=pokemus.capturado_poke;

                    aux_t* p = transformar_pokemon(nueva_pokemon);
                    if(espe->pokemones==NULL){
                        abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, abrir_lista_elemento,(void*)&espe->numero);
                    }
                    if(insertar_en_lista_pila_y_cola(&pokedex, &espe, &p->individual)==ERROR){
                        fclose(archivo);
                        return ERROR; 
                    }

                }else{//si no existe la especie lo agrego al arbol
                    
                    espe = crear_memoria_especie(nueva_especie);
                    if(arbol_insertar(pokedex->pokemones, espe)==ERROR){
                        fclose(archivo);
                        return ERROR;
                    }
                    especie_pokemon_t* var = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, (void*)&espe->numero);
                    var->pokemones=NULL;

                }
                
                

            }else{
                if(pokemus.capturado_poke==false){
                    printf("\nPokemon no capturado\n");
                }else if(arbol_buscar(pokedex->pokemones, (void*)&pokemus.especie_antigua.numero)==NULL){
                   printf("\nLa especie no existe\n"); 
                }else{
                    printf("\nNo existe el pokemon especifico\n");
                }
               
                fclose(archivo);
                return ERROR;
            }
            pokemus.se_elimina=false;
            pokemus.capturado_poke=false;

        }else if(leidos!=5 && leidos!=EOF){
            fclose(archivo);
            return ERROR;
        }


    }while(leidos==5);

    fclose(archivo);
    return EXITO;

}


void pokedex_ultimos_capturados(pokedex_t* pokedex){

    if(pokedex==NULL){
        printf("Ups!...  pokedex es nula\n");
        return;
    } 

    printf("\nLos ultimos pokemones capturason fueron: \n\n");
    if(lista_vacia(pokedex->ultimos_capturados)==true){
        printf("\tNo hay pokemones capturados.");
    }
    while(!lista_vacia(pokedex->ultimos_capturados)){
        printf("Nombre: %s  con Nivel: %i\n", ((particular_pokemon_t*)lista_tope(pokedex->ultimos_capturados))->nombre, ((particular_pokemon_t*)lista_tope(pokedex->ultimos_capturados))->nivel);
        if(lista_desapilar(pokedex->ultimos_capturados) == ERROR){
            printf("Hubo un error a la hora de desapilar\n");
            return;
        }
    }
   
    printf("\n");

}


void pokedex_ultimos_vistos(pokedex_t* pokedex){
    if(pokedex==NULL){
        printf("Ups!...  pokedex es nula\n");
        return;
    }

    printf("\nLos pokemones vistos fueron: \n\n");
    if(lista_vacia(pokedex->ultimos_vistos)==true){
        printf("\tNo hay pokemones vistos.");
    }
    while(!lista_vacia(pokedex->ultimos_vistos)){
        printf("Nombre: %s  con Nivel: %i\n", ((particular_pokemon_t*)lista_primero(pokedex->ultimos_vistos))->nombre, ((particular_pokemon_t*)lista_primero(pokedex->ultimos_vistos))->nivel);
        if(lista_desencolar(pokedex->ultimos_vistos)==ERROR){
            printf("Hubo un error a la hora de desencolar\n");
            return;
        } 
      
    }
   

    printf("\n");
}

void mostar_datos_pokemon(particular_pokemon_t* pokemon_solo, especie_pokemon_t* especie_pokemon){

    printf("Datos de la especie N° %i\n", especie_pokemon->numero);
    printf("Nombre: %s\n", especie_pokemon->nombre);
    printf("Descripcion: %s\n", especie_pokemon->descripcion);
    printf("Nombre del pokemon: %s\n", pokemon_solo->nombre);
    printf("Nivel: %i\n", pokemon_solo->nivel);
    if(pokemon_solo->capturado==true){
        printf("Está capturado?: SI \n");
    }else{
        printf("Está capturado?: NO \n");
    }
    printf("\n\n");
}


bool mostrar_pokemon(void* elemento, void* pokelimum){
    	
	if(elemento!=NULL){
      
        //busco si coinciden en especie
		if(((especie_pokemon_t*)elemento)->numero == ((pomum_t*)pokelimum)->especie_a_buscar){
            ((pomum_t*)pokelimum)->se_encontro_especie=true;
            //busco en la lista si se encuentra el pokemon
            for(size_t i=0;i<lista_elementos(((especie_pokemon_t*)elemento)->pokemones);i++){
                //si el pokemon es hallado
                particular_pokemon_t* un_pokemon = (particular_pokemon_t*)lista_elemento_en_posicion( ((especie_pokemon_t*)elemento)->pokemones, i);
                if(strcmp(((pomum_t*)pokelimum)->pokemon_a_encontrar, un_pokemon->nombre)==0){
                    
                    ((pomum_t*)pokelimum)->se_encontro_pokemon=true;
                    mostar_datos_pokemon(un_pokemon, (especie_pokemon_t*)elemento); 
                    return true;
                }
            }
            return true;
        }	
	}

	return false;
}

bool mostrar_todos_pokemones(void* elemento, void* extra){
    
    if(elemento!=NULL){
		
		if(((especie_pokemon_t*)elemento)->numero == *(int*)extra ){

            lista_iterador_t* it = lista_iterador_crear(((especie_pokemon_t*)elemento)->pokemones);
            printf("\nPokemones disponibles de la especie:\n ");
            int i=1;
            while(lista_iterador_tiene_siguiente(it)){
                printf("%i) Pokemon:  %s \n", i, ((particular_pokemon_t*)lista_iterador_siguiente(it))->nombre);
                i++;
            }
            
            printf("\n\n");
            lista_iterador_destruir(it);

            return true;
        }
			
	}

	return false;
}




void pokedex_informacion(pokedex_t* pokedex, int numero_pokemon, char nombre_pokemon[MAX_NOMBRE]){

    if(pokedex==NULL){
        printf("Ups!...  pokedex es nula\n");
        return;
    }
    if(strlen(nombre_pokemon)!='\0'){

        pomum_t pokelimum;
        pokelimum.se_encontro_pokemon=false;
        pokelimum.se_encontro_especie=false;
        pokelimum.especie_a_buscar=numero_pokemon;
        strcpy(pokelimum.pokemon_a_encontrar, nombre_pokemon);
        
        abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, mostrar_pokemon, (void*)&pokelimum);
       
        if(pokelimum.se_encontro_pokemon==false && pokelimum.se_encontro_especie==true){
            printf("\nEl pokemon es desconocido...\n");
        }  
        
        if(pokelimum.se_encontro_especie==false){
            printf("\n La especie es desconocida...\n");
        }
   
    }else{
        //listar a todos los ṕokemones de la misma especie
        abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, mostrar_todos_pokemones, (void*)&numero_pokemon);
    }

}
//solo libera aquellas especies que tiene la lista, no elimina a la especie en sí o al nodo del arbol!
bool eliminar_pokemones_cada_especie(void* elemento, void* extra){
    extra=extra;
    if(elemento!=NULL){//entra cada especie
        //recorro a la lista de cada especie para liberarlo
        for(size_t i=0; i<lista_elementos(((especie_pokemon_t*)elemento)->pokemones); i++){
            free((particular_pokemon_t*)lista_elemento_en_posicion( ((especie_pokemon_t*)elemento)->pokemones, i ) );
        }
        lista_destruir(((especie_pokemon_t*)elemento)->pokemones); 
        return false;
    }
    return true;
    
    

}

void pokedex_destruir(pokedex_t* pokedex){
    if(pokedex!=NULL){
        lista_destruir(pokedex->ultimos_capturados);
        lista_destruir(pokedex->ultimos_vistos);
        abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, eliminar_pokemones_cada_especie, NULL);
        arbol_destruir(pokedex->pokemones);
        free(pokedex);
    }
}

bool llenar_archivo_especie(void* especie, void* extra){
  
    char id_especie = 'E';
    char id_pokemon = 'P';
   
    if(especie!=NULL){
        //transcribo la informacion al archivo
        fprintf(*(FILE**)extra,"%c;%i;%s;%s\n", id_especie, ((especie_pokemon_t*)especie)->numero, ((especie_pokemon_t*)especie)->nombre, ((especie_pokemon_t*)especie)->descripcion);
        
        //recorro la lista de los pokemones de la especie
        for(size_t i=0;i<lista_elementos(((especie_pokemon_t*)especie)->pokemones);i++){

            particular_pokemon_t* pokemon_individual = (particular_pokemon_t*)lista_elemento_en_posicion( ((especie_pokemon_t*)especie)->pokemones, i);
            if(pokemon_individual->capturado==true){
                fprintf(*(FILE**)extra, "%c;%s;%i;S\n", id_pokemon, pokemon_individual->nombre,  pokemon_individual->nivel);

            }else{
                fprintf(*(FILE**)extra, "%c;%s;%i;N\n", id_pokemon, pokemon_individual->nombre,  pokemon_individual->nivel);
            }
        }
       
        return false;
    }else{
        return true;
    }

}

int pokedex_apagar(pokedex_t* pokedex){
    
    if(pokedex==NULL) return ERROR;
    if(arbol_vacio(pokedex->pokemones)==true) return ERROR;

    FILE* archivo_a_llenar = fopen("pokedex.txt", "w");
    if(archivo_a_llenar==NULL)  return ERROR;
    //la primera linea va el nombre del entrenador
    fprintf(archivo_a_llenar, "%s\n", pokedex->nombre_entrenador);
    abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, llenar_archivo_especie, (void*)&archivo_a_llenar);
    fclose(archivo_a_llenar);
    return EXITO;
}


pokedex_t* pokedex_prender(){

    int letra_inicial, cant_leidos;
    char tipo_EP, entrenador_ingresado [MAX_NOMBRE], entrenador_existente [MAX_NOMBRE];
    
    printf("\nIngrese un nombre para el entrenador:");
    scanf(" %[^\n]", entrenador_ingresado);
    
    FILE* archivo_a_leer= fopen("pokedex.txt", "r");
    printf("\nAbriendo archivo pokedex.txt ....\n");
    if(archivo_a_leer==NULL) return NULL;
   
    //esta parte no es necesaria podria simplemente moverlo con el fseek
    fscanf(archivo_a_leer, " %[^\n]\n", entrenador_existente);//lee la primera linea del archivo
    pokedex_t* pokedex_plus = pokedex_crear(entrenador_ingresado);
  
    if(pokedex_plus!=NULL){
        
        especie_pokemon_t especie_actual;
        int guardar_numero, guar_nivel;
        char guardar_nombre [MAX_NOMBRE], guardar_descripcion [MAX_NOMBRE], guar_capturado, guar_nombre [MAX_NOMBRE];

        printf("Cargando el archivo a la pokedex...\n");
       
        do{
            
            letra_inicial=fscanf(archivo_a_leer,"%[^;]",&tipo_EP);
            //necesito moverme un byte a la derecha porque sobra un ; en el archivo
            fseek(archivo_a_leer,1*sizeof(char),SEEK_CUR);
            especie_pokemon_t* nuevo_espe;

            if(letra_inicial==1){
                
               
                if(tipo_EP=='E'){ 

                  
                    cant_leidos=fscanf(archivo_a_leer, "%i;%[^;];%[^\n]\n",&guardar_numero, guardar_nombre, guardar_descripcion);
                    
                    if(cant_leidos==3){
                        
                        especie_actual.numero=guardar_numero;
                        strcpy(especie_actual.nombre,guardar_nombre);
                        strcpy(especie_actual.descripcion,guardar_descripcion);
                       
                        nuevo_espe=crear_memoria_especie(especie_actual);

                        if(arbol_insertar(pokedex_plus->pokemones, nuevo_espe)==EXITO){ 
                          
                            abb_con_cada_elemento(pokedex_plus->pokemones, ABB_RECORRER_PREORDEN, abrir_lista_elemento,(void*)&nuevo_espe->numero);
                            
                            if(nuevo_espe->pokemones==NULL){
                                printf("==============XXXXXX================\n");
                                pokedex_destruir(pokedex_plus);
                                fclose(archivo_a_leer);
                                return NULL;
                            }
                            
                        }else{
                                                
                            printf("==============XXXXXX================\n");
                            pokedex_destruir(pokedex_plus);
                            fclose(archivo_a_leer);
                            return NULL;
                    
                        }

                    }else if(cant_leidos!=3 && cant_leidos!=EOF){
                        printf("==============XXXXXX================\n");
                        pokedex_destruir(pokedex_plus);
                        fclose(archivo_a_leer);
                        return NULL;
                    }
                
                    
                }else if(tipo_EP=='P'){
                    
                    cant_leidos=fscanf(archivo_a_leer, "%[^;];%i;%c\n", guar_nombre, &guar_nivel, &guar_capturado);

                    if(cant_leidos==3){
                        
                        aux_t aux;
                        aux_t* un_pokemon=NULL;
                        
                        aux.indicativo_especie=nuevo_espe->numero;
                        aux.individual.nivel=guar_nivel;
                        
                        if(guar_capturado=='S'){
                            aux.individual.capturado=true;
                        }else{
                            aux.individual.capturado=false;
                        }
                        
                        strcpy(aux.individual.nombre, guar_nombre);
                        un_pokemon =transformar_pokemon(aux);
                        abb_con_cada_elemento(pokedex_plus->pokemones, ABB_RECORRER_PREORDEN, incorporar_en_lista, (void*)un_pokemon);

                    }else if(cant_leidos!=EOF && cant_leidos!=3){
                        printf("==============XXXXXX================\n");
                        pokedex_destruir(pokedex_plus);
                        fclose(archivo_a_leer);
                        return NULL;
                    }
                }else{
                    printf("==============XXXXXX================\n");
                    pokedex_destruir(pokedex_plus);
                    fclose(archivo_a_leer);
                    return NULL;
                }
              
            }else if(letra_inicial!=EOF && letra_inicial!=1){
                printf("==============XXXXXX================\n");
                pokedex_destruir(pokedex_plus);
                fclose(archivo_a_leer);
                return NULL;
            }
            
        }while(cant_leidos==3 && letra_inicial==1);
     
    }else{
        printf("==============XXXXXX================\n");
        pokedex_destruir(pokedex_plus);
        fclose(archivo_a_leer);
        return NULL;
    }
    
    fclose(archivo_a_leer);
    return pokedex_plus;
}

