#include "batallas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLOR_FVERDE    "\x1b[42m"
#define COLOR_NORMAL   "\x1b[0m"

const int MAX_POKEMONES = 3;
int contador = 0;

torneo_t* torneo_crear(char *ruta_archivo){

    torneo_t* torneo=NULL;
    pokemon_t pokes[MAX_POKEMONES];
    char entrenador[MAX_NOMBRE];
   
    torneo = malloc(1*sizeof(torneo_t));
    if(torneo==NULL){
        return NULL;
    }
    
    torneo->entrenadores=NULL;
    torneo->cantidad_entrenadores=0;
    torneo->ronda=0;
    
    FILE* archivo = fopen(ruta_archivo,"r");
    if(archivo==NULL){
        perror("No se pudo abrir el archivo\n");
        free(torneo);
        return NULL;
    }
    int indicador =0;
    int leidos;

    do{
            
        leidos = fscanf(archivo," %[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n ", entrenador, pokes[0].nombre, &pokes[0].fuerza, &pokes[0].agilidad, &pokes[0].inteligencia, pokes[1].nombre, &pokes[1].fuerza, &pokes[1].agilidad, &pokes[1].inteligencia, pokes[2].nombre, &pokes[2].fuerza, &pokes[2].agilidad, &pokes[2].inteligencia);
            
        if( leidos == 13){   
            entrenador_t*  auxiliar = realloc(torneo->entrenadores,(long unsigned int)(torneo->cantidad_entrenadores +1)*sizeof(entrenador_t));  
            if(auxiliar == NULL){
                //printf("No se pudo reservar memoria para entrenadores\n");
                fclose(archivo);
                free(torneo);
                return NULL;
            }
            torneo->entrenadores=auxiliar;
            strcpy(torneo->entrenadores[torneo->cantidad_entrenadores].nombre,entrenador);
            torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = malloc(3*sizeof(pokemon_t));
        
            if(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones == NULL){
                free(auxiliar);
                fclose(archivo);
                free(torneo);
                //printf("No se pudo reservar memoria para pokemones\n");
                return NULL;
            }
            memcpy(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones, pokes, 3*sizeof(pokemon_t));
            torneo->cantidad_entrenadores ++;
            indicador = 1;
                
        }else if(leidos != 13 && leidos != EOF) {   
            if(indicador==1){
                for(int i=0; i<torneo->cantidad_entrenadores; i++){
                    free(torneo->entrenadores[i].pokemones);
                }
            } 
            free(torneo);
            fclose(archivo);
            return NULL;
        }
           
    }while(leidos == 13);

    if(leidos != 13 && leidos != EOF) {        
        if(indicador==1){
            for(int i=0; i<torneo->cantidad_entrenadores; i++){
                free(torneo->entrenadores[i].pokemones);
            }
        }     
        free(torneo);
        fclose(archivo);
        return NULL;
    }

    if(leidos != 13 && indicador == 0){
        //printf("Error, el archivo está vacio\n");
        fclose(archivo);
        free(torneo);
        return NULL;
    }    
       
    fclose(archivo);
    return torneo;
}

void torneo_destruir(torneo_t* torneo){

    if(torneo == NULL){
        return;
    }
    if(torneo->entrenadores == NULL){
        free(torneo);
        return;
    }
   
    for(int i=0; i < torneo->cantidad_entrenadores; i++){
        free(torneo->entrenadores[i].pokemones);
    }
    free(torneo->entrenadores);
    free(torneo);   
}

void mostrar_pokemones(pokemon_t* pokemones){

    for(int j=0; j<MAX_POKEMONES; j++){
        //printf("\tPokemon:\t%s\t",pokemones[j].nombre); 
        //printf("\tFuerza:\t%i\t", pokemones[j].fuerza); 
        //printf("\tAgilidad:\t%i\t", pokemones[j].agilidad); 
        //printf("\tInteligencia:\t%i\t", pokemones[j].inteligencia);;
        putchar('\n');
        //printf("\t-----------------------------------------------------------------------------------------------------------------------\n");
    }
}
void formatear_entrenador(entrenador_t* entrenadores){

    for(int i=0; i<contador; i++){
        //printf("\nEntrenador: %s\n", entrenadores[i].nombre);
        //printf("\n");
        mostrar_pokemones(entrenadores[i].pokemones);
    }
}

