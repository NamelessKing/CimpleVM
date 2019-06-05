#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leggi.h"
#include "stampa.h"
#include "esegui.h"
#include "definitions.h"

/*
gcc -g3 -std=gnu89 -fuse-ld=gold -fsanitize=address -fsanitize=undefined -pedantic-errors -Wall -Wextra -o file prove.c && ./file
*/




int main() {

    char filename[] = "Test_estremo.cvm";

    int *array_istruzioni,dim_array_istruzioni;
    unsigned int IP=0;
    int stack[STACKSIZE];
    unsigned int SP=0;
    int registers[NREGISTERS]={0};
    /*unsigned int i_register;*/
    int ERROR_CODE;


    array_istruzioni = prendi_array_istruzioni(filename,&ERROR_CODE,&dim_array_istruzioni);
    printf("CODICE:%d\n",ERROR_CODE);


    printf("DIMENSIONE:%d\n",dim_array_istruzioni);

    if(ERROR_CODE == -2 || ERROR_CODE == 1){
        stampa(array_istruzioni,dim_array_istruzioni);
    }


    esegui(array_istruzioni,dim_array_istruzioni,&IP,stack,&SP,registers);


    free(array_istruzioni);
    return 0;

}

