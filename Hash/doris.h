#ifndef __DORIS_H__
#define __DORIS_H__

#include <stdbool.h>
#include <stddef.h>
#include "colores.h"

typedef struct doris doris_t;

doris_t* doris_crear();

void doris_asegurar(doris_t* probador, char* descripcion, bool valor);
void doris_estadistica(doris_t* probador);
void doris_destruir(doris_t* probador);


#endif /* __DORIS_H__ */