#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leggi.h"

/*
gcc -g3 -std=gnu89 -fuse-ld=gold -fsanitize=address -fsanitize=undefined -pedantic-errors -Wall -Wextra -o file prove.c && ./file
*/

int main() {

    int i;
    char filename[] = "test.cvm";
    int *array_istruzioni;
    int dim_array_istruzioni;
    int ERROR_CODE;


    array_istruzioni = prendi_array_istruzioni(filename,&ERROR_CODE,&dim_array_istruzioni);
    printf("CODICE:%d\n",ERROR_CODE);


    printf("DIMENSIONE:%d\n",dim_array_istruzioni);
    for(i = 0;i<dim_array_istruzioni;i++){
        printf("%d\n",array_istruzioni[i]);
    }

    free(array_istruzioni);
    return 0;

}