void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
    contador = torneo->cantidad_entrenadores;
    formatear_entrenador(torneo->entrenadores);
}

/*
*Cuenta todas las veces que aparece una vocal en los nombres de cada pokemon.
*/
int contar_vocales(entrenador_t* entrenador){
    
    char actual;
    int vocales=0;

    for(int k=0; k<MAX_POKEMONES; k++){
        for(int l=0; entrenador->pokemones[k].nombre[l] != 0; l++){

            actual=entrenador->pokemones[k].nombre[l];
            if(actual == 'a'|| actual == 'e'|| actual == 'i'|| actual == 'o'|| actual == 'u'){
                vocales ++;
            }
        }
    }
    return vocales;
}

/*
*Se encarga de obtener el total de vocales que tiene los nombre de cada
*pokemon, gana el que tiene mayor vocales y en caso de ser iguales
*gana el primer entrenador.
*/
int mayor_cant_vocales(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){

    int ganador;

    int total_vocal1 = contar_vocales(primer_entrenador);
    int total_vocal2 = contar_vocales(segundo_entrenador);
  
    if(total_vocal1 > total_vocal2){
        ganador=0;

    }else if (total_vocal1 < total_vocal2){
        ganador=1;
    }else{
        ganador=0;
    }
    return ganador;   
}

/*
*Suma cada fuerza de los pokemones, gana el que tiene mayor
*suma de fuerza, en caso de ser iguales se llama a la funcion mayor_cant_vocales() que se encargará
*de determinar el desempate.
*/
int suma_mayor_fuerza(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){
    
    int valor1 = 0;
    int valor2 = 0;
    int ganador;
    
    valor1 = primer_entrenador->pokemones[0].fuerza + primer_entrenador->pokemones[1].fuerza  + primer_entrenador->pokemones[2].fuerza ;
    valor2 = segundo_entrenador->pokemones[0].fuerza + segundo_entrenador->pokemones[1].fuerza  + segundo_entrenador->pokemones[2].fuerza ;

    if(valor1 > valor2){
        ganador = 0;
        
    }else if(valor1 < valor2 ){
        ganador = 1;
        
    }else{
        ganador = mayor_cant_vocales(primer_entrenador, segundo_entrenador);
    } 
    return ganador;  
}


/*
*Suma cada agilidad de los pokemones y gana el que tiene mayor suma de agilidad,
*en caso de haber un empate se le llama a la función mayor_cant_vocales() que se encargará de determinar
*el desempate.
*/
int suma_mayor_agilidad(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){

    int valor1 = 0;
    int valor2 = 0;
    int ganador;
    
    valor1 = primer_entrenador->pokemones[0].agilidad + primer_entrenador->pokemones[1].agilidad  + primer_entrenador->pokemones[2].agilidad ;
    valor2 = segundo_entrenador->pokemones[0].agilidad + segundo_entrenador->pokemones[1].agilidad  + segundo_entrenador->pokemones[2].agilidad ;

    if(valor1 > valor2){
        ganador = 0;
        
    }else if(valor1 < valor2 ){
        ganador = 1;
        
    }else{
        ganador = mayor_cant_vocales(primer_entrenador, segundo_entrenador);
    } 
    return ganador;  

}

/*
*Suma cada inteligencia de los pokemones, gana el que tiene mayor suma de 
*inteligencia, en caso de haber un empate se le llama a la función mayor_cant_vocales() que se encargará de 
*determinar el desempate.
*/
int suma_mayor_inteligencia(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){
    
    int valor1 = 0;
    int valor2 = 0;
    int ganador;
    
    valor1 = primer_entrenador->pokemones[0].inteligencia + primer_entrenador->pokemones[1].inteligencia  + primer_entrenador->pokemones[2].inteligencia ;
    valor2 = segundo_entrenador->pokemones[0].inteligencia + segundo_entrenador->pokemones[1].inteligencia  + segundo_entrenador->pokemones[2].inteligencia ;

    if(valor1 > valor2){
        ganador = 0;
        
    }else if(valor1 < valor2 ){
        ganador = 1;
        
    }else{
        ganador = mayor_cant_vocales(primer_entrenador, segundo_entrenador);
    } 
    return ganador; 
}

