#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include "leggi.h"
#include "definitions.h"



/*
La funzione "int* prendi_array_istruzioni(char *input,int *CODE,int *dim_array_istruzioni)"
prende come argomento:(char *input,int *CODE,int *dim_array_istruzioni) e restituisce un puntatore ad
un array dinamico(istruzione da eseguire o stampare).
Se il file è valido,l'ambiente chiamante di questa funione,riceve per referenza un codice(int *CODE) di errore o successo
e la dimensione dell'array dinamico contenente le estruzioni(int *dim_array_istruzioni).

codice = -4 (erroe apetura file)
       = -3 (file non valido )
       = -2 (file non valido perche troppe istruzioni rispetto la lunghezza data )
       = -1 (il file e valido ma le istruzioni sono minori rispetto la lunghezza data)
       =  1 (il file e valido )
*/
int* prendi_array_istruzioni(char *input,int *CODE,int *dim_array_istruzioni){

    /*array istruzioni in caso di successo dell apertura file/file valido,verra popolato*/
    int *array_istruzioni=NULL;
    FILE *fp_input;

    /*variabili che verrano usati con getline per prendere ogni linea*/
    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    /*istruzione/valore valido per linea*/
    int val_presente,val_ritorno,dimensione_array = 0,i_array = 0;

    fp_input = fopen(input, "r");

    if (fp_input == NULL){
        array_istruzioni = NULL;
        *CODE = -4;/*0 file non esistente*/
        *dim_array_istruzioni = 0;
        return array_istruzioni;
    }else{

        while((read = getline(&line, &len, fp_input)) != -1){

            val_presente = prendi_valore_dalla_linea(line,&val_ritorno);

            if(!val_presente){
                system("clear");
                printf("ERRORE(OVERFLOW FILE): valore da file supera il MASSIMO o MINIMO consentito dal tipo INT\n");
                exit(EXIT_FAILURE);
            }

            if(!dimensione_array && val_presente == 1){
                if(val_ritorno){
                    dimensione_array = val_ritorno;
                    array_istruzioni = (int *)malloc(sizeof(int)*dimensione_array);
                }
            }else{

                if(val_presente == 1){
                    if(i_array < dimensione_array){
                        /*printf("val_ritorno = %d\n",val_ritorno);*/
                        array_istruzioni[i_array] = val_ritorno;
                        /*printf("%d -> %d\n",i_array,array_istruzioni[i_array]);*/
                    }
                    i_array++;
                }
            }
        }


        free(line);
        fclose(fp_input);

        i_array--;


        if(!dimensione_array){
            *dim_array_istruzioni = dimensione_array;
            *CODE = -3;/*file vuoto o file non valido*/
            return array_istruzioni;
        }


        if(i_array>=dimensione_array){
            free(array_istruzioni);
            array_istruzioni = NULL;
            *dim_array_istruzioni = 0;
            *CODE = -2;/*-2 file non valido perche troppe istruzioni rispetto la lunghezza data*/
            /*exit(EXIT_FAILURE);*/
            return array_istruzioni;
        }else
        if(i_array<dimensione_array - 1 ){
            *dim_array_istruzioni  = i_array + 1;
            *CODE = -1;/*-1 WARNIG: il file e valido ma le istruzioni sono minori rispetto la lunghezza data*/
            return array_istruzioni;
        }else{
            *dim_array_istruzioni = dimensione_array;
            *CODE = 1;/* 1 ok, il numero delle istruzioni e coerente con la dimensione data dal file*/
            return array_istruzioni;
        }

    }
}


/*
La "int prendi_valore_dalla_linea(char *line,int *val_ritorno)"
prende l'istruzione dalla stringa in input (char *line)
se la stringa e valida il valore viene salvato su (int *val_ritorno)
se invece non è valida (result == -1) oppure il valore della stringa
e troppo grande(result == 0) per un intero(overflow o unterflow),
allora *val_ritorno viene imposatato a NULL.

Una stringa valida è quando si incontra in un indice (seguita solo da spazi o tabulazioni),
un numero un '-'seguida da un numero:
Condizione per una linea valida:
(line[i] >= '0' && line[i] <= '9') || ((line[i] == '-') && (line[i + 1] >= '0' && line[i + 1] <= '9'))
con tale condizione si preleva il numero con la funzione atoi()

*/
int prendi_valore_dalla_linea(char *line,int *val_ritorno){
    int i,result,flag = 0;

    i = 0;
    while(line[i] && !flag){
        if(line[i] == ' ' || line[i] == '\t' ){
            i++;
        }else
        if((line[i] >= '0' && line[i] <= '9') || ((line[i] == '-') && (line[i + 1] >= '0' && line[i + 1] <= '9'))){
            result = num_da_file_overflow(&line[i]);
            flag = 1;
        }else{
            result = -1;
            flag = 1;
        }
    }

    if(result == -1 ){/* result = -1 -> linea non valida*/
        val_ritorno = NULL;
    }

    if(result == 0 ){/* result = 0 -> valore file non consentito per overflow*/
        val_ritorno = NULL;
    }

    if(result == 1 ){/*result = 1 -> linea valida*/
        *val_ritorno = atoi(&line[i]);
    }

    return result;

}


/*
La "int num_da_file_overflow(char *s)"
prende come input una stringa ritorna 0 (overflow) se il numero in quella stringa
non puo essere contenuto in un INT,ritorna 1 se il numero puo essere contenuto
*/

int num_da_file_overflow(char *s){

    int j,s_dim=0;

    char s_max_int[40],s_min_int[40],*ptr_check,*ptr_to_s;

    sprintf(s_max_int,"%d",INT_MAX);
    sprintf(s_min_int,"%d",INT_MIN);


    if(*s == '-'){
        ptr_to_s = &s[1];
        ptr_check = &s_min_int[1];


    }else{
        ptr_to_s = s;
        ptr_check = s_max_int;
    }

    j = 0;
    while(ptr_to_s[j]>= '0' && ptr_to_s[j]<= '9'){
        s_dim++;
        j++;
    }

    if(s_dim>(int)strlen(ptr_check)){
        return 0;/*si overflow*/
    }else
    if(s_dim<(int)strlen(ptr_check)){
        return 1;/*no overflow*/
    }else{



        j = 0;
        while(ptr_to_s[j] == ptr_check[j] && j<s_dim){
            j++;
        }


        if(j == s_dim || (ptr_to_s[j] < ptr_check[j])){
            /*no overflow*/
            return 1;
        }

        if(ptr_to_s[j] > ptr_check[j]){
            /*si overflow*/
            return 0;
        }

    }
    return 0;
}



