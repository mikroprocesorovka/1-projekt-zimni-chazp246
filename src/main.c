#include "stm8s.h"
#include "milis.h"
#include <stdio.h>
#include "spse_stm8.h"
#include "uart1.h"
#include "delay.h"
#define _ISOC99_SOURCE
#define _GNU_SOURCE


#define LD1_PORT GPIOB
#define LD1_PIN GPIO_PIN_1
#define LD1_TRG (GPIO_ReadInputPin(LD1_PORT, LD1_PIN)!=RESET) 

#define LD2_PORT GPIOB
#define LD2_PIN  GPIO_PIN_2
#define LD2_TRG (GPIO_ReadInputPin(LD2_PORT, LD2_PIN)!=RESET) 


void setup(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //Nastavení prescaleru
    init_milis(); //inicializuje knihovnu milis
    init_uart1();
   
   /* GPIO_Init(LIPO_PORT5, LIPO_PIN5, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT5, LIPO_PIN5);
    printf("clanek6 je %ld\r\n", clanek6);*/
}
    



    





int main(void){
    setup(); //spustí funkci setup>>> ta zinicialuzuje další funkce
    uint32_t first = 0;
    uint32_t second = 0;
    uint32_t speed;
    while (1){
        if(LD1_TRG){
            first = milis();
        }
        if(LD2_TRG){
            second = milis();
        }
        
        speed = 1000 / (second-first);
    
        printf("rychlost: %ld\r\n", speed);
        


        }
    }
    



/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
