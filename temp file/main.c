
#include "keypad.h"
#include "LCD.h"

//void Delay(void);
int main()
{
  InitKeypad();
  InitLCD();
  LCD_Command(LcdClear);
  LCD_Command(DispOn);
  //LCD_Data('+');
  while (1){
    LCD_Data(Readkeypad(), mode);
  }
  return 0;
}

