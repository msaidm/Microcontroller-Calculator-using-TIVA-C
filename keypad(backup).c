#include "keypad.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "LCD.h"

int mode = 0;
int size = 0; 
int KeyPadIndex = 0; 

char array[17]; // Array that will be send to the calc fuction
char tempAns[17] ; // Array of the prv Answer 
char * resultFinal ; // Array that will be retruned by the calc function

 
bool isDisplaying = false; 
bool hashIsPressed = false; 
bool isEqualPressed = false; 
bool clicked[16] = false ; 

int getIndex(int i , int j )
{
  return 4*i+j-1 ; 
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

char* Readkeypad()
{
  
  char temp [17] = {'\0'} ; // Array of the pressed key that will be displayed on the LCD
  int tempIndex = 0 ;  
  GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
  
  
  for(int i= 0 ; i<4;i++)
  {
    GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_INT_PIN_4<<i,GPIO_INT_PIN_4<<i );
    for(int j  = 1 ; j<5;j++)
    {
      if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
      {
         Delay() ;   
         
        if(i==0 && !clicked[getIndex(i,1)] ) // The + sign 
         {
           
           printf("%c\n",'+') ; 
           array[KeyPadIndex] = '+' ; 
           if(!isEqualPressed){
           temp[tempIndex] = '+' ;  
           KeyPadIndex++ ;
           mode = 0 ; 
           }
           clicked[getIndex(i,1)] = true  ;  
          }
       
        else if(i==1 && !clicked[getIndex(i,2)] ) // The - sign 
        { 
          printf("%c\n",'-') ; 
          array[KeyPadIndex] = '-' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '-' ; 
          KeyPadIndex++ ;
          mode = 0 ; 
          }
          
          clicked[getIndex(i,2)] = true  ; 
        } 
       
        else if(i==2 && !clicked[getIndex(i,3)] ) // The x sign 
        { 
          printf("%c\n",'x') ;
          clicked[getIndex(i,3)] = true  ; 
          array[KeyPadIndex] = 'x' ;
          if(!isEqualPressed)
          {
            temp[tempIndex] = 'x' ; 
            KeyPadIndex++ ;
            mode = 0 ; 
            
          }
        }
       
        else if(i==3 && !clicked[getIndex(i,4)] ) // when Equal is pressed = 
        { 
          printf("%c\n",'=') ;
          clicked[getIndex(i,4)] = true  ; 
          temp[tempIndex] = '=' ; 
          isEqualPressed = true ; 
          mode = 1;
          array[KeyPadIndex] = '\0' ;
          resultFinal = calculate(array);
          for(int i = 0 ; i<strlen(resultFinal);i++)
          {
            tempAns[i] = resultFinal[i] ; 
          }
          KeyPadIndex = 0 ; 
          
          
          return resultFinal ;         
        }  
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1)==GPIO_INT_PIN_1) // 1 is pressed
      {
         mode = 0 ; 
          Delay() ; 
         if(i==0 && !clicked[getIndex(i,1)] )
         {
           printf("%c\n",'1') ; 
           array[KeyPadIndex] = '1' ;
           if(!isEqualPressed){
           temp[tempIndex] = '1' ; 
           KeyPadIndex++ ;
           }
           clicked[getIndex(i,1)] = true  ; 
            
          }
         
        else if(i==1 && !clicked[getIndex(i,2)] ) // 4 is pressed
        { 
          printf("%c",'4') ; 
          clicked[getIndex(i,2)] = true  ; 
          array[KeyPadIndex] = '4' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '4' ; 
          KeyPadIndex++ ;
          }
          
        } 
             
        else if(i==2 && !clicked[getIndex(i,3)] ) // 7is pressed
        { 
          printf("%c",'7') ; 
          
          array[KeyPadIndex] = '7' ;
          if(!isEqualPressed){
          temp[tempIndex] = '7' ; 
          KeyPadIndex++ ;
          }
          clicked[getIndex(i,3)] = true;          
        }
        
        else if(i==3 && !clicked[getIndex(i,4)] ) // star is pressed *
        {            
          printf("%c\n",'*') ; 
          clicked[getIndex(i,4)] = true; 
          KeyPadIndex = 0 ; 
          result = 0 ; 
          answer = 0 ; 
          op1=0 ; 
          op2 = 0 ; 
          index = 0 ; 
          tempIndex = 0 ; 
          
          for (int i = 0 ; i <strlen(temp);i++)
          {
             temp[i] = '\0' ;     
          }
          for (int i = 0 ; i <strlen(array);i++)
          {
             array[i] = '\0' ; 
          }
         
           for (int i = 0 ; i <strlen(final);i++)
          {
             final[i] = '\0' ; 
            
          }
          for(int i = 0 ;i<strlen(resultFinal) ; i++  )
          {
            resultFinal[i] = '\0' ; 
          } 
          
          for(int i = 0 ;i<strlen(resultFinal) ; i++  )
          {
            tempAns[i] = '\0' ; 
          }
          
          KeyPadIndex = 0 ; 
          result = 0 ; 
          answer = 0 ; 
          op1=0 ; 
          op2 = 0 ; 
          index = 0 ; 
          LCD_Command(LcdClear);
          LCD_Command(0x80);
          isEqualPressed = false ; 
        }     
      }

      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_2)==GPIO_INT_PIN_2) // 2 is pressed
      {
         mode = 0 ; 
        if(i==0 && !clicked[getIndex(i,1)])
         {
           printf("%c\n",'2') ;
           clicked[getIndex(i,1)] = true  ;
           array[KeyPadIndex] = '2' ; 
           
           if(!isEqualPressed){
           temp[tempIndex] = '2' ; 
           KeyPadIndex++ ;
           }
           
          
          }
        else if(i==1 && !clicked[getIndex(i,2)]) // 5 is pressed
        { 
          printf("%c\n",'5') ; 
          clicked[getIndex(i,2)] = true  ; 
          array[KeyPadIndex] = '5' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '5' ; 
          KeyPadIndex++ ;
          }
          
          
        } 
        else if(i==2 && !clicked[getIndex(i,3)] ) // 8 is pressed
        { 
          printf("%c\n",'8') ; 
          clicked[getIndex(i,3)] = true  ; 
          array[KeyPadIndex] = '8' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '8' ; 
          KeyPadIndex++ ;
          }
          
        }
        else if(i==3 && !clicked[getIndex(i,4)] ) // 0is pressed
        { 
          printf("%c\n",'0') ; 
          clicked[getIndex(i,4)] = true  ; 
          array[KeyPadIndex] = '0' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '0' ; 
          KeyPadIndex++ ;
          }
         
         
        }
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_3)==GPIO_INT_PIN_3) // 3 is pressed
      {
         mode = 0 ; 
          Delay() ; 
        if(i==0 && !clicked[getIndex(i,1)])
         {
           printf("%c\n",'3') ; 
           clicked[getIndex(i,1)] = true ; 
           array[KeyPadIndex] = '3' ; 
           if(!isEqualPressed){
           temp[tempIndex] = '3' ; 
           KeyPadIndex++ ;
           }
         
          
           
          }
       
        else if(i==1  && !clicked[getIndex(i,2)]) // 6 is pressed
        { 
          printf("%c\n",'6') ; 
          clicked[getIndex(i,2)] = true ; 
          array[KeyPadIndex] = '6' ; 
          if(!isEqualPressed){
          temp[tempIndex] = '6' ; 
          KeyPadIndex++ ;
          }
         
          
        } 
        
        else if(i==2 && !clicked[getIndex(i,3)] ) // 9 is pressed
        { 
          printf("%c\n",'9') ; 
          clicked[getIndex(i,3)] = true ; 
          array[KeyPadIndex] = '9' ;
          if(!isEqualPressed){
          temp[tempIndex] = '9' ; 
          KeyPadIndex++ ;
          }
          
         
        }
       
        else if(i==3  && !clicked[getIndex(i,4)] ) // # is pressed
        { 
          printf("%c\n",'#') ; 
          clicked[getIndex(i,4)] = true ; 
          temp[0]='A';
          temp[1]='N';
          temp[2]='S';
          
          for(i = 0 ; i<strlen(tempAns) ;i++)
          { 
            array[i]= tempAns[i] ; 
          }
          KeyPadIndex = strlen(tempAns)  ; 
          LCD_Command(LcdClear);
          LCD_Command(0x80);
          isEqualPressed = false ; 
        }  
        
        
      
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_4)==0)
      {
        if(i==0 && clicked[getIndex(i,1)])
        {
          clicked[getIndex(i,1)] = false ; 
        }
       else if(i==1 && clicked[getIndex(i,2)])
        {
          clicked[getIndex(i,2)] = false ; 
        }
         else if(i==2 && clicked[getIndex(i,3)])
        {
          clicked[getIndex(i,3)] = false ; 
        }
         else if(i==3 && clicked[getIndex(i,4)])
        {
          clicked[getIndex(i,4)] = false ; 
        }
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1)==0)
      {
         if(i==0 && clicked[getIndex(i,1)])
        {
          clicked[getIndex(i,1)] = false ; 
        }
       else if(i==1 && clicked[getIndex(i,2)])
        {
          clicked[getIndex(i,2)] = false ; 
        }
         else if(i==2 && clicked[getIndex(i,3)])
        {
          clicked[getIndex(i,3)] = false ; 
        }
         else if(i==3 && clicked[getIndex(i,4)])
        {
          clicked[getIndex(i,4)] = false ; 
        }
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_2)==0)
      {
         if(i==0 && clicked[getIndex(i,1)])
        {
          clicked[getIndex(i,1)] = false ; 
        }
       else if(i==1 && clicked[getIndex(i,2)])
        {
          clicked[getIndex(i,2)] = false ; 
        }
         else if(i==2 && clicked[getIndex(i,3)])
        {
          clicked[getIndex(i,3)] = false ; 
        }
         else if(i==3 && clicked[getIndex(i,4)])
        {
          clicked[getIndex(i,4)] = false ; 
        }
      }
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_3)==0)
      {
         if(i==0 && clicked[getIndex(i,1)])
        {
          clicked[getIndex(i,1)] = false ; 
        }
       else if(i==1 && clicked[getIndex(i,2)])
        {
          clicked[getIndex(i,2)] = false ; 
        }
         else if(i==2 && clicked[getIndex(i,3)])
        {
          clicked[getIndex(i,3)] = false ; 
        }
         else if(i==3 && clicked[getIndex(i,4)])
        {
          clicked[getIndex(i,4)] = false ; 
        }
      }
      
      }
      
  }
  return &temp[0] ; 
} 
void Delay()
{
  int count=0 ; 
  while(count<199000)
  {count++;}
}



