#include "keypad.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "LCD.h"
#include "Menu.h"
#include "RTC.h"
#include "ContactList.h"

uint8_t Module = 0;
void (*CurrentModule)(void);

void MenuInit(void)
{
	InitLCD();
	InitRTC();
	InitKeypad();	
        InitContactList();
	CurrentModule = RTCModule;
}

void RunCurrentModule(void)
{
	(*CurrentModule)();
}

void RTCModule(void)
{
	DisplayClock();
	Readkeypad();
}

void CalculatorModule(void)
{
	Readkeypad();
}

void ListModule(void)
{
	Readkeypad();
}

void SwitchModule(void)
{
	Module = (Module+1)%Max_Modules;
	
	switch(Module)
	{
		case RTC:
			ClearDisplay();
			CurrentModule = RTCModule;
			break;
			
		case Calculator:
			ClearDisplay();
			CurrentModule = CalculatorModule;
			break;
		
		case List:
			ClearDisplay();
                        New();
			CurrentModule = ListModule;
			break;
			
		default:
			break;
	}
}