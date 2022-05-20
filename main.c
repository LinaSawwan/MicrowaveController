// Including drivers
#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "lcd.h"
#include "keypad.h"

// Including C libraries
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>

// Global variables
enum states{Idle, Cooking, SetWeight, SetTime};
int state;
unsigned char prog;
unsigned int number_of_seconds;
char weight;
bool SAME_PROG = true;

void SysInit(){
	keypad_Init();
	LCD_Init();
	RGBLED_Init();
	SWs_Init();
	Buzzer_VInit ();
}

int main(){
	
	SysInit();
	
	while(1){
		
		SAME_PROG=true;
		state = Idle;
		LCD_write_string("A-Popcorn B-Beef");
		LCD_goto_position(1,2);
		LCD_write_string("C-Chicken D-Else");
		delay_s(2);
		LCD_VCLRScreen();
		
		while( keypad_getkey() == 0xFF );
		prog = keypad_getkey();
		
		if(true){                       //CHeck if it's A/B/C/D
			
			LCD_VCLRScreen();
			LCD_char(prog);
			delay_s(2);
			LCD_VCLRScreen();
		
			while(SAME_PROG){             //programme loop
				
				switch (state){
					
					case Idle:                //Idle State
						if(prog=='A'){ 						             //Popcorn programme
						
					  LCD_write_string("Popcorn");
						number_of_seconds=60;
						state = Cooking ;
						break;
					}
			
					else  if(prog =='B'){ 			             //Beef programme
						LCD_write_string("Beef Weight?");
						delay_s(2);
						state=SetWeight; 
						break;
					}
		 
					else if(prog =='C'){ 			               //Chicken programme
						LCD_write_string("Chicken Weight?");
						delay_s(2);
						state=SetWeight; 
						break;
					}


					else if(prog =='D'){				            //Set Time programme
						LCD_write_string("Cooking Time?");
						delay_s(2);
						state=SetTime;
						break;
					 }

					 
					 
					case Cooking:                             //Cooking State
						break;
					 
					
					
					case SetWeight:                          //SetWeight State
						break;
					
					
					
					case SetTime:                            //SetTime State
						break;
				
				
				}
			}
		}
	}
}
