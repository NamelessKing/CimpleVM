#include "definitions.h"

void esegui(int *array_istruzioni,int dim_array_istruzioni,unsigned int *IP,int stack[STACKSIZE],unsigned int*SP,int registers[NREGISTERS]);


void print_stack(int stack[STACKSIZE],int n, int sp);


int push(int valore,int stack[STACKSIZE],unsigned int *SP);


int pop(int stack[STACKSIZE],unsigned int *SP,int *valore);


void mov(int i_registro,int valore,int registers[NREGISTERS]);


int jmp(int valore,unsigned int *IP,int dim_array_istruzioni);


int add(int* result, int a, int b);


int sub(int* result, int a, int b);


int multi(int * result,int a, int b);


int divi(int * result,int a, int b);
