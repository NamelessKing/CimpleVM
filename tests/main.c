#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    char *s = "ciao -12 a tutti";
    int v;



    v = atoi(&s[5]);



    printf("%d",v);






	return 0;
}
