#include "LCD.h"
#include "keypad.h"

int main()
{
  //InitKeypad();
  InitLCD();
  //LCD_Command(DispOn);
  LCD_Command(LcdClear);
  LCD_Data('M');
  
  return 0;
}
