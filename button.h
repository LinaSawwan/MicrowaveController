#include "tm4c123gh6pm.h"
#define READ_BIT(reg,bit) (reg & (1<<bit))>>bit

void SWs_Init(void);
unsigned char SW1_Read(void);
unsigned char SW2_Read(void);
unsigned char SW3_Read(void);
