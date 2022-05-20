#include "keypad.h"																		
#include "buzzer.h"											

/* Array of 4x4 to define characters which will be printe on specific key pressed */
unsigned  char symbol[RowsSize][ColsSize] =    {{ '1', '2',  '3', 'A'},      
                                                { '4', '5',  '6', 'B'},      
                                                { '7', '8',  '9', 'C'},      
                                                { '*', '0',  '#', 'D'}};
																								
																								
void keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x09;            //enable clc for port A & D  
  while ((SYSCTL_RCGCGPIO_R&0x09)==0);  //wait for clock to be enabled
  GPIO_PORTA_CR_R  |= 0xF0;             //allow changes to all the bits in port A
  GPIO_PORTD_CR_R  |= 0x0F;             //allow changes to all the bits in port D
  GPIO_PORTA_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTD_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTD_PDR_R |= 0x0F;             //pull down resistor on Raws
  GPIO_PORTA_DEN_R |= 0xF0;             //digital enable pins in port A
  GPIO_PORTD_DEN_R |= 0x0F;             //digital enable pins in port D
	GPIO_PORTA_DATA_R &= 0xF0;
	GPIO_PORTD_DATA_R &= 0x0F;
}

/* keypad_getkey() function returns the value of key pressed by the user by traversing columns
and rows respectivley */
unsigned char keypad_getkey(void)
{
  	
int i,j; 
	
	
for( i = 0; i < 4; i++)           								//columns traverse
    {
      GPIO_PORTA_DATA_R = (1U << (i+4));
      delay_ms(2);
      for( j = 0; j < 4; j++)                     //rows traverse
      {
        if((GPIO_PORTD_DATA_R &0x0F )& (1U << j)){
					  Buzzer_ON ();
						delay_ms(20);
						Buzzer_OFF ();
						GPIO_PORTA_DATA_R &= (~0xF0);
						GPIO_PORTD_DATA_R &= (~0x0F);
						return symbol[j][i];
				}
          
      }
    }
	return 0xFF;	

	}
	
