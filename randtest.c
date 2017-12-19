#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(){
unsigned int iseed = (unsigned int)time(NULL);
srand(iseed);
int i;
int j;
printf("define N 30\n");

printf("define DEFAULT_INT_BITS N\n");

printf("unsigned int S,O;\n");
printf("module void main(){\n");



printf("O=0;\n" );
i = rand()& 0b00111111111111111111111111111111;
printf("O= %d;\n",i);
for (j=0; j<9; j++)
{
i= rand()& 0b00111111111111111111111111111111;
printf("if\n");
printf(":: (S==%d)-> O=%d;\n", i, i);
printf(":: else -> skip;\n");
printf("fi\n");
}
printf("S=0;\n");
printf("}\n");



}

