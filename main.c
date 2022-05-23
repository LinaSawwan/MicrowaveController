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

void SysInit(void);
bool Is_Number(unsigned char chr);
bool Is_Programme(unsigned char chr);
void EnterTime();
void display_numbers();
void pause ();
int StartCooking();
void Error_msg();

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
					 
					
					
					 case SetWeight:                             //SetWeight State
				
					while(keypad_getkey()==0xFF);
					weight=keypad_getkey();     
					/*if(check if valid weight(weight)){
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
					*/
					
					case SetTime:                            //SetTime State
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

bool Is_Number(unsigned char chr){
	if( chr<48 | chr>57)
		return false;
	else return true;
}

void pause (){                      //pause state
	while((SW1_Read() == 1)&&(SW2_Read() == 1)){
										RGB_TOGGLE();
										delay_s(1);
										
	}
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


bool Is_Programme(unsigned char chr){
	if( (chr=='A')||(chr=='B')||(chr=='C')||(chr=='D')){
		return true;}
	else return false;
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

int StartCooking(){
    
            for (int i=number_of_seconds;i>=0;i--){
							
							if(SW3_Read()==0){
								while(SW3_Read()==0){         //opened Door state
								
									RGB_TOGGLE();
									Buzzer_TOGGLE();
									delay_s(1);	
								} 					                  
								Buzzer_OFF();
								pause();                      //pause state
								if (SW1_Read() == 0){
										//display_numbers(0);
										delay_ms(500);
										LCD_VCLRScreen();
										return 0;
								}
						  }				                        
							
							if ( SW1_Read() == 1){          //Not paused
								RGB_ON(); 
                delay_s (1);
								display_numbers(number_of_seconds--);
							}
							else{
									delay_s(1);
									pause();                    //pause state
									if (SW1_Read() == 0){
										
										delay_ms(500);
										LCD_VCLRScreen();
											return 0;
									}
							}
        }
				return 1;
}
 

void display_numbers() {
int number_of_minutes =  number_of_seconds/60;
int number_of_seconds_reminder = ( number_of_seconds - number_of_minutes * 60) ;
int j;
int i;	
 for(j=number_of_minutes ; j>= 0 ;j--)
    
   { if (number_of_seconds_reminder != 0) 
    { for ( i = number_of_seconds_reminder ; i> 0 ; i--) 
   {    
		     char min[2]={0,0};
		     char sec1[2]={0,0};
		     sprintf(min, "%d" ,number_of_minutes);
         LCD_write_string(min); 
         LCD_char(':');
		     sprintf(sec1, "%d" ,number_of_seconds_reminder ); 
         LCD_write_string(sec1);
         delay_s(1);
         number_of_seconds_reminder--;
		     LCD_VCLRScreen();
                } 
         char min[2]={0,0};
				 sprintf(min, "%d" ,number_of_minutes);			
         LCD_write_string(min);
         LCD_write_string(":");
         LCD_write_string("00");
			    delay_s(1);					
         number_of_minutes--;
						LCD_VCLRScreen();;
       }
                      
    else  {  
           for ( i = 59 ;i>= 0 ; i--)
        {	char min[2]={0,0};
		     char sec[2]={0,0};
		       sprintf(min, "%d" ,number_of_minutes);
           LCD_write_string(min); 
           LCD_char(':');
		       sprintf(sec, "%d" ,i); 
           LCD_write_string(sec);	
           delay_s(1);
				   LCD_VCLRScreen();}
           number_of_minutes--;
					
      }
 }  
}
