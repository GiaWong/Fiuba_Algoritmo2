#include "pokedex.h"
#include <stdio.h>
#include "colores.h"
#define EXITO 0
#define ERROR -1

bool verificar_primera_entrada(char rpta){
    if(rpta=='I' || rpta=='S') return true;
    return false;
}

void primera_lista_comandos(char* dato){
    do{ 
        system("clear");
        printf("\n\t"COLOR_AMARILLO"COMANDOS DISPONIBLES:"COLOR_NORMAL"\n\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Iniciar Pokedex  presione tecla I\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Salir del programa  presione tecla S\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Pedir ayuda presione tecla H\n");
        scanf("%c", &(*dato));    
            
    }while(verificar_primera_entrada(*dato)==false || (*dato)=='H');

}

bool verificar_segunda_entrada(char rpt){
    if(rpt=='M' || rpt=='P' || rpt=='E'|| rpt=='S' || rpt=='A'){
        return true;
    }else{
        return false;
    }
}

void segunda_lista_comandos(char* dato){
    do{
        system("clear");
        printf("\n\t"COLOR_AMARILLO"COMANDOS DISPONIBLES:"COLOR_NORMAL"\n\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información especie presione tecla M\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información pokémon presione tecla P\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Evolucionar pokémon presione tecla E\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Avistar pokemon presione tecla A\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Pedir ayuda presione tecla H\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Salir del programa sin guardar cambios presione tecla S\n");

        scanf("%c", &(*dato));    

    }while(verificar_segunda_entrada(*dato)==false || (*dato) =='H');
}


bool verificar_tercera_entrada(char vary){
    if(vary=='G' || vary=='M' || vary=='P' || vary=='V'|| vary=='C'|| vary=='S'|| vary=='E'){
        return true;
    }else{
        return false;
    }
}
void tercera_lista_comandos(char* dato){
    do{
        system("clear");
        printf("\n\t"COLOR_AMARILLO"COMANDOS DISPONIBLES:"COLOR_NORMAL"\n\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Guardar Pokedex  presione tecla G\n"); 
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información especie presione tecla M\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información pokémon presione tecla P\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Vistas recientes presione tecla V\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Capturas recientes presione tecla C\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Pedir ayuda presione tecla H\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Evolucionar pokemon presione tecla E\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Salir del programa sin guardar cambios presione tecla S\n");
        scanf("%c", &(*dato));    
        
    }while(verificar_tercera_entrada(*dato)==false || (*dato)=='H');

}

bool verificar_cuarta_entrada(char vary){
    if(vary=='G' || vary=='M' || vary=='P' || vary=='V'|| vary=='C'|| vary=='S'|| vary=='A' || vary=='E'){
        return true;
    }else{
        return false;
    }

}
void cuarta_lista_comandos(char* dato){
    do{
        system("clear");
        printf("\n\t"COLOR_AMARILLO"COMANDOS DISPONIBLES:"COLOR_NORMAL"\n\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Guardar Pokedex  presione tecla G\n"); 
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información especie presione tecla M\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información pokémon presione tecla P\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Vistas recientes presione tecla V\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Capturas recientes presione tecla C\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Pedir ayuda presione tecla H\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Avistar pokemon presione tecla A\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Evolucionar pokemon presione tecla E\n");//agree
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Salir del programa sin guardar cambios presione tecla S\n");
        scanf("%c", &(*dato));    
        
    }while(verificar_cuarta_entrada(*dato)==false || (*dato)=='H');

}


bool verificar_quinta_entrada(char var){
    if(var=='S'|| var=='A'|| var=='E'|| var=='M'|| var=='P'){
        return true;
    }else{
        return false;
    }
}
void quinta_lista_comandos(char* dato){
    do{
        system("clear");
        printf("\n\t"COLOR_AMARILLO"COMANDOS DISPONIBLES:"COLOR_NORMAL"\n\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Salir del programa sin guardar cambios presione tecla S\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Pedir ayuda presione tecla H\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Avistar pokemon presione tecla A\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Evolucionar pokemon presione tecla E\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información de la especie presione tecla M\n");
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO"Información pokémon presione tecla P\n");
        
        scanf("%c", &(*dato)); 

    }while(verificar_quinta_entrada(*dato)==false || (*dato)=='H');
}


