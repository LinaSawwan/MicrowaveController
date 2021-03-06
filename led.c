#include "led.h "


void RGBLED_Init(){
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTF_DIR_R |= 0x0E;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTF_DATA_R &= ~0x0E;
}

void RGB_OFF(){
	GPIO_PORTF_DATA_R &= ~0x0E;
}

void RGB_ON(){
	GPIO_PORTF_DATA_R |= 0x0E;
}

void RGB_TOGGLE(){
	GPIO_PORTF_DATA_R ^= 0x0E;
}

void RED_OFF(){
	GPIO_PORTF_DATA_R &= ~0x02;
}

void RED_ON(){
	GPIO_PORTF_DATA_R |= 0x02;
}



