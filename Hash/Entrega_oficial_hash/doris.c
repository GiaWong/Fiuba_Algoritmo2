#include "doris.h"
#include <stdio.h>
#include <stdlib.h>

struct doris{
    int pruebas_exitosas;
    int pruebas_totales;
};

doris_t* doris_crear(){
    return calloc(1,sizeof(doris_t));
}

void doris_asegurar(doris_t* probador, char* descripcion, bool valor){
    
    if(probador==NULL) return;
    if(valor==true)   probador->pruebas_exitosas ++;
    probador->pruebas_totales ++;
    printf(COLOR_NORMAL"\n"COLOR_VERDE"Test:"COLOR_BLANCO" %s [%s"COLOR_BLANCO"]"COLOR_NORMAL"\n", descripcion, valor==true? COLOR_AMARILLO"EXITO":COLOR_ROJO"FALLA");

}

void doris_estadistica(doris_t* probador){
    if(probador==NULL) return;
    printf(COLOR_BLANCO"\nPasaron "COLOR_AMARILLO"%i"COLOR_BLANCO" pruebas de un total de "COLOR_ROJO"%i"COLOR_BLANCO" pruebas"COLOR_NORMAL"\n", probador->pruebas_exitosas, probador->pruebas_totales);

}

void doris_destruir(doris_t* probador){
    free(probador);
}