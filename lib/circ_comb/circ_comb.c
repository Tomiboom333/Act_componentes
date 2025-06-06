#include <circ_comb.h>
#include <stdbool.h>
#include <stm32f103xb.h>
#define MUX1_IN_0 0 //pa
#define MUX1_IN_1 1 //pa
#define MUX1_SELENT 2 //pa
#define MUX1_OUT 0 //pb

#define MUX2_IN_0 4 //pa
#define MUX2_IN_1 5 //pa
#define MUX2_SELENT 6 //pa
#define MUX2_OUT 5 //pb

#define CONT_CLK 3 //pa
#define CONT_OUT_0 1 //pb
#define CONT_OUT_1 2 //pb
#define CONT_OUT_2 3 //pb
#define CONT_OUT_3 4 //pb

#define SUM_A_0 9 //pa
#define SUM_A_1 10 //pa
#define SUM_B_0 11 //pa
#define SUM_B_1 12 //pa
#define SUM_CY 15 //pa
#define SUM_Z_0 12 //pb
#define SUM_Z_1 13 //pb
#define SUM_CO 14 //pb


void Circ_Init(){
    int i;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    int pinesA[12] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 15}; 
    int pinesB[9] = {0, 1, 2, 3, 4, 5, 12, 13, 14};
    for (i=0; i<12; i++){
        if (pinesA[i]<8){
            GPIOA -> CRL &= ~(0xF << (pinesA[i]*4));
            GPIOA -> CRL |= (1 << ((pinesA[i]*4)+2));
        }
        else{
            GPIOA -> CRH &= ~(0xF << ((pinesA[i]%8)*4));
            GPIOA -> CRH |= (1 << (((pinesA[i]%8)*4)+2));
        }
    } 
    for (i=0; i<9; i++){
        if(pinesB<8){
            GPIOA -> CRL &= ~(0xF << (pinesB[i]*4));
            GPIOB -> CRL |= (1 << (pinesB[i]*4));
        }
        else{
            GPIOA -> CRL &= ~(0xF << ((pinesB[i]%8)*4));
            GPIOB -> CRH |= (1 << ((pinesB[i]%8)*4));
        }
    }
}
bool mux1(){
    bool pa2 = GPIOA -> IDR |= (1 << 2);
    if(pa2==false){
        
    }
}
