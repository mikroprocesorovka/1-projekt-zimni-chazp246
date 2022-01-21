#include "stm8s.h"
#include "milis.h"
#include <stdio.h>
#include "spse_stm8.h"
#include "uart1.h"
//#include "delay.h"
#define _ISOC99_SOURCE
#define _GNU_SOURCE


//vypnutí alarmu?
#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


//definování pinů na kterých bude připojena baterie
//hlavní GND pin balančního konektoru
#define LIPO_PIN_GND GPIO_PIN_0
#define LIPO_PORT_GND GPIOB
//1. článek
#define LIPO_PIN1 GPIO_PIN_1
#define LIPO_PORT1 GPIOB
//2. článek
#define LIPO_PIN2 GPIO_PIN_2
#define LIPO_PORT2 GPIOB
//3. článek
#define LIPO_PIN3 GPIO_PIN_3
#define LIPO_PORT3 GPIOB
//4. článek
#define LIPO_PIN4 GPIO_PIN_4
#define LIPO_PORT4 GPIOB
//5. článek
#define LIPO_PIN5 GPIO_PIN_5
#define LIPO_PORT5 GPIOB
//6. článek
#define LIPO_PIN6 GPIO_PIN_6
#define LIPO_PORT6 GPIOB


void init_ADC(void){
    //na kanálech 0 - 5 (PB1 - PB 6) vypne výstupní buffer
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL0, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL1, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL2, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL3, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL4, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL5, DISABLE);
    //volba frekvence AD převodníku + CLOCK signálu
    ADC2_PrescalerConfig(ADC2_PRESSEL_FCPU_D4);
    //zarovnání
    ADC2_AlignConfig(ADC2_ALIGN_RIGHT);
    //nastavení multiplexeru ?? co vlastně dělá? nebo v čem je jinej? SPL to má fakt divně vyřešený, se to volá jen jednou i když bych měřil jiný kanál...
    ADC2_Select_Channel(ADC2_CHANNEL_4);
    //samotné zapnutí AD převodníku
    ADC2_Cmd(ENABLE);  
    //menší startup delay pro převodník
    ADC2_Startup_Wait();  
}




void setup(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //Nastavení prescaleru
    init_milis(); //inicializuje knihovnu milis
    init_uart1(); //inicializuje VESTAVĚNÝ uart1
    init_ADC(); //inicializace ADC
}


void all (void){
    GPIO_Init(LIPO_PORT1, LIPO_PIN1, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT1, LIPO_PIN1);

    clanek1 = ADC_get(ADC2_CHANNEL_1);
    GPIO_Init(LIPO_PORT2, LIPO_PIN2, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT2, LIPO_PIN2);

    GPIO_Init(LIPO_PORT3, LIPO_PIN3, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT3, LIPO_PIN3);

    GPIO_Init(LIPO_PORT4, LIPO_PIN4, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT4, LIPO_PIN4);

    GPIO_Init(LIPO_PORT5, LIPO_PIN5, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT5, LIPO_PIN5);

    GPIO_Init(LIPO_PORT6, LIPO_PIN6, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT6, LIPO_PIN6);

    GPIO_Init(LIPO_PORT_GND, LIPO_PIN_GND, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_WriteLow(LIPO_PORT_GND, LIPO_PIN_GND);
    
    //GPIO_Init(LIPO_PIN7, LIPO_PORT7, GPIO_MODE_IN_FL_NO_IT);
}



int main(void){
    uint32_t time = 0;
    uint16_t rawADC = 0;
    uint32_t napeti = 0;
    uint32_t teplota = 0;
    uint32_t clanek1 = 0;
    uint32_t clanek2 = 0;
    uint32_t clanek3 = 0;
    uint32_t clanek4 = 0;
    uint32_t clanek5 = 0;
    uint32_t clanek6 = 0;
    uint32_t test = 0;


    setup();
    ////////////////dal jsi sem 0 tak to pak nehledej
    while (0) { 

        if (milis() - time > 1000 ) { 
            time = milis();
            rawADC = ADC_get(ADC2_CHANNEL_4);
            napeti = rawADC * (uint32_t)3300 / 1024;
            teplota = (napeti - 0.4) / 0.0195;


            printf("rawADC je %d\r\n", rawADC);
            printf("napeti je %ld\r\n", napeti);
            printf("teplota je %ld\r\n", teplota);
        }

        /*LED_FLIP; */
        /*_delay_ms(333);*/
        /*printf("Funguje to!!!\n");*/
    }
    
    
    while(1){
        if (napeti == 0){
            GPIO_Init(LIPO_PORT_GND, LIPO_PIN_GND, GPIO_MODE_OUT_PP_LOW_SLOW);
            GPIO_WriteLow(LIPO_PORT_GND, LIPO_PIN_GND);
            test = ADC_get(ADC2_CHANNEL_0);
            GPIO_WriteLow(LIPO_PORT_GND, LIPO_PIN_GND);
            napeti = 1;
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
