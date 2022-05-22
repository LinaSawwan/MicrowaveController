#include "button.h"

void SWs_Init(){                        //sw1&2 in F4,F0 and sw3 in A1
SYSCTL_RCGCGPIO_R |= 0x21;
while ((SYSCTL_PRGPIO_R & 0x21)==0);
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTA_LOCK_R = 0x4C4F434B;

GPIO_PORTF_CR_R |= 0x11;
GPIO_PORTA_CR_R |= 0x04;

GPIO_PORTF_AMSEL_R &= ~0x11;
GPIO_PORTA_AMSEL_R &= ~0x04;

GPIO_PORTF_PCTL_R &= ~0x000F000F;
GPIO_PORTF_PCTL_R &= ~0x00000F00;

GPIO_PORTF_AFSEL_R &= ~0x11;
GPIO_PORTA_AFSEL_R &= ~0x04;

GPIO_PORTF_DIR_R &= ~0x11;
GPIO_PORTA_DIR_R &= ~0x04;

GPIO_PORTF_PUR_R |= 0x11;
GPIO_PORTA_PUR_R |= 0x04;

GPIO_PORTF_DEN_R |= 0x11;
GPIO_PORTA_DEN_R |= 0x04;
}


unsigned char SW2_Read(){
  return ((GPIO_PORTF_DATA_R & (1<<0))>>0);
}

unsigned char SW1_Read(){
	int n = ((GPIO_PORTF_DATA_R & (1<<4))>>4);
	return n;
}

unsigned char SW3_Read(){
	int n = ((GPIO_PORTA_DATA_R & (1<<2))>>2);
	return n;
}

