#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

int main(){
int x;
printf("Saisissez 1 si vous voulez un transcodage avec data et 0 sinon :");
scanf("%d", &x);

if(x==0){
FILE *f = fopen("testt.txt", "w");
	for(int i=4161; i<=32247 ;i++ ){
        if (f == NULL){
            printf("Error opening file!\n");
            exit(1);}
        if (test_format(i)){
            fprintf(f, " %d,",i);
        }

}
    fclose(f);
}
if(x==1){
    int N ;
    int h ;
    int k ;
    int p ;
    printf("Saisissez la data :");
    scanf("%d", &p);


    FILE *f = fopen("test_1.txt", "w");
	for(int i=520; i<=4030 ;i++ ){
        if (f == NULL){
            printf("Error opening file!\n");
            exit(1);}
        if (test_format(i)){
            h=convertDecimalToOctal(i);
            N=convertDecimalToOctal(p);
            k= N*10000+h;
            k = convertOctalToDecimal(k);
            fprintf(f, " %d,\n",k);
        }

}
    fclose(f);
}
}
