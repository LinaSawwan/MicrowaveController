#include "lcd.h"

void LCD_cmd(unsigned char cmd){
	GPIO_PORTB_DATA_R=cmd;

	GPIO_PORTE_DATA_R=(LOW<<1)|(LOW<<2)|(HIGH<<3);
	delay_ms(1);
	GPIO_PORTE_DATA_R=(LOW<<1)|(LOW<<2)|(LOW<<3);
	delay_ms(2);
}

void LCD_char(unsigned char data){
		
		GPIO_PORTB_DATA_R=data;

	GPIO_PORTE_DATA_R=(HIGH<<1)|(LOW<<2)|(HIGH<<3);
	delay_us(30);
	GPIO_PORTE_DATA_R=(HIGH<<1)|(LOW<<2)|(LOW<<3);
	delay_us(30);

	return;
}

void PortB_Init()
{ // for LCD Data
	SYSCTL_RCGCGPIO_R |= 0x00000002;
  while ((SYSCTL_PRGPIO_R&0x02) == 0){};
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
  GPIO_PORTB_PUR_R = 0x00;

}

void PortE_Init ()
{ // E1.E2.E3 for LCD control and E4,E5 for UART5
	SYSCTL_RCGCGPIO_R |= 0x00000010;
  while ((SYSCTL_PRGPIO_R&0x10) == 0){};
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R |= 0x0E;
	GPIO_PORTE_DIR_R |= 0x0E;
	GPIO_PORTE_DEN_R |= 0x0E;
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_AFSEL_R &= (~0x0E);
	GPIO_PORTE_PCTL_R = 0x00000000;
  GPIO_PORTE_PUR_R = 0x00;
}

void LCD_Init(){
	PortB_Init();
	PortE_Init();
	LCD_cmd(Set8bitFunction);
	delay_ms(1);

	LCD_cmd(EntryMode);
	delay_ms(1);

	LCD_cmd(DisplayOn);
	delay_ms(1);

	LCD_cmd(Clear);
	delay_ms(2);

	LCD_cmd(Home);
	delay_ms(2);
	
	LCD_cmd(cursorOff);
	delay_ms(2);
}

void LCD_write_string(char  *s)
{ // sends a string to display on the LCD
	int		i=0;
	while(s[i]!='\0')
	{
		LCD_char(s[i]);
		i++;
	}

	return;
}

void LCD_goto_position(unsigned char  x,unsigned char  y)
{ // goes to position (x,y) on the display
	unsigned char  line_no[]={0x80,0xC0};
	LCD_cmd(line_no[y-1] + x - 1);
	delay_ms(2);
}

void LCD_VCLRScreen(){
	LCD_cmd(Clear);
}
