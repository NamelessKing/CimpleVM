#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include "esegui.h"
#include "definitions.h"


void esegui(int *array_istruzioni,int dim_array_istruzioni,unsigned int *IP,int stack[STACKSIZE],unsigned int*SP,int registers[NREGISTERS]){

    int halt = 0;
    int temp;

    while( !halt && array_istruzioni[*IP] != HALT ){


        switch (array_istruzioni[*IP]) {
     	    case DISPLAY:

       	    		printf("%d\n",registers[array_istruzioni[*IP+1]]);

       	    		*IP+=2;
       	    		break;
     	    case PRINT_STACK:


       	    		print_stack(stack,*SP - array_istruzioni[*IP+1],*SP - 1);


       	    		*IP+=2;
       	    		break;
       		case PUSH:
       	    		push(registers[array_istruzioni[*IP+1]],stack,SP);

       	    		*IP+=2;
       	    		break;
       		case POP:
                    if(pop(stack,SP,&temp)){
                        registers[array_istruzioni[*IP+1]] = temp;
                    }

       	    		*IP+=2;
       	    		break;
       		case MOV:

                    mov(array_istruzioni[*IP+1],array_istruzioni[*IP+2],registers);

       	    		*IP+=3;
       	    		break;
       		case CALL:
       	    		push((int)(*IP + 2),stack,SP);
       	    		jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni);

       	    		break;
       		case RET:


       		        if(pop(stack,SP,&temp)){
           		        *IP = (unsigned int) temp;
       		        }

       	    		break;
       		case JMP:

                    jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni);

       	    		break;
       		case JZ:
       		        if(stack[*SP - 1] == 0){
                        jmp(array_istruzioni[*IP+1],IP,dim_array_istruzioni);
                        *SP-=1;
       		        }else{
       		            *SP-=1;
       		            *IP+=2;
       		        }



       	    		break;
       		case JPOS:
                    if(stack[*SP - 1] > 0){
                        jmp(array_istruzioni[*IP+1],IP,dim_array_istruzioni);
                        *SP-=1;
       		        }else{
       		            *SP-=1;
       		            *IP+=2;
       		        }


       	    		break;
       		case JNEG:
                    if(stack[*SP - 1] < 0){
                        jmp(array_istruzioni[*IP+1],IP,dim_array_istruzioni);
                        *SP-=1;
       		        }else{
       		            *SP-=1;
       		            *IP+=2;
       		        }


       	    		break;
       		case ADD:

                    if(add(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]])){
                        push(temp,stack,SP);
                        *IP+=3;
                    }else{
                        halt = 1;
                    }


       	    		break;
       		case SUB:
       	    		if(add(&temp,registers[array_istruzioni[*IP+1]],-registers[array_istruzioni[*IP+2]])){
                        push(temp,stack,SP);
                        *IP+=3;
                    }else{
                        halt = 1;
                    }


       	    		break;
       		case MUL:
       	    		if(multi(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]])){
                        push(temp,stack,SP);
                        *IP+=3;
                    }else{
                        halt = 1;
                    }

       	    		break;
       		case DIV:
       	    		if(divi(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]])){
                        push(temp,stack,SP);
                        *IP+=3;
                    }else{
                        halt = 1;
                    }
       	    		break;
    	    default:
                    printf("ERRORE STRUTTURA CODICE MACCHINA\n");
                    halt = 1;
    	     		break;
	    }

    }

}


void print_stack(int stack[STACKSIZE],int n,int sp){
    while(sp>=n){
        printf("\n[%d] %d\n",sp,stack[sp]);
        sp--;
    }
}


int push(int valore,int stack[STACKSIZE],unsigned int *SP){
    if(*SP<STACKSIZE){
        stack[*SP] = valore;
        *SP+=1;
        return 1;
    }else{
        return 0;
    }
}


int pop(int stack[STACKSIZE],unsigned int *SP,int *valore){
    if(*SP>0 ){
        *SP-=1;
        *valore = stack[*SP];
        return 1;
    }else{
        return 0;
    }
}


void mov(int i_registro,int valore,int registers[NREGISTERS]){
    registers[i_registro] = valore;
}



int jmp(int valore,unsigned int *IP,int dim_array_istruzioni){
    if(valore >= 0 && valore < dim_array_istruzioni ){
        *IP = (unsigned int)valore;

        /*printf("IP = %d    dim_array_istruzioni = %d \n\n\n",*IP,dim_array_istruzioni);*/
        return 1;
    }else{
        return 0;
    }
}

int add(int* result, int a, int b){
	*result = a + b;
	if(a > 0 && b > 0 && *result <= 0)
		return 0;
	if(a < 0 && b < 0 && *result >= 0)
		return 0;
	return 1;
}

int multi(int * result,int a, int b){


    /*printf("%d * %d = %d\n\n\n",a,b,a*b);*/

    if((a == INT_MIN && b == -1) || (b == INT_MIN && a == -1)){
       return 0;
    }

    *result = a * b;
    if (a == 0 || b == 0)
    	return 1;


	if (a == (*result / b))
		return 1;
	else
		return 0;
}

int divi(int * result,int a, int b){
    if(b == 0)
        return 0;
    else{
        *result = a/b;
        return 1;
    }
}

