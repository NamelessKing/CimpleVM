#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include<errno.h>
#include "esegui.h"
#include "definitions.h"


void esegui(int *array_istruzioni,int dim_array_istruzioni,unsigned int *IP,int stack[STACKSIZE],unsigned int*SP,int registers[NREGISTERS]){

    int halt = 0;
    int temp,operations_return_value;


    while( !halt && array_istruzioni[*IP] != HALT ){


        switch (array_istruzioni[*IP]) {
     	    case DISPLAY:

                    if(array_istruzioni[*IP+1]<32 && array_istruzioni[*IP+1]>=0){
                        printf("%d\n",registers[array_istruzioni[*IP+1]]);
                    }else{
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [DISPLAY] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [DISPLAY] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }
                    }

       	    		*IP+=2;

       	    		if(((int)*IP>=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW):[DISPLAY] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}

       	    		break;
     	    case PRINT_STACK:


                    if(((int)*SP - array_istruzioni[*IP+1])<0){
                        system("clear");
                        printf("ERRORE(UNDERFLOW): [PRINT_STACK] stack[%d] indice per stack fuori dal limite\n",(*SP - array_istruzioni[*IP+1]));
                        printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                        exit(EXIT_FAILURE);
                    }


       	    		print_stack(stack,*SP - array_istruzioni[*IP+1],*SP - 1);


       	    		*IP+=2;

       	    		if(((int)*IP>=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW): [PRINT_STACK] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}
       	    		break;
       		case PUSH:


       		        if(!push(registers[array_istruzioni[*IP+1]],stack,SP)){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [PUSH] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                        printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                        exit(EXIT_FAILURE);
       		        }

       	    		*IP+=2;

       	    		if(((int)*IP>=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW): [PUSH] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}
       	    		break;
       		case POP:
                    if(pop(stack,SP,&temp)){
                        registers[array_istruzioni[*IP+1]] = temp;
                    }else{
                        system("clear");
                        printf("ERRORE(UNDERFLOW): [POP] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                        printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                        exit(EXIT_FAILURE);
                    }

       	    		*IP+=2;

       	    		if(((int)*IP>=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW): [POP] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}
       	    		break;
       		case MOV:

       		        if(array_istruzioni[*IP+1]<32 && array_istruzioni[*IP+1]>=0){
                        mov(array_istruzioni[*IP+1],array_istruzioni[*IP+2],registers);
                    }else{

                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [MOV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [MOV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }

                    }

       	    		*IP+=3;

       	    		if(((int)*IP>=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW): [MOV] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}
       	    		break;
       		case CALL:

                    if(((int)*IP+2 >=dim_array_istruzioni)){
       	    		    system("clear");
                        printf("ERRORE(OVERFLOW): [CALL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+2);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
       	    		}else{

       	    		    if(!push((int)(*IP + 2),stack,SP)){
                            system("clear");
                            printf("ERRORE(OVERFLOW): [CALL] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
       		            }



       		            if(!jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni)){

                            if(array_istruzioni[*IP+1]<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [CALL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [CALL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }
       		            }
       	    		}


       	    		break;
       		case RET:

       		        if(pop(stack,SP,&temp)){

           		        if(!jmp(temp,IP,dim_array_istruzioni)){

                            if(temp<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [RET] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",temp);
                                printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [RET] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",temp);
                                printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                                exit(EXIT_FAILURE);
                            }
       		            }
       		        }else{
       		            system("clear");
                        printf("ERRORE(UNDERFLOW): [RET] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                        printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                        exit(EXIT_FAILURE);
       		        }

       	    		break;
       		case JMP:

                    if(!jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni)){

                            if(array_istruzioni[*IP+1]<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [JMP] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [JMP] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }
   		            }

       	    		break;
       		case JZ:
       		        if(stack[*SP - 1] == 0){

                        if(!jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni)){

                            if(array_istruzioni[*IP+1]<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [JZ] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [JZ] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }
   		                }


                        if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JZ] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }

       		        }else{

       		            if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JZ] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }


       		            *IP+=2;
       		            if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [JZ] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }
       		        }



       	    		break;
       		case JPOS:
                    if(stack[*SP - 1] > 0){


                        if(!jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni)){

                            if(array_istruzioni[*IP+1]<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [JPOS] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [JPOS] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }
   		                }


                        if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JPOS] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }




       		        }else{


       		            if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JPOS] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }


       		            *IP+=2;
       		            if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [JPOS] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }


       		        }


       	    		break;
       		case JNEG:
                    if(stack[*SP - 1] < 0){


                        if(!jmp(array_istruzioni[*IP + 1],IP,dim_array_istruzioni)){

                            if(array_istruzioni[*IP+1]<0){
                                system("clear");
                                printf("ERRORE(UNDERFLOW): [JNEG] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }else{
                                system("clear");
                                printf("ERRORE(OVERFLOW): [JNEG] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",array_istruzioni[*IP+1]);
                                exit(EXIT_FAILURE);
                            }
   		                }


                        if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JNEG] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }



       		        }else{
       		            if(((int)(*SP) - 1) < 0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [JNEG] stack[%d] indice per stack fuori dal limite\n",(int)*SP - 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
                        }else{
                            *SP-=1;
                        }


       		            *IP+=2;
       		            if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [JNEG] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }
       		        }


       	    		break;
       		case ADD:


                    if((((int)*IP+1) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [ADD] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+1);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }

                    if((((int)*IP+2) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [ADD] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+2);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }


                    if(array_istruzioni[*IP+1]>=32 || array_istruzioni[*IP+1]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [ADD] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [ADD] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }
                    }


                    if(array_istruzioni[*IP+2]>=32 || array_istruzioni[*IP+2]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [ADD] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [ADD] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }
                    }



                    operations_return_value = add(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);

                    /*overflow*/
                    if(operations_return_value == 1 ){
                        system("clear");
                        printf("ERRORE(INT OVERFLOW): [ADD] %d + %d -> operazione non consentita,il risultato supera il MASSIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else
                    if(operations_return_value == -1){
                        system("clear");
                        printf("ERRORE(INT UNDERFLOW): [ADD] %d + %d -> operazione non consentita,il risultato supera il MINIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else{

                        if(!push(temp,stack,SP)){
                            system("clear");
                            printf("ERRORE(OVERFLOW): [ADD] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
       		            }

                        *IP+=3;
                        if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [ADD] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }

                    }

       	    		break;
       		case SUB:

                    if((((int)*IP+1) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [SUB] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+1);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }

                    if((((int)*IP+2) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [SUB] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+2);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }


                    if(array_istruzioni[*IP+1]>=32 || array_istruzioni[*IP+1]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [SUB] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [SUB] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }
                    }


                    if(array_istruzioni[*IP+2]>=32 || array_istruzioni[*IP+2]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [SUB] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [SUB] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }
                    }



                    operations_return_value = sub(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);

                    /*overflow*/
                    if(operations_return_value == 1 ){
                        system("clear");
                        printf("ERRORE(INT OVERFLOW): [SUB] %d - %d -> operazione non consentita,il risultato supera il MASSIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else
                    if(operations_return_value == -1){
                        system("clear");
                        printf("ERRORE(INT UNDERFLOW): [SUB] %d - %d -> operazione non consentita,il risultato supera il MINIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else{

                        if(!push(temp,stack,SP)){
                            system("clear");
                            printf("ERRORE(OVERFLOW): [SUB] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
       		            }

                        *IP+=3;
                        if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [SUB] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }

                    }


       	    		break;
       		case MUL:
                    if((((int)*IP+1) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [MUL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+1);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }

                    if((((int)*IP+2) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [MUL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+2);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }


                    if(array_istruzioni[*IP+1]>=32 || array_istruzioni[*IP+1]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [MUL] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [MUL] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }
                    }


                    if(array_istruzioni[*IP+2]>=32 || array_istruzioni[*IP+2]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [MUL] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [MUL] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }
                    }



                    operations_return_value = multi(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);

                    /*overflow*/
                    if(operations_return_value == 1 ){
                        system("clear");
                        printf("ERRORE(INT OVERFLOW): [MUL] %d * %d -> operazione non consentita,il risultato supera il MASSIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else
                    if(operations_return_value == -1){
                        system("clear");
                        printf("ERRORE(INT UNDERFLOW): [MUL] %d * %d -> operazione non consentita,il risultato supera il MINIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else{

                        if(!push(temp,stack,SP)){
                            system("clear");
                            printf("ERRORE(OVERFLOW): [MUL] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
       		            }

                        *IP+=3;
                        if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [MUL] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }

                    }



       	    		break;
       		case DIV:

                    if((((int)*IP+1) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [DIV] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+1);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }

                    if((((int)*IP+2) >= dim_array_istruzioni) ){
                        system("clear");
                        printf("ERRORE(OVERFLOW): [DIV] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP+2);
                        printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                        exit(EXIT_FAILURE);
                    }


                    if(array_istruzioni[*IP+1]>=32 || array_istruzioni[*IP+1]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [DIV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [DIV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+1]);
                            exit(EXIT_FAILURE);
                        }
                    }


                    if(array_istruzioni[*IP+2]>=32 || array_istruzioni[*IP+2]<0){
                        if(array_istruzioni[*IP+1]<0){
                            system("clear");
                            printf("ERRORE(UNDERFLOW): [DIV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }else{
                            system("clear");
                            printf("ERRORE(OVERFLOW): [DIV] registers[%d] indice per registro fuori dal limite\n",array_istruzioni[*IP+2]);
                            exit(EXIT_FAILURE);
                        }
                    }



                    operations_return_value = divi(&temp,registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);

                    /*overflow*/
                    if(operations_return_value == 1 ){
                        system("clear");
                        printf("ERRORE(INT OVERFLOW): [DIV] %d / %d -> operazione non consentita,il risultato supera il MASSIMO consentito dal tipo INT\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else
                    if(operations_return_value == -1){
                        system("clear");
                        printf("ERRORE(DENOMINATORE = 0): [DIV] %d / %d -> operazione non consentita,divisione per 0\n",
                            registers[array_istruzioni[*IP+1]],registers[array_istruzioni[*IP+2]]);
                        exit(EXIT_FAILURE);
                    }else{

                        if(!push(temp,stack,SP)){
                            system("clear");
                            printf("ERRORE(OVERFLOW): [DIV] stack[%d] indice per stack fuori dal limite\n",(int)*SP + 1);
                            printf("L'indice consentito deve essere SP >= 0 e SP < %d\n",(int)STACKSIZE);
                            exit(EXIT_FAILURE);
       		            }

                        *IP+=3;
                        if(((int)*IP>=dim_array_istruzioni)){
           	    		    system("clear");
                            printf("ERRORE(OVERFLOW): [DIV] array_istruzioni[%d] indice per array_istruzioni fuori dal limite\n",*IP);
                            printf("L'indice consentito deve essere IP >= 0 e IP < %d\n",dim_array_istruzioni);
                            exit(EXIT_FAILURE);
       	    		    }

                    }


       	    		break;
    	    default:
    	            system("clear");
                    printf("ERRORE STRUTTURA CODICE MACCHINA\n");
                    exit(EXIT_FAILURE);
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

    if (((b > 0) && (a > (INT_MAX - b)))) {
        return 1;/*overflow*/
    } else
    if( ((b < 0) && (a < (INT_MIN - b)))){
        return -1;/*underflow*/
    }else{
        *result = a + b;
        return 0;/*operazione valida*/
    }

}



int sub(int* result, int a, int b){
    if (((b > 0) && (a < ( INT_MIN + b)))) {
        return 1;/*overflow*/
    } else
    if( ((b < 0) && (a > (INT_MAX + b)))){
        return -1;/*underflow*/
    }else{
        *result = a - b;
        return 0;/*operazione valida*/
    }
}




int multi(int * result,int a, int b){

    if (a > 0) {  /* a e positivo */
        if (b > 0) {  /* a e b sono positivi */
            if (a > (INT_MAX / b)) {

                return 1;/*overflow*/
            }
        } else { /* a positivo, b negativo */
            if (b < (INT_MIN / a)) {

                return -1;/*underflow*/
            }
        } /* a positivo, b negativo */
    } else { /* a  negativo */
        if (b > 0) { /* a negativo, b  positivo */
            if (a < (INT_MIN / b)) {

                return -1;
            }
        } else { /* a e b sono negativi */
            if ( (a != 0) && (b < (INT_MAX / a))) {

                return 1;/*overflow*/
            }
        }
    }

    *result = a * b;
    return 0;/*operazione valida*/

}

int divi(int * result,int a, int b){

    if(b == 0){
        return -1;/*divisione per 0*/
    }else
    if(((a == INT_MIN) && (b == -1))){
        return 1;/*overflow*/
    }else{
        *result = a / b;
        return 0;/*operazione valida*/

    }
}

