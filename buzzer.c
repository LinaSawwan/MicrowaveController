#include "buzzer.h"

void Buzzer_VInit () {
SYSCTL_RCGCGPIO_R |= 0x01 ; 
while ((SYSCTL_RCGCGPIO_R & 0x08) ==0) ; 
GPIO_PORTA_LOCK_R = 0x4C4F434B ; 
GPIO_PORTA_CR_R |= 0x08 ; 
GPIO_PORTA_DEN_R |= 0x08 ; 
GPIO_PORTA_DIR_R |= 0x08 ; 
GPIO_PORTA_AFSEL_R &= ~0x08 ; 
GPIO_PORTA_PCTL_R &= ~0x0000F000 ; 
GPIO_PORTA_DATA_R &= ~0x08 ; 
}

void Buzzer_ON (){
GPIO_PORTA_DATA_R |= 0x08 ; 
}


void Buzzer_OFF (){
GPIO_PORTA_DATA_R &= ~0x08 ; 
}

void Buzzer_TOGGLE (){
GPIO_PORTA_DATA_R ^= 0x08 ; 
}
