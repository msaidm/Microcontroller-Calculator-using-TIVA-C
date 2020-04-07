#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <stdio.h>

extern int mode; 

void InitKeypad(void);

char Readkeypad(void) ; 
void Delay(void) ; 