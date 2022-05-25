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
enum states{Idle, SetWeight, SetTime, Cooking, PAUSE, DONE, RESET};
int state;
char weight;
unsigned char prog;
unsigned int number_of_seconds;
bool SAME_PROG = true;

void SysInit(void);
bool Is_Program(unsigned char chr);
bool Is_Number(unsigned char chr);
bool Is_ValidWeight (unsigned char chr);
void Error_msg();
void display_numbers(int number_of_seconds);
void EnterTime();
void openDoor();
void pause();
void done();
void reset();

int main(){
	
	SysInit();
	
	while(1){
		
		SAME_PROG=true;
		state = Idle;              //Default State 
		
		while( keypad_getkey() == 0xFF ){
			LCD_write_string("A-Popcorn B-Beef");
	   	LCD_goto_position(1,2);
		  LCD_write_string("C-Chicken D-Else");
		  delay_ms(800);
			LCD_VCLRScreen();
		}		
		
		prog = keypad_getkey();
		delay_s(1);
		
		if(Is_Program(prog)){                       //CHeck if it's A/B/C/D
			
			LCD_VCLRScreen();
			LCD_char(prog);
			delay_s(2);
			LCD_VCLRScreen();
		
			while(SAME_PROG){             //programme loop
				
				switch (state){
					
					case Idle:                               //Idle State
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
					
					
					case SetWeight:                             //SetWeight State
				 
					
					while(keypad_getkey()==0xFF);
					weight=keypad_getkey();     
					if(!Is_ValidWeight(weight)){
						Error_msg();
						
						if (prog == 'B'){
							LCD_write_string("Beef weight?");
						}

						else if (prog == 'C'){
							LCD_write_string("Chicken weight?");
						}
						
						delay_s(2);
						break;
					}
					
					else{
					LCD_VCLRScreen();
					LCD_char(weight);
					LCD_write_string(" Kg");
					delay_s(1);
					if (prog=='B'){
						char w[] = {weight};
						number_of_seconds = atoi(w)*30;
					}
					else if (prog=='C'){
						char w[] = {weight};
						number_of_seconds = atoi(w)*12; 
					 } 
					state=Cooking;
					break;
				 }
					
					case SetTime:                            //SetTime State
						LCD_VCLRScreen();
						EnterTime();
						while(SW2_Read()==1); 
						state = Cooking;
						break;
				  		 
					case Cooking:                             //Cooking State
					
						while(SW2_Read()==1);
						delay_ms(1);
						int exit=0;
						for (int i=number_of_seconds;i>=0;i--){
							 
								if(SW3_Read()==0){              //opened Door state
									state=PAUSE;
									exit=1;
									break;
								}			
							
								if ( SW1_Read() == 0){
									state=PAUSE;
									exit=1;
									break;
								}
							
								else{          //Continue 
										RGB_ON(); 
										delay_s (1);
										display_numbers(number_of_seconds--);
								}
							
					}
					if(exit==1)
							break;
					display_numbers(0);	
					state = DONE;
					break;
					
					case PAUSE:		
						openDoor();
				  pause();
				
					if (SW1_Read() == 0){
					    state=RESET;
							break;
					}
					if (SW3_Read() == 0){
					    state=PAUSE;
							break;
					}
					else{
							state=Cooking;
							break;
					}
					
					case DONE:
						done();
					  
					case RESET:
						reset();
						break;
           
				}
			}
		}
	}
}

void SysInit(){
	keypad_Init();
	LCD_Init();
	RGBLED_Init();
	SWs_Init();
	Buzzer_VInit ();
}

bool Is_Program(unsigned char chr){
	if( (chr=='A')||(chr=='B')||(chr=='C')||(chr=='D')){
		return true;}
	else return false;
}

bool Is_Number(unsigned char chr){
	if( chr<48 | chr>57)
		return false;
	else return true;
}
bool Is_ValidWeight (unsigned char chr){
 if (Is_Number(chr)&(chr!='0'))
	 return true;
 else
	 return false;
}

void Error_msg(){
	LCD_VCLRScreen();
	RGB_OFF();
	RED_ON();
	LCD_write_string("ERR");
	delay_s(2);
	LCD_VCLRScreen();
	RED_OFF();
}

void display_numbers(int number_of_seconds) {
	int number_of_minutes =  number_of_seconds/60;
	int number_of_seconds_reminder = ( number_of_seconds - number_of_minutes * 60) ;
	LCD_VCLRScreen();  
	char min[2];
	char sec[2];
	sprintf(min, "%d" ,number_of_minutes);
 
	if(number_of_minutes<10)
		LCD_write_string("0"); 
	 
  LCD_write_string(min); 
  LCD_char(':');

  if(number_of_seconds_reminder<10)
    LCD_write_string("0"); 

	sprintf(sec, "%d" ,number_of_seconds_reminder ); 
	LCD_write_string(sec);
  }


void EnterTime(){
	unsigned char nb='0';
	char display[5]={'0','0',':','0','0'};
	number_of_seconds = 0;
  LCD_VCLRScreen();
	LCD_write_string (display);
	
	while(SW2_Read()==1){
		if (SW1_Read() == 0){
			display[0]='0';
			display[1]='0';
			display[3]='0';
			display[4]='0';
			LCD_VCLRScreen();
			LCD_write_string (display);
			}
		else{
			nb = keypad_getkey();
			if (nb!=0xFF){
				if(Is_Number(nb)){
					display[0]=display[1];
					display[1]=display[3];
					display[3]=display[4];
					display[4]=nb;
					LCD_VCLRScreen();
					LCD_write_string (display);
					delay_ms(500);
				}
				else{
					Error_msg();
					display[0]='0';
					display[1]='0';
					display[3]='0';
					display[4]='0';
					LCD_write_string (display);
				}	
			}
		}
		}
	  LCD_VCLRScreen();
		char min[] = {display[0],display[1]};
		char sec[] = {display[3],display[4]};
    number_of_seconds = atoi(sec) + (60) * atoi(min);
		if ((atoi(sec)>59)||(atoi(min)>29)){
			Error_msg();
			EnterTime();
		}
    
}

void openDoor(){
	while(SW3_Read()==0){         
		RGB_TOGGLE();
		Buzzer_TOGGLE();
		delay_s(1);	
	}
}

void pause(){
Buzzer_OFF();		
	delay_ms(1700);
	while((SW1_Read() == 1)&&(SW2_Read() == 1)&&(SW3_Read() == 1)){
						RGB_TOGGLE();
						delay_s(1);
	}
}
void done(){
	delay_s(1);
	LCD_VCLRScreen();
	LCD_write_string("DONE");
	RGB_OFF();
	for(int i=0;i<6;i++){
	delay_s(1);
	RGB_TOGGLE();
	Buzzer_TOGGLE();
	}

}
void reset(){
	LCD_VCLRScreen();
	RGB_OFF();
	SAME_PROG = false;
}





