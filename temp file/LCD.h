#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#define LCD
#define LcdClear 0x01
#define IncCursor 0x06
#define DispOn 0x0F


void InitLCD(void);
void LCD_Command(uint8_t command);
void LCD_Data(char data1,int mode);



