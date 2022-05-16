#include "tm4c123gh6pm.h"
#include "led.h"
#include "lcd.h"
#include "delay.h"
#include "keypad.h"

//Testing keypad
int main(){               
	RGBLED_Init();
	LCD_Init();
	keypad_Init();
	
	RGB_ON();
	while(1){
		while(keypad_getkey()==0xFF);
		unsigned char c = keypad_getkey();
		LCD_char(c);
		delay_s(2);
		LCD_VCLRScreen();
	
	}
	
	
}
