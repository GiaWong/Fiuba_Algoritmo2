#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "batallas.h"

#define COLOR_VERDE    "\x1b[32m\x1b[1m"
#define COLOR_FVERDE   "\x1b[42m"
#define COLOR_NORMAL   "\x1b[0m"

int suma_mayor_fuerza(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int suma_mayor_agilidad(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int suma_mayor_inteligencia(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int suma_mayor_longitud_nombres(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int mayor_fuerza_par(entrenador_t* entrenador_1, entrenador_t* entrenador_2);

void formatear_entrenador(entrenador_t* entrenadores);

void mostrar_mensaje_inicial(torneo_t* torneo){ 
    printf(COLOR_NORMAL "\n=================================================="COLOR_FVERDE" PARTICIPANTES A COMPETIR:"COLOR_NORMAL"====================================================\n" );
    torneo_listar(torneo, formatear_entrenador);
    printf(COLOR_NORMAL"\n" COLOR_VERDE "################################################################################################################################" COLOR_NORMAL"\n");
    printf("==> Presione enter para continuar...");
    getchar();

}

void mostrar_mensaje(torneo_t* torneo){
    printf("\n================================================= Pasan a la siguiente ronda: ================================================= \n");
    torneo_listar(torneo, formatear_entrenador);
    printf(COLOR_NORMAL"\n" COLOR_VERDE "################################################################################################################################" COLOR_NORMAL"\n");
    printf("==> Presione enter para continuar...");
    getchar();

} 

void mostrar_ganador(torneo_t* torneo){
    printf("\n\t================================================= EL GANADOR ES ================================================= \n");
    torneo_listar(torneo, formatear_entrenador);
    printf("\n El torneo finalizó !!!\n");
   
}

bool verificar_estado(torneo_t* torneo, int estado){
    int respuesta;

    if(estado == EXITO && torneo->cantidad_entrenadores > 1){
        mostrar_mensaje(torneo);
        respuesta = true;

    }else if(estado==ERROR){
        printf("\nUps, no se jugó bien el torneo \n");
        torneo_destruir(torneo);
        respuesta =  false;

    }else if(estado == EXITO && torneo->cantidad_entrenadores == 1){
        respuesta = true;
    }

    return respuesta;
}

int main(){

    torneo_t* torneo = NULL ;
    int estado = EXITO;
    char* archivo = "archivo_par_25.csv";
  
    torneo = torneo_crear(archivo);
    
    if(torneo == NULL){
        printf("No se pudo crear el torneo\n");
        return ERROR;
    }
    torneo->ronda = 0;
    mostrar_mensaje_inicial(torneo);
    
    if( torneo->cantidad_entrenadores == 1){
        printf("\nNo se pudo competir, por lo tanto el ganador es:\n");
        torneo_listar(torneo, formatear_entrenador);
        printf("\n==> El torneo finalizó !!!\n");
        torneo_destruir(torneo);
        return EXITO;
    }
   
    while(torneo->cantidad_entrenadores > 1 && estado == EXITO){
        
        estado = torneo_jugar_ronda(torneo, suma_mayor_fuerza);
        if(verificar_estado(torneo, estado) == false){
            return ERROR;
        }
   
        if(torneo->cantidad_entrenadores > 1){
            estado = torneo_jugar_ronda(torneo, suma_mayor_agilidad);
            if(verificar_estado(torneo, estado) == false){
            return ERROR;
            }
         
            if(torneo->cantidad_entrenadores > 1){
                estado = torneo_jugar_ronda(torneo, suma_mayor_inteligencia);
                if(verificar_estado(torneo, estado) == false){
                    return ERROR;
                }
            
                if(torneo->cantidad_entrenadores > 1){
                    estado = torneo_jugar_ronda(torneo, suma_mayor_longitud_nombres);
                    if(verificar_estado(torneo, estado) == false){
                        return ERROR;
                    }
                 
                    if(torneo->cantidad_entrenadores > 1){
                        estado = torneo_jugar_ronda(torneo, mayor_fuerza_par);
                        if(verificar_estado(torneo, estado) == false){
                            return ERROR;
                        }
                        
                    }

                }
                
            }
        }      
    }

    if(estado == EXITO && torneo->cantidad_entrenadores == 1){
        mostrar_ganador(torneo);
        torneo_destruir(torneo);
        return EXITO;
    }
 
    return EXITO;
}

