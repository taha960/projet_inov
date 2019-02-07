#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int test_format(int i );
int convertDecimalToOctal(int decimalNumber);
long long convertOctalToDecimal(int octalNumber);


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


int convertDecimalToOctal(int decimalNumber)
{
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}

long long convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}
int test_format(int i ){
    int a;
    char b[] =  "";

    int resulat = 1;
    a=convertDecimalToOctal(i);
    sprintf(b,"%d",a);


    for(int j=0; j<4;j++){

        if (b[j]==b[j+1])resulat=1;
}
    return resulat;

}
