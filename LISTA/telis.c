#include "telis.h"
#include "colores.h"
#include <stdio.h>
#include <stdbool.h>


void telis_asegurar(telis_t* telis, char* descripcion, bool dato){
  if(!telis)
    return;
    
  if(dato==true)
    telis->pruebas_exitosas ++;
    
  telis->pruebas_totales ++;
  printf("\n"COLOR_AMARILLO"PRUEBA:"COLOR_NORMAL" %s %s\n", descripcion, dato? COLOR_AMARILLO"EXITO"COLOR_NORMAL: COLOR_ROJO"FALLA"COLOR_NORMAL);
}

void telis_mostrar_estadistica(telis_t* telis){
  if(!telis)
    return;
        
  printf(COLOR_NORMAL"\nPruebas exitosas:"COLOR_AMARILLO" %i"COLOR_NORMAL" de "COLOR_ROJO"%i"COLOR_NORMAL"\n",telis->pruebas_exitosas,telis->pruebas_totales);

}
void telis_avisar(char* aviso){
  printf(COLOR_NORMAL"\n"COLOR_VERDE"AVISO:"COLOR_BLANCO" %s"COLOR_NORMAL"\n",aviso);
}