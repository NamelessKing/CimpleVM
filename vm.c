#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leggi.h"
#include "stampa.h"

/*
gcc -g3 -std=gnu89 -fuse-ld=gold -fsanitize=address -fsanitize=undefined -pedantic-errors -Wall -Wextra -o file prove.c && ./file
*/

int main() {

    char filename[] = "test.cvm";
    int *array_istruzioni;
    int dim_array_istruzioni;
    int ERROR_CODE;


    array_istruzioni = prendi_array_istruzioni(filename,&ERROR_CODE,&dim_array_istruzioni);
    printf("CODICE:%d\n",ERROR_CODE);


    printf("DIMENSIONE:%d\n",dim_array_istruzioni);

    if(ERROR_CODE == -2 || ERROR_CODE == 1){
        stampa(array_istruzioni,dim_array_istruzioni);
    }


    free(array_istruzioni);
    return 0;

}

