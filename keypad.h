#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <stdio.h>

extern int mode; 
extern int result ; 
extern int answer ; 
extern char final[16];
extern int op1;
extern int op2;
extern int index;
extern int temp ; 
extern bool EquPressed; 

void InitKeypad(void);
void KeyPressedHandler(void);
void KeyReleasedHandler(void);
void HandleRTCInput(int index); 
void HandleContactListInput(int index);
void HandleCalculatorInput(int index);

void Readkeypad(void) ; 
void ClearArrays(void);
