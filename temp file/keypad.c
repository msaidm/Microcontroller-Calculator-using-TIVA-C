#include "keypad.h"
#include <string.h>
#include <stdio.h>

int mode = 0;

void InitKeypad(void){
  //Enable Port D
  //0-3 outputs port D 
  //1-4 input port E  
  
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
  
  GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
}

char* Readkeypad()
{
  char a;
  GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
  char array[17] ; 
  char result[17] ; 
  int index = 0  ; 
  int size = 0 ; 
  //bool clicked[16] ; 
  bool clicked = false ; 
  for(int i= 0 ; i<4;i++)
  {
    GPIOPinWrite(GPIO_PORTC_BASE,0xFF,0 );
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_INT_PIN_4<<i,GPIO_INT_PIN_4<<i );
    for(int j  = 1 ; j<5;j++)
    {
      if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
      {
        
        if(i==0 )
         {
           printf("%c\n",'+') ; 
           a = '+';
           array[index] = '+' ;  
           index++ ;
           mode = 0 ; 
           return &array[index-1] ; 
           
            //clicked = true  ; 
           //Delay() ;
           
            
          }
       
        else if(i==1 )
        { 
          printf("%c\n",'-') ; 
          array[index] = '-' ;  
          index++ ;
           mode = 0 ; 
          return &array[index-1] ; 
          clicked = true  ; 
          //Delay();
        } 
       
        else if(i==2 )
        { 
          printf("%c\n",'x') ;
          clicked = true  ; 
          array[index] = 'x' ;  
          index++ ;
           mode = 0 ; 
          return &array[index-1] ;  
          //Delay();
        }
       
        else if(i==3 )
        { 
          printf("%c\n",'=') ;
          clicked = true  ; 
          index = 0 ; 
          char result[] = pars() ; 
          mode = 1;
          return &result[0] ;  
          //Delay();
          //return array ; 
        }  
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1)==GPIO_INT_PIN_1)
      {
         mode = 0 ; 
        if(i==0 )
         {
           printf("%c\n",'1') ; 
           array[index] = '1' ;  
           index++ ;
           return &array[index-1] ;  
           clicked = true  ; 
            //Delay();
          }
         
        else if(i==1  )
        { 
          printf("%c",'4') ; 
          clicked = true  ; 
          array[index] = '4' ;  
          index++ ;
          return &array[index-1] ; 
          //Delay();
        } 
             
        else if(i==2 )
        { 
          printf("%c",'7') ; 
          clicked = true  ; 
          array[index] = '7' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        }
        
        else if(i==3 )
        { 
          printf("%c\n",'*') ; 
          clicked = true  ; 
          array[index] = '*' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        }     
      }

      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_2)==GPIO_INT_PIN_2)
      {
         mode = 0 ; 
        if(i==0 )
         {
           printf("%c\n",'2') ;
           clicked = true  ;
           array[index] = '2' ;  
           index++ ;
           return &array[index-1] ;
            //Delay();
          }
        else if(i==1 )
        { 
          printf("%c\n",'5') ; 
          clicked = true  ; 
          array[index] = '5' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        } 
        else if(i==2 )
        { 
          printf("%c\n",'8') ; 
          clicked = true  ; 
          array[index] = '8' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        }
        else if(i==3 )
        { 
          printf("%c\n",'0') ; 
          clicked = true  ; 
          array[index] = '0' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        }
      }
      
      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
      {
         mode = 0 ; 
        if(i==0)
         {
           printf("%c\n",'3') ; 
           clicked = true ; 
           array[index] = '3' ;  
          index++ ;
          return &array[index-1] ;
           //Delay();
           
          }
       
        else if(i==1 )
        { 
          printf("%c\n",'6') ; 
          clicked = true ; 
          array[index] = '6' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        } 
        
        else if(i==2 )
        { 
          printf("%c\n",'9') ; 
          clicked = true ; 
          array[index] = '9' ;  
          index++ ;
          return &array[index-1] ;
          //Delay() ; 
        }
       
        else if(i==3  )
        { 
          printf("%c\n",'#') ; 
          clicked = true ; 
          array[index] = '#' ;  
          index++ ;
          return &array[index-1] ;
          //Delay();
        }
      
      }
      
