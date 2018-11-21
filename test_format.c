#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

bool test_format(int i ){
    int a;
    char b[] =  "";

	bool resulat = true;
	a=convertDecimalToOctal(i);
	sprintf(b,"%d",a);


    for(int j=0; j<4;j++){

        if (b[j]==b[j+1])resulat=false;
}
	return resulat;

}
