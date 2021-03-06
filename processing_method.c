#include "stm32f7xx.h"                  // Device header

int main(void)
{
    int INPUT, portA, portF, OUTPUT;

    //Activate GPIOA, GPIOF, GPIOI, GPIOC
    RCC->AHB1ENR |= (1 << 0) | (1 << 5) | (1 << 8) | (1 << 2);

    //Define PC7-PC6-PI3-PI2-PI1-PI0 as outputs
    GPIOC->MODER |= (1 << 14) | (1 << 12);
    GPIOI->MODER |= (1 << 6) | (1 << 4) | (1 << 2) | (1 << 0);

    //Define PA15 as an input, all other GPIO's are inputs after reset
    GPIOA->MODER &= ~((unsigned int)1 << 31);
    
	int i = 0;
    while(1){
		i++;
		if(i >= 1000000){
			i = 0;
		}
        portA = GPIOA->IDR;
        portF = GPIOF->IDR;

        //SWITCHi = bit i on INPUT
		//Input is generated the same way as in class exercise
        INPUT = (portA & (1 << 0)) | ((portA & (1 << 8)) >> 7) | ((portA & (1 << 15)) >> 13)
                                                                  | ((portF & 0x7C0) >> 3);
        OUTPUT = 0;
        
        /*
         Write bits of output register based on the equations
        */
        //LED0 = S0.S1.S2.S3+S5.S6+/S7
        if((INPUT & 0x0F)==0x0F){
          OUTPUT |= (1 << 0);
        }
        else if((INPUT & 0x60)==0x60){
          OUTPUT |= (1 << 0);
        }
		else if(!(INPUT & 0x80)){
			OUTPUT |= (1 << 0);
		}
        //LED1 = S0.S6./S7+S4./S5.S6
        if((INPUT & 0xC1) == 0x41){
          OUTPUT |= (1 << 1);
        }
		else if((INPUT & 0x60)==0x40){
			OUTPUT |= (1 << 1);
		}
		//LED2 = S1.S2.S3.S4+/S6./S7
		if((INPUT & 0x1E) == 0x1E){
			OUTPUT |= (1 << 2);
		}
		else if(!((INPUT & 0xC0) == 0xC0)){
			OUTPUT |= (1 << 2);
		}
		//LED3 = S2./S4.S6+S0./S7+S4.S5
		if((INPUT & 0x54) == 0x44){
			OUTPUT |= (1 << 3);
		}
		else if((INPUT & 0x81) == 0x01){
			OUTPUT |= (1 << 3);
		}
		else if((INPUT & 0x30) == 0x30){
			OUTPUT |= (1 << 3);
		}
		//LED4 = S1.S3+S5.S6
		if((INPUT & 0x0A) == 0x0A){
			OUTPUT |= (1 << 4);
		}
        else if((INPUT & 0x60) == 0x60){
			OUTPUT |= (1 << 4);
		}
		//LED5 = S0.S1
		if((INPUT & 0x03) == 0x03){
			OUTPUT |= (1 << 5);
		}
        /*
         Actually turn on LEDs
        */
        GPIOI->ODR = (GPIOI->ODR & ~0x0F) | (OUTPUT & 0x0F);
		GPIOC->ODR = (GPIOC->ODR & ~0x0F) | ((OUTPUT & 0x30) << 2);
    }
}
