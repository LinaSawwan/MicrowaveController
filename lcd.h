#include "delay.h"
#include "stdint.h"

#define HIGH   1
#define LOW    0

#define RS 0x02
#define RW 0x04
#define EN 0x08

#define Clear		             0x01         
#define Home             		 0x02          
#define EntryMode            0x06          
#define DisplayOff           0x08 
#define shiftDisplayRight    0x1C
#define shiftDisplayLeft     0x18
#define DisplayOn            0x0F 
#define cursorOff            0x0C
#define cursorOn             0x0E
#define Reset                0x30          
#define Set8bitFunction      0x38          
#define FirstRow             0x80                   
#define SecondRow            0xC0  

void LCD_cmd(unsigned char cmd);
void LCD_char(unsigned char data);
void PortB_Init(void);
void PortE_Init (void);
void LCD_Init(void);
void LCD_write_string(char  *s);
void LCD_VCLRScreen(void);
void LCD_goto_position(unsigned char  x,unsigned char  y);
