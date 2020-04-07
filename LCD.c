#include "LCD.h"
#include "Delay.h"
#include <string.h>


void InitLCD(void){
  //Enable Port B
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  //Enable Port A
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}

  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
  LCD_Command(twoLines) ; 
  LCD_Command(LcdClear);
  LCD_Command(DispOn);
}

void LCD_Command(uint8_t command)
{
  GPIOPinWrite(GPIO_PORTB_BASE, Reset, 0);   
  GPIOPinWrite(GPIO_PORTB_BASE, command , command);
  GPIOPinWrite(GPIO_PORTA_BASE, Reset, 0);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
  Delay(2);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
  //GPIOPinWrite(GPIO_PORTB_BASE, 0x0C , 0x0C);
  Delay(2);
}


void ClearDisplay(void)
{
  LCD_Command(LcdClear);
  LCD_Command(firstRow);
}

void Display(char text[], int row, int col)
{
	if(row == 1)
		LCD_Command(secondRow);
	
	else
		LCD_Command(firstRow);
	
	for(int i=0 ; i < col ; i++)
		LCD_Command(shiftCursorRight);
		
	LCD_Data(text);
	
}

void DisplayCharacter(char c)
{
  if(c == '\0')
    return;
  
  uint8_t data = (uint8_t) c;
  GPIOPinWrite(GPIO_PORTB_BASE, Reset, 0);
  GPIOPinWrite(GPIO_PORTB_BASE, data, data);
  GPIOPinWrite(GPIO_PORTA_BASE, Reset, 0);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_4, GPIO_PIN_2|GPIO_PIN_4);
  Delay(2);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
  Delay(2); 
}

void LCD_Data(char* data1)
{
  int n = strlen(data1);

  for(int i=0; i<n ; i++)
    DisplayCharacter(data1[i]);
}