#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <stdio.h>

extern char final[16];

int parseToInt(char arr []);
void calculate(char arr []);
void parseToCharArray(int number);
