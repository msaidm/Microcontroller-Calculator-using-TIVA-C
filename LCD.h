#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#define Reset 0xFF
#define LcdClear 0x01
#define Home 0x02
#define IncCursor 0x06
#define DispOn 0x0F
#define DispOn2 0x0E
#define firstRow 0x80
#define secondRow 0xC0
#define shiftCursorRight 0x14
#define shiftCursorLeft 0x10
#define twoLines 0x38

void InitLCD(void);
void LCD_Command(uint8_t command);
void LCD_Data(char* data1);
void DisplayCharacter(char c);
void Display(char text[], int row, int col);
void ClearDisplay(void);


