#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leggi.h"
#include "definitions.h"

/*void delme_2(){
}*/

/*int controllo_valore_valido(char *line,int posPartenza){
    int i, eValido = 0;

    i = posPartenza;
    while(line[i]){
        if(line[i] >= '1' && line[i] <= '9'){

        }
    }
}*/

int prendi_valore_dalla_linea(char *line,int *val_ritorno){
    int i,flag = 0;

    i = 0;
    while(line[i] && !flag){
        if(line[i] == ' '){
            i++;
        }else
        if((line[i] >= '0' && line[i] <= '9') || line[i] == '-'){
            flag = 1;
        }else{
            flag = -1;
        }
    }

    if(flag == -1 || flag == 0){
        flag = 0;/* flag = 0 -> linea non valida*/
        val_ritorno = NULL;
    }

    if(flag == 1 ){/*flag = 1 -> linea valida*/
        *val_ritorno = atoi(&line[i]);
    }

    return flag;

}



int* prendi_array_istruzioni(char *input,int *CODE,int *dim_array_istruzioni){

    int *array_istruzioni=NULL;
    FILE *fp_input;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    /*istruzione/valore valido per linea*/
    int val_presente,val_ritorno,dimensione_array = 0,i_array = 0;

    fp_input = fopen(input, "r");

    if (fp_input == NULL){
        array_istruzioni = NULL;
        *CODE = -1;/*0 file non esistente*/
        *dim_array_istruzioni = 0;
        return array_istruzioni;
    }else{

        while((read = getline(&line, &len, fp_input)) != -1){

            val_presente = prendi_valore_dalla_linea(line,&val_ritorno);

            if(!dimensione_array && val_presente){
                if(val_ritorno){
                    dimensione_array = val_ritorno;
                    array_istruzioni = (int *)malloc(sizeof(int)*dimensione_array);
                }
            }else{

                if(val_presente){
                    if(i_array < dimensione_array){
                        array_istruzioni[i_array] = val_ritorno;
                        printf("%d -> %d\n",i_array,array_istruzioni[i_array]);
                    }
                    i_array++;
                }
            }
        }


        free(line);
        fclose(fp_input);

        i_array--;
        printf("i_array = %d     dimensione_array = %d \n",i_array,dimensione_array);



        if(!dimensione_array){
            *dim_array_istruzioni = dimensione_array;
            *CODE = -3;/*file vuoto o file non valido*/
            return array_istruzioni;
        }


        if(i_array>=dimensione_array){
            free(array_istruzioni);
            array_istruzioni = NULL;
            *dim_array_istruzioni = 0;
            *CODE = -1;/*-1 file non valido perche troppe istruzioni rispetto la lunghezza data*/
            return array_istruzioni;
        }else
        if(i_array<dimensione_array - 1 ){
            *dim_array_istruzioni  = i_array + 1;
            *CODE = -2;/*-2 WARNIG: il file e valido ma le istruzioni sono minori rispetto la lunghezza data*/
            return array_istruzioni;
        }else{
            *dim_array_istruzioni = dimensione_array;
            *CODE = 1;/* 1 ok, il numero delle istruzioni e coerente con la dimensione data dal file*/
            return array_istruzioni;
        }

    }
}





