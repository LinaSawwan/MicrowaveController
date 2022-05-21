#include "delay.h"

/* Micro seconds delay function */
void delay_us(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
}	

void SysTick_wait( unsigned long delay){
NVIC_ST_CTRL_R =0;
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R =0;
NVIC_ST_CTRL_R =0x00000005;
while((NVIC_ST_CTRL_R & 0X00010000)==0){};
}

void delay_ms(unsigned long delay){
 unsigned long i;
 for(i=0;i<delay;i++){
 SysTick_wait(16000);
 }
}

void delay_s (unsigned long delay){
	unsigned long i;
	for(i=0;i<delay;i++){
	SysTick_wait(16000000);
  }
}