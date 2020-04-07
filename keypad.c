#include "keypad.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "LCD.h"
#include "Menu.h"
#include "Delay.h"
#include "ContactList.h"

int mode = 0;
int size = 0; 
int KeyPadIndex = 0;  
int shiftAmount = 2;
int LCDRow = 0;
int tempIndex = 0 ;  
bool canType = true;
char tempDisplay[17]; // Array of the pressed key that will be displayed on the LCD

char array[17]; // Array that will be send to the calc fuction
char tempAns[17] ; // Array of the prv Answer 
char * resultFinal ; // Array that will be retruned by the calc function
char keypadCharacters[] = {'1','2','3','+','4','5','6','-','7','8','9','x','*','0','#','='};
char Alphanumeric[] = {'0',' ',
                                       '1',
                                       '2','A','B','C',
                                       '3','D','E','F',
                                       '4','G','H','I',
                                       '5','J','K','L',
                                       '6','M','N','O',
                                       '7','P','Q','R','S',
                                       '8','T','U','V',
                                       '9','W','X','Y','Z'}; 

int AlphanumericIndices[] = {0,2,3,7,11,15,19,23,28,32};

bool isDisplaying = false; 
bool hashIsPressed = false; 
bool isEqualPressed = false; 
bool clicked[16] = false ; 

int getIndex(int i , int j )
{
  return 4*i+j; 
}


void InitKeypad(void){
  
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {
    }
  
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
  
  //Enable Port E
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }
  GPIOIntRegister(GPIO_PORTE_BASE, KeyPressedHandler);       // 23mel handler 
 //GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_RISE_EDGE);
  
  GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
}

void KeyPressedHandler()
{
  
}

void HandleRTCInput(int index)
{
	clicked[index] = true;
	
	switch(index)
	{
		case 14:
                        SwitchModule();
			break;
			
		default:
			break;
	}
}

