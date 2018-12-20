#include "dsk6713_aic23.h"
#include "math.h"
#include "TablesPulsesAcoustiques.inc"
#include "FiltreBasseBand_18500_22000_400Coef.inc"
#include <stdio.h>
#include <stdlib.h>
Uint32 input_sample();
void output_sample(int out_data);
void comm_poll();
int detec_Pulse();

Uint32 fs = DSK6713_AIC23_FREQ_48KHZ;

#define RC              7
#define SEUIL_Detection 100

const short Coeff[8] = {-24636, -25997,	-27246,	-28378,	-29389,	-30274,	-31029,-31651};
Uint16 TabTrace[8];
short Xn,Yn;
short XnBuffer[N+1], YnBuffer[N];
short i, j, f;
short IntgC, Fx;
short Qn[8], Qn_1[8], Qn_2[8];
int tmp1, tmp2;
Uint16 t;
Uint32 Module[8];
int DetectionPulse;
struct Node{
Uint32 ModuleMax;
short fmax;					 /* data in this element */
struct Node *next; /* pointer to next element */
};
void  mod_cal(struct Node *start);
void bubbleSort(struct Node *start);
void swap(struct Node *a, struct Node *b);
void insertAtTheBegin(struct Node **start_ref, Uint32 ModuleMaxi) ;


main(){
	comm_poll();
	struct Node *start = NULL;

		for(t = 0 ; t< 960; t++){
			while(detec_Pulse()){
				insertAtTheBegin(&start, start->ModuleMax);
			   	mod_cal(start);
  				bubbleSort(start);
  				Fx = start->fmax;
  				output_sample(TablePulse[Fx][t]);
  			}}
		for (t=0 ; t<(48000 - 960); t++) output_sample(0);
  		}
int detec_Pulse() {
			for( i=0 ; i < N; i++){
				XnBuffer[i] = 0;
				YnBuffer[i] = 0;
			}
			IntgC = 0;
			DetectionPulse = 0; t=0;

				Xn = input_sample(); t++;
				XnBuffer[0] = Xn;
				Yn =0;

				for ( i =N-1; i>=0;i--)
					{
					    Yn= Yn + (int)(XnBuffer[i] * h[i]) >> k;
					    XnBuffer[i+1] = XnBuffer[i];
					}
                IntgC = IntgC + (short) ((abs(Yn) - IntgC) >> RC);

                YnBuffer[j] = (short) IntgC;
                j = (j +1) % N;
				if(IntgC > SEUIL_Detection) {
					DetectionPulse = 1;
					return DetectionPulse;
				}

			}
void  mod_cal(struct Node *start) {

		for(f =0; f<8;f++){
					Qn_1[f]= Qn_2[2] = 0;
				}
				for(i = 0;i<96;i++){
					Xn = input_sample();
					for(f = 0; f<8; f++){
						tmp1 = Coeff[f]*Qn_1[f];                                 // Q14*Q8 =Q22
						tmp1 = tmp1 + (int)(Xn << 7);                            // Q22 * Q15 << 7 = Q22
						tmp1 = tmp1 - (int)(Qn_2[f] << 14);                      // Q22 + Q8 << 14 = Q22
						Qn_1[f] = (short) (tmp1 >> 14) ;                         // Q22 <<14 = Q8
					    Qn_2[f] = Qn_1[f];
					    Qn_1[f] = Qn[f];

					}


				}
				start->ModuleMax= 0 ;

				for( f=0 ; f<8; f++){
					tmp1 =(int)( Qn_1[f]*Qn_1[f]);                                //Q8 * Q8 =Q8
					tmp1 = tmp1 + (int)(Qn_2[f]*Qn_2[f]) ;                         //Q16 + Q8 * Q8 = Q16
					tmp2 = (int)(Qn_2[f] *Coeff[f] >> 6);                        //Q8 * Q14 >>6 = Q16
					tmp2 = (int)((tmp2 * Qn_1[f]) >>8);                     //Q8 * Q8 >>8 = Q16
 				    tmp1 = tmp1 + tmp2;                              //Q16 +Q16 = Q16
  				    Module[f] =(Uint32)( tmp1 + tmp2) ;
  				    if (Module[f] > start->ModuleMax){
  				    	start->ModuleMax= Module[f];
  				    	start->fmax = f;
  				    }

  				}}
void bubbleSort(struct Node *start)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->ModuleMax > ptr1->next->ModuleMax)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b)
{
    int temp = a->ModuleMax;
    a->ModuleMax = b->ModuleMax;
    b->ModuleMax = temp;
}
void insertAtTheBegin(struct Node **start_ref, Uint32 ModuleMaxi)
{
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node));
    ptr1->ModuleMax = ModuleMaxi;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}
