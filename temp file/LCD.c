#include "LCD.h"

void InitLCD(void){
  //Enable Port B
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
  
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  //Enable Port A
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }
  
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
}

void LCD_Command(uint8_t command){
  GPIOPinWrite(GPIO_PORTB_BASE, 0xFF, 0);   
  GPIOPinWrite(GPIO_PORTB_BASE, command , command);
  GPIOPinWrite(GPIO_PORTA_BASE, 0xFF, 0);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
  for(int i=0;i<1000000;i++){}
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
  //GPIOPinWrite(GPIO_PORTB_BASE, 0x0C , 0x0C);
  for(int i=0;i<1000000;i++){}
}
void LCD_Data(char* data1, int mode){
  if(mode == 0 )
  {
  if(data1 == '\0')
    return;
  
  uint8_t data = (uint8_t)*data1;
  GPIOPinWrite(GPIO_PORTB_BASE, 0xFF, 0);
  GPIOPinWrite(GPIO_PORTB_BASE, data, data);
  GPIOPinWrite(GPIO_PORTA_BASE, 0xFF, 0);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_4, GPIO_PIN_2|GPIO_PIN_4);
  for(int i=0;i<1000000;i++){}
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
  for(int i=0;i<1000000;i++){}
  //LCD_Command(IncCursor);
  }
  
  if(mode ==1)
  {
    uint8_t result = (uint8_t)data1;
  GPIOPinWrite(GPIO_PORTB_BASE, 0xFF, 0);
  GPIOPinWrite(GPIO_PORTB_BASE, result, result);
  GPIOPinWrite(GPIO_PORTA_BASE, 0xFF, 0);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_4, GPIO_PIN_2|GPIO_PIN_4);
  for(int i=0;i<1000000;i++){}
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
  for(int i=0;i<1000000;i++){}
  //LCD_Command(IncCursor);
  }
}
