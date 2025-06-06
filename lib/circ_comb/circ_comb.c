#include <circ_comb.h>
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

#define SUM_A0 9 //pa
#define SUM_A1 10 //pa
#define SUM_B0 11 //pa
#define SUM_B1 12 //pa
#define SUM_CY 15 //pa
#define SUM_Z0 12 //pb
#define SUM_Z1 13 //pb
#define SUM_CO 14 //pb

int pinesA[12] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 15}; 
int pinesB[9] = {0, 1, 2, 3, 4, 5, 12, 13, 14};

void Circ_Init(){
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    for (int i=0; i<13; i++){
        if (pinesA[i]<8){
            GPIOA -> CRL &= ~(0xF << (pinesA[i]*4));
            GPIOA -> CRL |= (1 << ((pinesA[i]*4)+2));
        }
        else{
            GPIOA -> CRH &= ~(0xF << ((pinesA[i]%8)*4));
            GPIOA -> CRH |= (1 << (((pinesA[i]%8)*4)+2));
        }
    } 
    for (int i=0; i<10; i++){
        if(pinesB[i]<8){
            GPIOB -> CRL &= ~(0xF << (pinesB[i]*4));
            GPIOB -> CRL |= (1 << (pinesB[i]*4));
        }
        else{
            GPIOB -> CRL &= ~(0xF << ((pinesB[i]%8)*4));
            GPIOB -> CRH |= (1 << ((pinesB[i]%8)*4));
        }
    }
}
void mux1(){
    int pa2 = GPIOA -> IDR & (1 << MUX1_SELENT);
    if(pa2==0){
        int pa0 = GPIOA -> IDR & (1 << MUX1_IN_0);
        if (pa0) GPIOB -> BSRR |= (1 << MUX1_OUT);
        else GPIOB -> BSRR |= (1 << MUX1_OUT+16);
    }
    else{
        int pa1 = GPIOA -> IDR & (1 << MUX1_IN_1);
        if (pa1) GPIOB -> BSRR |= (1 << MUX1_OUT);
        else GPIOB -> BSRR |= (1 << MUX1_OUT+16);
    }
}
void mux2(){
    int pa6 = GPIOA -> IDR & (1 << MUX2_SELENT);
    if(pa6==0){
        int pa4 = GPIOA -> IDR & (1 << MUX2_IN_0);
        if (pa4) GPIOB -> BSRR |= (1 << MUX2_OUT);
        else GPIOB -> BSRR |= (1 << MUX2_OUT+16);
    }
    else{
        int pa5 = GPIOA -> IDR & (1 << MUX2_IN_1);
        if (pa5) GPIOB -> BSRR |= (1 << MUX2_OUT);
        else GPIOB -> BSRR |= (1 << MUX2_OUT+16);
    }
}
int posicion = 0;
void conta(){
    int salidas[4] ={CONT_OUT_0, CONT_OUT_1, CONT_OUT_2, CONT_OUT_3};
    int pa3 = GPIOA -> IDR & (1 << 3);
    if (pa3==1){
        for (int i=0; i<4; i++){
            GPIOB -> BSRR |= (1 << salidas[i]+16);
        }
        if (posicion>3){
            posicion=0;
            GPIOB -> BSRR |= (1 << salidas[posicion]);
            posicion++;
            delay_ms(100);
        }
        else{
            GPIOB -> BSRR |= (1 << salidas[posicion]);
            posicion++;
            delay_ms(100);
        }
        
    }
}
void sum(){
    int pa9 = GPIOA -> IDR & (1 << SUM_A0);
    int pa10 = GPIOA -> IDR & (1 << SUM_A1);
    int pa11 = GPIOA -> IDR & (1 << SUM_B0);
    int pa12 = GPIOA -> IDR & (1 << SUM_B1);
    int pa15 = GPIOA -> IDR & (1 << SUM_CY);
    int cy;
    int A = pa9 + pa11;
    int B = pa10 + pa12;
    //preguntarse por carrys
    int suma = A | (B << 1) | (cy << 2);
}