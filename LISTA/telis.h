#ifndef __TELIS_H__
#define __TELIS_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct telis{
    int pruebas_exitosas;
    int pruebas_totales; 
} telis_t;//telis "testing de lista"

/*
*Muestra el mensaje que se manada como aviso
*/
void telis_avisar(char* aviso);

/*
*Verifica si lo que recibe por parametro corresponde realmente con el dato
*/
void telis_asegurar(telis_t* telis, char* descripcion, bool dato);

/*
*Muestra cuantas pruebas exitosas hubo y cuantas pruebas de falla .
*/
void telis_mostrar_estadistica(telis_t* telis);


#endif /* __TELIS_H__ */