/*
*Suma cada longitud de nombres de los pokemones, y gana el que tiene
*mayor valor, en caso de haber un empate se le llama a la funcion mayor_cant_vocales() que determinará
*el desempate.
*/
int suma_mayor_longitud_nombres(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){
    
    long unsigned int valor1 = 0;
    long unsigned int valor2 = 0;
    int ganador;
    

    valor1 = strlen(primer_entrenador->pokemones[0].nombre) + strlen(primer_entrenador->pokemones[1].nombre)  + strlen(primer_entrenador->pokemones[2].nombre);
    valor2 = strlen(segundo_entrenador->pokemones[0].nombre) + strlen(segundo_entrenador->pokemones[1].nombre) + strlen(segundo_entrenador->pokemones[2].nombre);

    if(valor1 > valor2){
        ganador = 0;
        
    }else if(valor1 < valor2 ){
        ganador = 1;
        
    }else{
        ganador = mayor_cant_vocales(primer_entrenador, segundo_entrenador);
    } 
    return ganador; 

}

/*
*Cuenta todas las veces en las que cada fuerza de los pokemones son numeros pares
*/
int contar_fuerza_par(entrenador_t* entrenador){

    int valor = 0;

    for(int i =0; i<MAX_POKEMONES; i++){
        if(entrenador->pokemones[i].fuerza %2 == 0){
            valor ++;
        }
    }
    return valor;
}

/*
*Se encarga de obtener quien tinen mayor fuerza par 
*de los pokemones, en caso de haber un empate se le llama a la 
*función mayor_cant_vocales() que determinará el desempate.
*/
int mayor_fuerza_par(entrenador_t* primer_entrenador, entrenador_t* segundo_entrenador){
    
    int ganador;

    int total_fuerza1 = contar_fuerza_par(primer_entrenador);
    int total_fuerza2 = contar_fuerza_par(segundo_entrenador);

    if(total_fuerza1 > total_fuerza2){
        ganador = 0;
        
    }else if(total_fuerza1 < total_fuerza2 ){
        ganador = 1;
        
    }else{
        ganador = mayor_cant_vocales(primer_entrenador, segundo_entrenador);
    } 
    return ganador; 

}

int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){

    if(torneo == NULL || ganador_batalla == NULL){
        //printf("No se pudo acceder a torneo_jugar_ronda, parametros nulos\n");
        return ERROR;
    }
    if(torneo->cantidad_entrenadores == 1){
        //printf("No se puede jugar con un solo entrenador\n");
        return ERROR;
    }
    
    int pos, i, participante_ganador;
    void* aux_reducir = NULL;
    int primer_entrenador, segundo_entrenador;
    int cantidad_enfrentamiento = torneo->cantidad_entrenadores/2;
    int veces_enfrentamiento = 0;

    torneo->ronda ++;
    //printf(COLOR_NORMAL"\n\t\t\t\t\t\t\t"COLOR_FVERDE "RONDA: %i"COLOR_NORMAL"\n",torneo->ronda);

    while( veces_enfrentamiento < cantidad_enfrentamiento){

        primer_entrenador  = veces_enfrentamiento;
        segundo_entrenador = veces_enfrentamiento +1;

        participante_ganador = ganador_batalla(&torneo->entrenadores[primer_entrenador],&torneo->entrenadores[segundo_entrenador]);
        
        if(participante_ganador == 0){    
           //printf(" \nEl participante a eliminar es :  %s\n", torneo->entrenadores[segundo_entrenador].nombre);
            pos = veces_enfrentamiento + 1;  

        }else {         
           //printf(" \nEl participante a eliminar es :  %s\n", torneo->entrenadores[primer_entrenador].nombre); 
            pos = veces_enfrentamiento;          
        }

        free(torneo->entrenadores[pos].pokemones);

        for(i=pos; i < torneo->cantidad_entrenadores - 1 ;i++){ 
            torneo->entrenadores[i] = torneo->entrenadores[i +1];
        }
     
        aux_reducir = realloc(torneo->entrenadores, ((long unsigned int)torneo->cantidad_entrenadores - 1) * sizeof(entrenador_t));
        
        if(aux_reducir == NULL){
            //printf("\tError al reservar memoria =( \n");
            return ERROR;
        }
        
        torneo->entrenadores = aux_reducir;
        torneo->cantidad_entrenadores --;
    
        veces_enfrentamiento ++;
    }
    return EXITO;
}

