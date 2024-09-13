#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "lista.h"
#include "hash.h"
#include "hash_iterador.h"

#define ERROR -1
#define EXITO 0

#define COLOR_ROJO     "\x1b[31m\x1b[1m"
#define COLOR_VERDE    "\x1b[32m\x1b[1m"
#define COLOR_AMARILLO "\x1b[33m\x1b[1m"
#define COLOR_NORMAL   "\x1b[0m"
#define COLOR_FROJO     "\x1b[41m"
#define COLOR_FVERDE    "\x1b[42m"
#define COLOR_FNORMAL   "\x1b[40m"
#define COLOR_CELESTE   "\x1b[0;36m"

char* duplicar_string(const char* string){
  if(!string)
    return NULL;

  char* palabra = malloc(strlen(string)+1);
  strcpy(palabra,string);
  return palabra;
}

void destruir_string(void* elemento){
  if(elemento){
    printf("Libero el dato: %s\n", (char*)elemento);
    free(elemento);
  }
}

bool hash_crear_destructor_null(){//1
  printf("Se crea un hash con destructor null\n");
  hash_t* hash = hash_crear(NULL,3);
  if(hash == NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_crear_destructor_null_capacidad_menor(){
  printf("Se crea un hash con destructor null y capacidad menor a 3\n");
  hash_t* hash = hash_crear(NULL,2);
  if(hash == NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_crear_destructor(){//3
  printf("Se crea un hash con destructor \n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_crear_destructor_capacidad_menor(){//2
  printf("Se crea un hash con destructor y capacidad menor a 3\n");
  hash_t* hash = hash_crear(destruir_string,2);
  if(hash == NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_crear(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de hash crear\n"COLOR_NORMAL);
  if(hash_crear_destructor_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_crear_destructor_null_capacidad_menor()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_crear_destructor()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_crear_destructor_capacidad_menor()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool hash_insertar_hash_null(){//1
  printf("Se inserta en un hash inexistente\n");
  char* elemento = duplicar_string("Sabias que los pelicanos sacan su columna vertebral por la boca para enfriarse?");
  int test = hash_insertar(NULL,"A4214",elemento);
  if(test != ERROR){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    free(elemento);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    free(elemento);
    return true;
  }
}

bool hash_insertar_hash_valido_clave_invalida(){//2
  bool error = false;
  printf("Se inserta en un hash inexistente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  char* elemento = duplicar_string("Sabias que los pelicanos sacan su columna vertebral por la boca para enfriarse?");
  int test = hash_insertar(hash,"",elemento);
  if(test != ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    free(elemento);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    free(elemento);
    return true;
  }
}

bool hash_insertar_hash_valido(){//3
  bool error = false;
  printf("Se inserta en un hash inexistente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"A4214",duplicar_string("Sabias que los pelicanos sacan su columna vertebral por la boca para enfriarse?"));
  if(test == ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_insertar_repetido_hash_valido(){
  bool error = false;
  printf("Se inserta repetido en un hash valido\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"A4214",duplicar_string("Sabias que los monos aman la fruta?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"A4214",duplicar_string("Sabias que las hienas atacan a los leones?"));
  if(test == ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_insertar_hash_cantidad(){
  bool error = false;
  printf("Se insertan muchos en un hash\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"A4214",duplicar_string("Sabias que los pelicanos sacan su columna vertebral por la boca para enfriarse?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"PQ452",duplicar_string("Sabias que los perros son hermosos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"FO523",duplicar_string("Sabias que las ballenas son mamiferos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"PR214",duplicar_string("Sabias que los tigres son gatos grandes?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P00A2",duplicar_string("Sabias que los gatos nos ven como sus esclavos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"L0C0S",duplicar_string("Sabias que los lobos marinos son amigables?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"F0C0S",duplicar_string("Sabias que los animales grandes tienen menor tendencia a morir por cancer?"));

  if(test == ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_insertar(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de hash insertar\n"COLOR_NORMAL);
  if(hash_insertar_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas+1;
  }
  if(hash_insertar_hash_valido()){
    *cantidad_pruebas = *cantidad_pruebas+1;
  }
  if(hash_insertar_hash_valido_clave_invalida()){
    *cantidad_pruebas = *cantidad_pruebas+1;
  }
  if(hash_insertar_hash_cantidad()){
    *cantidad_pruebas = *cantidad_pruebas+1;
  }
  if(hash_insertar_repetido_hash_valido()){
    *cantidad_pruebas = *cantidad_pruebas+1;
  }
}

bool hash_obtener_hash_null(){//1
  printf("Se intenta obtener un elemento de un hash null\n");
  void* elemento = hash_obtener(NULL,"AB896");
  if(elemento != NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_obtener_clave_inexistente(){//2
  bool error = false;
  printf("Se intenta obtener un elemento de un hash con clave inexistente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  void* elemento = hash_obtener(hash,"OL976");
  if(elemento != NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_obtener_clave_existe(){//3
  bool error = false;
  printf("Se intenta obtener un elemento de un hash \n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  void* elemento = hash_obtener(hash,"AB896");
  if(elemento == NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_obtener_clave_invalida(){
  bool error = false;
  printf("Se intenta obtener un elemento de un hash con una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  void* elemento = hash_obtener(hash,"");
  if(elemento != NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_obtener(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de hash obtener\n"COLOR_NORMAL);
  if(hash_obtener_clave_invalida()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_obtener_clave_existe()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_obtener_clave_inexistente()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_obtener_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool hash_contiene_hash_null(){//1
  printf("Se intenta ver si contiene un elemento un hash null\n");
  bool contener = hash_contiene(NULL,"A98D7");
  if(contener){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_contiene_clave_invalida(){
  bool error = false;
  printf("Se intenta intenta ver si contiene un elemento una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  bool contener = hash_contiene(hash,"");
  if(contener || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_contiene_clave_inexistente(){//2
  bool error = false;
  printf("Se intenta intenta ver si contiene un elemento una clave inexistente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  bool contener = hash_contiene(hash,"A952F");
  if(contener || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_contiene_elemento_existente(){//3
  printf("Se intenta intenta ver si contiene un elemento una clave valida\n");
  bool error = false;
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int salida = hash_insertar(hash,"AB896",duplicar_string("Sabias que los delfines son agresivos?"));
  if(salida == ERROR){
    error = true;
  }
  bool contener = hash_contiene(hash,"AB896");
  if(!contener || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_contiene(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Se hacen pruebas de hash_contiene\n"COLOR_NORMAL);
  if(hash_contiene_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_contiene_clave_invalida()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_contiene_clave_inexistente()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_contiene_elemento_existente()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool hash_cantidad_hash_null(){
  printf("Se prueba hash_canitdad con un hash NULL\n");
  size_t total = hash_cantidad(NULL);
  if(total != 0){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_cantidad_hash_vacio(){
  printf("Se prueba hash_cantidad con un hash sin elementos\n");
  bool error = false;
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  size_t total = hash_cantidad(hash);
  if(total != 0 || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_cantidad_con_elementos(){
  printf("Se pruebas hash_cantidad con varios elementos validos\n");
  bool error = false;
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P00A2",duplicar_string("Sabias que los gatos nos ven como sus esclavos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"L0C0S",duplicar_string("Sabias que los lobos marinos son amigables?"));
  size_t total = hash_cantidad(hash);
  if(total != 3 || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_cantidad(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de hash_cantida\n"COLOR_NORMAL);
  if(hash_cantidad_con_elementos()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_cantidad_hash_vacio()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_cantidad_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool hash_quitar_hash_null(){
  printf("Se prueba hash_quitar con un hash NULL\n");
  int salida = hash_quitar(NULL,"AB985");
  if(salida != ERROR){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_quitar_clave_invalida(){
  bool error = false;
  printf("Se prueba hash_quitar con una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  int salida = hash_quitar(hash,"");
  if(salida != ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_quitar_clave_inexistente(){
  bool error = false;
  printf("Se prueba hash_quitar con una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  int salida = hash_quitar(hash,"AB862");
  if(salida != ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_quitar_clave_valida(){
  bool error = false;
  printf("Se prueba hash_quitar con una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  int salida = hash_quitar(hash,"P42T1");
  if(salida == ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_quitar_cantidad(){
  bool error = false;
  printf("Se prueba hash_quitar con una clave invalida\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"PQ452",duplicar_string("Sabias que los perros son hermosos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"FO523",duplicar_string("Sabias que las ballenas son mamiferos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"PR214",duplicar_string("Sabias que los tigres son gatos grandes?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P00A2",duplicar_string("Sabias que los gatos nos ven como sus esclavos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"L0C0S",duplicar_string("Sabias que los lobos marinos son amigables?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"CA005");
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"L0C0S");
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"P00A2");
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"PQ452");
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"FO523");
  if(test == ERROR){
    error = true;
  }
  test = hash_quitar(hash,"PR214");
  if(test == ERROR || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_quitar(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de hash_quitar\n"COLOR_NORMAL);
  if(hash_quitar_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_quitar_clave_inexistente()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_quitar_clave_invalida()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_quitar_cantidad()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_quitar_clave_valida()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool mostrar_pantalla(hash_t* hash, const char* clave, void* aux){
  if(!clave)
    return true;

  aux=aux;
  hash=hash;

  printf("Dato en el hash: %s\n", clave);

  return false;
}

bool hash_con_cada_clave_hash_vacio(){
  bool error = false;
  printf("Se prueba hash_con_cada_clave con un hash vacio\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  size_t cantidad = hash_con_cada_clave(hash,mostrar_pantalla,NULL);
  if(cantidad != 0 || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_con_cada_clave_funcion_valida(){//3
  bool error = false;
  printf("Se prueba hash_con_cada_clave con un hash vacio\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"PQ452",duplicar_string("Sabias que los perros son hermosos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"FO523",duplicar_string("Sabias que las ballenas son mamiferos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"PR214",duplicar_string("Sabias que los tigres son gatos grandes?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P42T1",duplicar_string("Sabias que los elefantes se embarran para cuidar su piel?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"P00A2",duplicar_string("Sabias que los gatos nos ven como sus esclavos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"L0C0S",duplicar_string("Sabias que los lobos marinos son amigables?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  size_t cantidad = hash_con_cada_clave(hash,mostrar_pantalla,NULL);
  if(cantidad != 7 || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_con_cada_clave_funcion_null(){//2
  bool error = false;
  printf("Se prueba hash_con_cada_clave con un hash vacio\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  size_t cantidad = hash_con_cada_clave(hash,NULL,NULL);
  if(cantidad != 0 || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_con_cada_clave_hash_null(){//1
  printf("Se prueba hash_con_cada_clave con un hash vacio\n");
  size_t cantidad = hash_con_cada_clave(NULL,mostrar_pantalla,NULL);
  if(cantidad != 0){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}


void pruebas_iterador_interno(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas de iterador interno\n"COLOR_NORMAL);
  if(hash_con_cada_clave_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_con_cada_clave_funcion_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_con_cada_clave_funcion_valida()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_con_cada_clave_hash_vacio()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}
//**********************************************************
bool hash_iterador_crear_hash_null(){
  printf("Se prueba hash_iterador_crear con un hash null\n");//------------------2
  hash_iterador_t* iterador = hash_iterador_crear(NULL);
  if(iterador != NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_iterador_crear_hash_vacio(){
  bool error = false;
  printf("Se prueba hash_iterador_crear con un hash vacio\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  if(iterador != NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_destruir(hash);
    return true;
  }
}

bool hash_iterador_crear_hash_valido(){//------------------1
  bool error = false;
  printf("Se prueba hash_iterador_crear con un hash valido\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  if(iterador == NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_iterador_crear(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas hash_iterador_crear\n"COLOR_NORMAL);
  if(hash_iterador_crear_hash_valido()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_iterador_crear_hash_vacio()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_iterador_crear_hash_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

bool hash_iterador_siguiente_iterador_null(){
  printf("Se prueba hash_iterador_siguiente con un iterador NULL\n");
  const char* clave = hash_iterador_siguiente(NULL);
  if(clave != NULL){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_iterador_siguiente_iterador_valido(){//------------------3
  bool error = false;
  printf("Se prueba hash_iterador_siguiente con un iterador valido y tiene siguiente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"LO005",duplicar_string("Sabias que los orangutanes usan herramientas?"));
  if(test == ERROR){
    error = true;
  }
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  if(iterador == NULL){
    error = true;
  }
  const char* clave = hash_iterador_siguiente(iterador);
  if(clave == NULL || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_iterador_siguiente(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas hash_iterador_siguiente\n"COLOR_NORMAL);
  if(hash_iterador_siguiente_iterador_valido()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_iterador_siguiente_iterador_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}
//**********************************************************
bool hash_iterador_tiene_siguiente_iterador_null(){
  printf("Se prueba hash_iterador_tiene_siguiente con un iterador NULL\n");
  bool siguiente = hash_iterador_tiene_siguiente(NULL);
  if(siguiente){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    return true;
  }
}

bool hash_iterador_tiene_siguiente_iterador_valido(){
  bool error = false;
  printf("Se prueba hash_iterador_tiene_siguiente con un iterador valido y tiene siguiente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  test = hash_insertar(hash,"LO005",duplicar_string("Sabias que los orangutanes usan herramientas?"));
  if(test == ERROR){
    error = true;
  }
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  if(iterador == NULL){
    error = true;
  }
  bool siguiente = hash_iterador_tiene_siguiente(iterador);
  if(!siguiente || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return true;
  }
}

bool hash_iterador_no_tiene_siguiente_iterador_valido(){
  bool error = false;
  printf("Se prueba hash_iterador_tiene_siguiente con un iterador valido y no tiene siguiente\n");
  hash_t* hash = hash_crear(destruir_string,3);
  if(hash == NULL){
    error = true;
  }
  int test = hash_insertar(hash,"CA005",duplicar_string("Sabias que los delfines son agresivos?"));
  if(test == ERROR){
    error = true;
  }
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  if(iterador == NULL){
    error = true;
  }
  const char* clave = hash_iterador_siguiente(iterador);
  bool siguiente = hash_iterador_tiene_siguiente(iterador);
  if(clave == NULL|| siguiente || error){
    printf(COLOR_ROJO"ERROR"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return false;
  }else{
    printf(COLOR_VERDE"EXITO"COLOR_NORMAL"\n");
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return true;
  }
}

void pruebas_hash_iterador_tiene_siguiente(int* cantidad_pruebas){
  printf(COLOR_AMARILLO"Pruebas hash_iterador_tiene_siguiente\n"COLOR_NORMAL);
  if(hash_iterador_tiene_siguiente_iterador_valido()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_iterador_tiene_siguiente_iterador_null()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
  if(hash_iterador_no_tiene_siguiente_iterador_valido()){
    *cantidad_pruebas = *cantidad_pruebas +1;
  }
}

int main(){
  int pruebas_totales = 0;
  pruebas_hash_crear(&pruebas_totales);
  pruebas_hash_insertar(&pruebas_totales);
  pruebas_hash_quitar(&pruebas_totales);
  pruebas_hash_obtener(&pruebas_totales);
  pruebas_hash_cantidad(&pruebas_totales);
  pruebas_hash_contiene(&pruebas_totales);
  pruebas_iterador_interno(&pruebas_totales);
  pruebas_hash_iterador_crear(&pruebas_totales);
  pruebas_hash_iterador_siguiente(&pruebas_totales);
  pruebas_hash_iterador_tiene_siguiente(&pruebas_totales);
  printf("Tenes un total de %i de pruebas\n",pruebas_totales);
}
