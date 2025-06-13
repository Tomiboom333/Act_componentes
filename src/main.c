#include "stm32f103xb.h"
#include <circ_comb.h>

int main(){
    Circ_Init();
    while(1){
        mux1();
        mux2();
        conta();
        sum();
    }
}