//      if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
//      {
//        
//        if(i==0 )
//         {
//           printf("%c\n",'+') ; 
//           clicked = true  ; 
//           //Delay() ;
//           
//            
//          }
//       
//        else if(i==1 && ~clicked)
//        { 
//          printf("%c\n",'-') ; 
//          clicked = true  ; 
//          //Delay();
//        } 
//       
//        else if(i==2 && ~clicked)
//        { 
//          printf("%c\n",'x') ;
//          clicked = true  ; 
//          //Delay();
//        }
//       
//        else if(i==3 && ~clicked)
//        { 
//          printf("%c\n",'=') ;
//          clicked = true  ; 
//          //Delay();
//          //return array ; 
//        }  
//      }
//      
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1)==GPIO_INT_PIN_1)
//      {
//        if(i==0 && ~clicked)
//         {
//           printf("%c\n",'1') ; 
//           clicked = true  ; 
//            //Delay();
//          }
//         
//        else if(i==1 && ~clicked )
//        { 
//          printf("%c",'4') ; 
//          clicked = true  ; 
//          //Delay();
//        } 
//             
//        else if(i==2 && ~clicked)
//        { 
//          printf("%c",'7') ; 
//          clicked = true  ; 
//          //Delay();
//        }
//        
//        else if(i==3 && ~clicked)
//        { 
//          printf("%c\n",'*') ; 
//          clicked = true  ; 
//          //Delay();
//        }     
//      }
//
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_2)==GPIO_INT_PIN_2)
//      {
//        if(i==0 && ~clicked)
//         {
//           printf("%c\n",'2') ;
//           clicked = true  ;
//            //Delay();
//          }
//        else if(i==1 && ~clicked)
//        { 
//          printf("%c\n",'5') ; 
//          clicked = true  ; 
//          //Delay();
//        } 
//        else if(i==2 && ~clicked)
//        { 
//          printf("%c\n",'8') ; 
//          clicked = true  ; 
//          //Delay();
//        }
//        else if(i==3 && ~clicked)
//        { 
//          printf("%c\n",'0') ; 
//          clicked = true  ; 
//          //Delay();
//        }
//      }
//      
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
//      {
//        if(i==0 && ~clicked)
//         {
//           printf("%c\n",'3') ; 
//           clicked = true ; 
//           //Delay();
//           
//          }
//       
//        else if(i==1 && ~clicked)
//        { 
//          printf("%c\n",'6') ; 
//          clicked = true ; 
//          //Delay();
//        } 
//        
//        else if(i==2 && ~clicked)
//        { 
//          printf("%c\n",'9') ; 
//          clicked = true ; 
//          //Delay() ; 
//        }
//       
//        else if(i==3 && ~clicked)
//        { 
//          printf("%c\n",'#') ; 
//          //clicked = true ; 
//          //Delay();
//        }
//       
//      }
      
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_4)==0)
//       {
//         if(i==0 && clicked==true)
//         {
//           clicked = false ; 
//         }
//        else if(i==1 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==2 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==3 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         
//       }
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_3)==0)
//       {
//          if(i==0 && clicked==true)
//         {
//           clicked = false ; 
//         }
//        else if(i==1 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==2 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==3 && clicked==true)
//         {
//           clicked = false ; 
//         }
//       }
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_2)==0)
//       {
//          if(i==0 && clicked==true)
//         {
//           clicked = false ; 
//         }
//        else if(i==1 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==2 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==3 && clicked==true)
//         {
//           clicked = false ; 
//         }
//       }
//      else if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_INT_PIN_1)==0)
//       {
//          if(i==0 && clicked==true)
//         {
//           clicked = false ; 
//         }
//        else if(i==1 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==2 && clicked==true)
//         {
//           clicked = false ; 
//         }
//         else if(i==3 && clicked==true)
//         {
//           clicked = false ; 
//         }
//       }
    
      
    }
    //GPIOPinWrite(GPIO_PORTD_BASE,0xFF,0 );
  }
} 
void Delay()
{
  int count=0 ; 
  while(count<199000)
  {count++;}
}



