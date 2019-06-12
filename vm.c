#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "leggi.h"
#include "stampa.h"
#include "esegui.h"
#include "definitions.h"



int main(int argc, char *argv[]) {


    /*dichiarazione dei 3 array (array_istruzioni,stack,registers)*/
    int *array_istruzioni,dim_array_istruzioni;
    unsigned int IP=0;
    int stack[STACKSIZE];
    unsigned int SP=0;
    int registers[NREGISTERS]={0};
    /*unsigned int i_register;*/
    /*variabile che prende il il codice di vari stati ritornato dalla funzione prendi_array_istruzioni(argv[2],&ERROR_CODE,&dim_array_istruzioni) */
    int ERROR_CODE;


    if (argc != 3){
        system("clear");
        printf("ERRORE(ARGOMENTI LINEA DI COMANDO):Numeri argomenti da linea di comando non validi\n");
        exit(EXIT_FAILURE);
    }


    if(strcmp(argv[1], "stampa") == 0){
        array_istruzioni = prendi_array_istruzioni(argv[2],&ERROR_CODE,&dim_array_istruzioni);

        if(ERROR_CODE == -4){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):Errore apertura file (%s)\n",argv[2]);
            exit(EXIT_FAILURE);
        }else
        if(ERROR_CODE == -3){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):File non valido (%s)\n",argv[2]);
            exit(EXIT_FAILURE);
        }else
        if(ERROR_CODE == -2){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):File non valido perche troppe istruzioni rispetto la lunghezza data \n");
            exit(EXIT_FAILURE);
        }else{

           if(ERROR_CODE == -1 || ERROR_CODE == 1){
                if(ERROR_CODE == -1){
                    printf("WARNING(FILE):Il file e valido ma le istruzioni sono minori rispetto la lunghezza data\n\n");
                }
                stampa(array_istruzioni,dim_array_istruzioni);
            }
            free(array_istruzioni);
        }
    }else
    if(strcmp(argv[1], "esegui") == 0){
        array_istruzioni = prendi_array_istruzioni(argv[2],&ERROR_CODE,&dim_array_istruzioni);

        if(ERROR_CODE == -4){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):Errore apertura file (%s)\n",argv[2]);
            exit(EXIT_FAILURE);
        }else
        if(ERROR_CODE == -3){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):File non valido (%s)\n",argv[2]);
            exit(EXIT_FAILURE);
        }else
        if(ERROR_CODE == -2){
            free(array_istruzioni);
            system("clear");
            printf("ERRORE(FILE):File non valido perche troppe istruzioni rispetto la lunghezza data \n");
            exit(EXIT_FAILURE);
        }else{

           if(ERROR_CODE == -1 || ERROR_CODE == 1){
                if(ERROR_CODE == -1){
                    printf("WARNING(FILE):Il file e valido ma le istruzioni sono minori rispetto la lunghezza data\n\n");
                }
                esegui(array_istruzioni,dim_array_istruzioni,&IP,stack,&SP,registers);
            }
            free(array_istruzioni);
        }
    }else{
        system("clear");
        printf("ERRORE(ARGOMENTI LINEA DI COMANDO):Comando (%s) non valido\n",argv[1]);
        exit(EXIT_FAILURE);
    }



    return 0;

}

