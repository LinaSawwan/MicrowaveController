#include "tm4c123gh6pm.h"
#include "delay.h"

/* Defines the size of rows and columns of keypad */
#define  RowsSize  4
#define  ColsSize  4

																						
																								
void keypad_Init(void);
unsigned char keypad_getkey(void);
