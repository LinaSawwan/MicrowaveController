#include "tm4c123gh6pm.h"
#include "led.h"
<<<<<<< HEAD
=======
#include "lcd.h"
#include "delay.h"
#include "keypad.h"
>>>>>>> 6c902248c0df214cb4daa0ee892ff50c1faec12a

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