void HandleContactListInput(int index)
{
  clicked[index] = true;
  int alphanumericIndex = 0;
  switch(index)
	{
          case 0:
            if(canType)
            {
              DisplayCharacter('1'); 
              LCD_Command(shiftCursorLeft);
              if(LCDRow == 0)
                Name[shiftAmount-2] = '1';
              
              else
                Telephone[shiftAmount-2] ='1';
            }
          break;
          
        case 1:
          if(canType)
          {
              AlphanumericIndices[2] = AlphanumericIndices[2] + 1;
              if(AlphanumericIndices[2] == 7)
                AlphanumericIndices[2] = 3;
              
              alphanumericIndex = AlphanumericIndices[2];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
          }
          break;
          
          case 2:
            if(canType)
            {
              AlphanumericIndices[3] = AlphanumericIndices[3] + 1;
              if(AlphanumericIndices[3] == 11)
                AlphanumericIndices[3] = 7;
              
              alphanumericIndex = AlphanumericIndices[3];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 3: 
            if(canType)
            {
              shiftAmount++;  
              if(shiftAmount == 16)
              {
                shiftAmount = 2;
                if(LCDRow == 0)
                {
                  LCDRow = 1;
                  LCD_Command(secondRow);
                }
                
                else
                {
                  LCDRow = 0;
                  LCD_Command(firstRow);
                }
                
                  LCD_Command(shiftCursorRight);
                LCD_Command(shiftCursorRight);
              }
              
              else
                LCD_Command(shiftCursorRight); 
            }
          break;
          
          case 4:
            if(canType)
            {
              AlphanumericIndices[4] = AlphanumericIndices[4] + 1;
              if(AlphanumericIndices[4] == 15)
                AlphanumericIndices[4] = 11;
              
              alphanumericIndex = AlphanumericIndices[4];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 5:
            if(canType)
            {
            AlphanumericIndices[5] = AlphanumericIndices[5] + 1;
            if(AlphanumericIndices[5] == 19)
              AlphanumericIndices[5] = 15;
            
            alphanumericIndex = AlphanumericIndices[5];
            DisplayCharacter(Alphanumeric[alphanumericIndex]); 
            LCD_Command(shiftCursorLeft);
            if(LCDRow == 0)
              Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
            
            else
              Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 6:
            if(canType)
            {
            AlphanumericIndices[6] = AlphanumericIndices[6] + 1;
            if(AlphanumericIndices[6] == 23)
              AlphanumericIndices[6] = 19;
            
            alphanumericIndex = AlphanumericIndices[6];
            DisplayCharacter(Alphanumeric[alphanumericIndex]); 
            LCD_Command(shiftCursorLeft); 
            if(LCDRow == 0)
              Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
            
            else
              Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 7: 
            if(canType)
            {
              if(shiftAmount > 2)
              {
                shiftAmount--; 
                LCD_Command(shiftCursorLeft); 
              }
            }
          break;
          
          case 8:
            if(canType)
            {
            AlphanumericIndices[7] = AlphanumericIndices[7] + 1;
            if(AlphanumericIndices[7] == 28)
              AlphanumericIndices[7] = 23;
            
            alphanumericIndex = AlphanumericIndices[7];
            DisplayCharacter(Alphanumeric[alphanumericIndex]); 
            LCD_Command(shiftCursorLeft); 
            if(LCDRow == 0)
              Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
            
            else
              Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 9:
            if(canType)
            {
              AlphanumericIndices[8] = AlphanumericIndices[8] + 1;
              if(AlphanumericIndices[8] == 32)
                AlphanumericIndices[8] = 28;
              
              alphanumericIndex = AlphanumericIndices[8];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
          case 10:
            if(canType)
            {
              AlphanumericIndices[9] = AlphanumericIndices[9] + 1;
              if(AlphanumericIndices[9] == 37)
                AlphanumericIndices[9] = 32;
              
              int alphanumericIndex = AlphanumericIndices[9];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
          break;
          
        case 11:
          Save();
          canType = false;
          break;
        
        case 12:
          New();
          LCDRow = 0;
          shiftAmount = 2;
          canType = true;
          break;
          
          case 13:
            if(canType)
            {
              AlphanumericIndices[0] = AlphanumericIndices[0] + 1;
              if(AlphanumericIndices[0] == 2)
                AlphanumericIndices[0] = 0;
              
              alphanumericIndex = AlphanumericIndices[0];
              DisplayCharacter(Alphanumeric[alphanumericIndex]); 
              LCD_Command(shiftCursorLeft); 
              if(LCDRow == 0)
                Name[shiftAmount-2] =Alphanumeric[alphanumericIndex];
              
              else
                Telephone[shiftAmount-2]= Alphanumeric[alphanumericIndex];
            }
            
          break;
		case 14:
                        canType = true;
                        SwitchModule();
			break;
		
        case 15:
          Load();
          canType = false;
          break;
          
		default:
			break;
	}
}

void HandleCalculatorInput(int index)
{
       
       
       clicked[index] = true;
	
	switch(index)
	{
		case 12:
		  printf("%c\n",'*') ; 
          KeyPadIndex = 0 ; 
          result = 0 ; 
          answer = 0 ; 
          op1=0 ; 
          op2 = 0 ; 
          index = 0 ; 
          tempIndex = 0 ; 
          
          ClearArrays();
          
          KeyPadIndex = 0 ; 
          result = 0 ; 
          answer = 0 ; 
          op1=0 ; 
          op2 = 0 ; 
          index = 0 ; 
          LCD_Command(LcdClear);
          LCD_Command(0x80);
          isEqualPressed = false ; 
		  break;
		  
		case 14:
		 Delay(1000);
			if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1 << 2)==GPIO_INT_PIN_1 << 2)
				SwitchModule();

			
			else
			{
                          
                         
			  tempDisplay[0]='A';
			  tempDisplay[1]='N';
			  tempDisplay[2]='S';
			  
			  for(int i = 0 ; i<strlen(tempAns) ;i++)
			  { 
				array[i]= tempAns[i] ; 
			  }
			  KeyPadIndex = strlen(tempAns)  ; 
			  ClearDisplay();
			  Display(tempDisplay, 0,0);
                          //tempDisplay[tempIndex] = '\0' ;
                          
			  isEqualPressed = false ; 			
			}
		  break;
		  
		case 15:
		  printf("%c\n",'=') ;
         // tempDisplay[tempIndex] = '=' ; 
          isEqualPressed = true ; 
          mode = 1;
          array[KeyPadIndex] = '\0' ;
          
          calculate(array);
          for(int i = 0 ; i<strlen(final);i++)
          {
            tempAns[i] = final[i] ; 
          }
          KeyPadIndex = 0 ; 
          Display(final,1,0);
          break;
          //return resultFinal ; 
		  
		default:
            char pressedCharacter = keypadCharacters[index];
            array[KeyPadIndex] = pressedCharacter ; 
           if(!isEqualPressed)
		   {
           tempDisplay[tempIndex] = pressedCharacter ;  
           KeyPadIndex++ ;
           tempIndex++ ; 
           mode = 0 ; 
           Display(tempDisplay, 0,0);
           }
           clicked[index] = true  ;  
	}
}

void ClearArrays(void)
{
  for (int i = 0 ; i <17;i++)
          {
             tempDisplay[i] = '\0' ;   
          }
          for (int i = 0 ; i <17;i++)
          {
             array[i] = '\0' ; 
          }
         
           for (int i = 0 ; i <17;i++)
          {
             final[i] = '\0' ; 
            
          }
          for(int i = 0 ;i<17 ; i++  )
          {
            resultFinal[i] = '\0' ; 
          } 
          
          for(int i = 0 ;i<17 ; i++  )
          {
            tempAns[i] = '\0' ; 
          }
}

void Readkeypad(void)
{
  GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
  
  
  for(int i= 0 ; i<4;i++)
  {
    GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_INT_PIN_4<<i,GPIO_INT_PIN_4<<i);
    for(int j  = 0 ; j<4;j++)
    {
	  int pressedIndex = getIndex(i,j);
      if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1 << j)==GPIO_INT_PIN_1 << j && !clicked[pressedIndex])
      {
         Delay(150) ;   
         printf("#\n");
		 switch(Module)
		 {
			case Calculator:
				HandleCalculatorInput(pressedIndex);
				break;
				
			case RTC:
				HandleRTCInput(pressedIndex);
				break;
				
			case List:
				HandleContactListInput(pressedIndex);
				break;
		 }  
	  }
       
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1 << j)== 0)
		  clicked[pressedIndex] = false; 
    }      
   }     
  }





