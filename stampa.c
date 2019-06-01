#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stampa.h"
#include "definitions.h"

/*void delme_1(){
}*/


void stampa(int *array_istruzioni,int dim_array_istruzioni){
    int i = 0;

    while(i < dim_array_istruzioni){

        switch (array_istruzioni[i]) {
       	    case HALT:
       	    		printf("[  %d]  HALT\n",i);
       	    		i+=1;
       	    		break;
     	    case DISPLAY:
       	    		printf("[  %d]  DISPLAY R%d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
     	    case PRINT_STACK:
       	    		printf("[  %d]  PRINT_STACK %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case PUSH:
       	    		printf("[  %d]  PUSH R%d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case POP:
       	    		printf("[  %d]  POP R%d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case MOV:
       	    		printf("[  %d]  MOV R%d %d\n",i,array_istruzioni[i+1],array_istruzioni[i+2]);
       	    		i+=3;
       	    		break;
       		case CALL:
       	    		printf("[  %d]  CALL %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case RET:
       	    		printf("[  %d]  RET\n",i);
       	    		i+=1;
       	    		break;
       		case JMP:
       	    		printf("[  %d]  JMP %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case JZ:
       	    		printf("[  %d]  JZ %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case JPOS:
       	    		printf("[  %d]  JPOS %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case JNEG:
       	    		printf("[  %d]  JNEG %d\n",i,array_istruzioni[i+1]);
       	    		i+=2;
       	    		break;
       		case ADD:
       	    		printf("[  %d]  ADD R%d R%d\n",i,array_istruzioni[i+1],array_istruzioni[i+2]);
       	    		i+=3;
       	    		break;
       		case SUB:
       	    		printf("[  %d]  SUB R%d R%d\n",i,array_istruzioni[i+1],array_istruzioni[i+2]);
       	    		i+=3.;
       	    		break;
       		case MUL:
       	    		printf("[  %d]  MUL R%d R%d\n",i,array_istruzioni[i+1],array_istruzioni[i+2]);
       	    		i+=3;
       	    		break;
       		case DIV:
       	    		printf("[  %d]  DIV R%d R%d\n",i,array_istruzioni[i+1],array_istruzioni[i+2]);
       	    		i+=3;
       	    		break;
    	    default:
                    printf("ERRORE STRUTTURA CODICE MACCHINA\n");
                    i = dim_array_istruzioni;
    	     		break;
	    }

    }

}