void comandos_completos(pokedex_t** pokedex, char comando_ingresado){
    char rpta;
    char ruta_avistamiento[MAX_RUTA];
    char ruta_archivo_evoluciones[MAX_RUTA];
    int numero_especie;
    char nombre_pokemon[MAX_NOMBRE];
    
    switch(comando_ingresado){

        case 'G'://Guarda la Pokedex. Realiza la accion de guardar la infomación en el archivo pokedex.txt
            printf("\n\n");
            if(pokedex_apagar(*pokedex)==EXITO){
                printf("\nSe guardó la informacion de la pokedex en el archivo pokedex.txt\n");
            }else{
                printf("\nError interno... No se pudo guardar la informacion correctamente\n");
            }
            printf("\n\n");
            getchar();
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            segunda_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break;

        case 'S'://salir del programa sin guardar
            system("clear");
            pokedex_destruir(*pokedex);
            printf("\n"COLOR_ROJO">>>> Salió de la pokedex, recuerde si no usó el comando G antes de esta acción el programa no guardó los cambios."COLOR_NORMAL"\n\n");
            return;
        break;

  
        case 'A'://:Actualizará la Pokedex incorporando a ella los Pokémon avistados. La información de los nuevos avistamientos se encuenta en en archivo avistamientos.txt.
            
            printf("\n\n");
            printf("Ingrese la ruta del archivo extension .txt de avistamiento: ");
            scanf(" %s", ruta_avistamiento);
            printf("\n");
            if(pokedex_avistar(*pokedex, ruta_avistamiento)==EXITO){
                printf("\n\n");
                printf("Se actualizó los pokemones del archivo avistamiento\n\n");
                getchar();
                printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
                getchar();
                tercera_lista_comandos(&rpta);
    
            }else{
                printf("Error, no se pudo cargar en la pokedex los datos del archivo avistamiento.\n\n");
                getchar();
                printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
                getchar();
                segunda_lista_comandos(&rpta);
            }
           
            comandos_completos(pokedex, rpta);
        break;

        case 'E':
            printf("\n\n");
            printf("Ingrese la ruta del archivo de pokemones evolucionados: ");
            scanf(" %s", ruta_archivo_evoluciones);
            printf("\n");
            if(pokedex_evolucionar(*pokedex, ruta_archivo_evoluciones)==EXITO){
                printf("Se actualizó las evoluciones de la pokedex\n\n");
            }else{
                printf("Error interno... No se actualizó todas las evoluciones de la pokedex\n\n");
                
            }
            getchar();
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            cuarta_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break;

        case 'C'://Muestra los últimos Pokémon capturados
            printf("\n");
            getchar();
            pokedex_ultimos_capturados(*pokedex);
            printf("\n");
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            cuarta_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break;

        case 'V'://Muestra los últimos Pokémon vistos
            printf("\n");
            pokedex_ultimos_vistos(*pokedex);
            printf("\n");
            getchar();
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            cuarta_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break;

        case 'M'://Muestra la información de la especie.

            printf("\n");
            printf("Ingrese el numero de la especie del pokemon: ");
            scanf(" %i", &numero_especie); 
            printf("\n");
            getchar();
           
            especie_pokemon_t* especie = (especie_pokemon_t*) arbol_buscar((*pokedex)->pokemones, (void*)&numero_especie );
            if(especie!=NULL){
                
                printf("Datos de la especie N° %i\n", especie->numero);
                printf("Nombre: %s\n", especie->nombre);
                printf("Descripcion: %s\n", especie->descripcion);
            }else{
                printf("No se encontró el numero de la especie del pokemon =( \n");
            }
            printf("\n\n");
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            quinta_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break;

        case 'P'://Muestra la información de un Pokémon de una determinada especie.

            printf("\n");
            printf("Ingrese el numero de especie del pokemon: ");
            scanf(" %i", &numero_especie);
            printf("\n");
            printf("Ingrese el nombre del pokemon: ");
            scanf(" %s", nombre_pokemon);/*nombre vacio es enter?*/ //getchar(nombre_pokemon)
            printf("\n\n");
            pokedex_informacion(*pokedex, numero_especie, nombre_pokemon);
            printf("\n");
            getchar();
            printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
            getchar();
            quinta_lista_comandos(&rpta);
            comandos_completos(pokedex, rpta);
        break; 
    }
}


int main(){
    
    system("clear");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t"COLOR_AMARILLO"Bienvenido a la Pokedex"COLOR_NORMAL"\n \t\t\t\t"COLOR_AMARILLO"Lea bien las indicaciones y considere los comandos con mayuscula =)"COLOR_NORMAL"\n\n\n");
  
    char comando;
    printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar...\n");
    getchar();
    primera_lista_comandos(&comando);

    if(comando=='I'){
         
        pokedex_t* pokedex = pokedex_prender();
        if(pokedex==NULL){
            printf(COLOR_ROJO"Ocurrió un error interno, no se pudo crear la pokedex."COLOR_NORMAL"\n");
            printf(COLOR_ROJO"...inicie nuevamente el programa (o_O)"COLOR_NORMAL"\n\n");
            pokedex_destruir(pokedex);
            return 0;
        }
        printf("\n");
        getchar();
        printf(COLOR_AMARILLO"==>"COLOR_BLANCO" Presione enter para continuar..."COLOR_NORMAL);
        getchar();
        segunda_lista_comandos(&comando);
        comandos_completos(&pokedex, comando);
    }else{
        printf(COLOR_ROJO"El programa a terminado."COLOR_NORMAL"\n");
    }
   
    return 0;
}  
