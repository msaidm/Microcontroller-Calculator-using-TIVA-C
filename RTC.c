#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"
#include "RTC.h"
#include "LCD.h"
#include "parser.h"

uint32_t Years = 2019;

void InitRTC(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE)){}
	HibernateEnableExpClk(SysCtlClockGet());
	HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE);  
	HibernateCounterMode(HIBERNATE_COUNTER_RTC);
	HibernateRTCEnable();
	HibernateRTCSet(DefaultDate);
}

void DisplayClock(void)
{
	uint32_t timeInSeconds = HibernateRTCGet();
	DisplaySeconds(timeInSeconds);
	DisplayMinutes(timeInSeconds);
	DisplayHours(timeInSeconds);
	DisplayDays(timeInSeconds);
	DisplayMonths(timeInSeconds);
        DisplayYears(timeInSeconds);
}

void DisplaySeconds(uint32_t timeInSeconds)
{
	uint32_t Seconds = (timeInSeconds)%60;
	parseToCharArray(Seconds);
        if(Seconds < 10)
	{
		Display("0", 1, 6);
		Display(final,1, 7);	
	}
	else
		Display(final, 1, 6);
}

void DisplayMinutes(uint32_t timeInSeconds)
{
	uint32_t Minutes = (timeInSeconds/SecondsInMinute)%60;
	parseToCharArray(Minutes);
        if(Minutes < 10)
	{
		Display("0", 1, 3);
		Display(final,1, 4);	
	}
	else
		Display(final, 1, 3);

	Display(":",1, 5); 
}

void DisplayHours(uint32_t timeInSeconds)
{
	uint32_t Hours = (timeInSeconds/SecondsInHour)%24;
	 parseToCharArray(Hours);
        if(Hours < 10)
	{
		Display("0", 1, 0);
		Display(final,1, 1);	
	}
	else
		Display(final, 1, 0);

	Display(":",1, 2);
}

void DisplayDays(uint32_t timeInSeconds)
{
	uint32_t Days = 1+((timeInSeconds/SecondsInDay)%31);
	parseToCharArray(Days);
	if(Days < 10)         
	{
		Display("0", 0, 0);
		Display(final,0, 1);	
	}
	else
		Display(final, 0, 0);
	
	Display("/",0, 2);
}

void DisplayMonths(uint32_t timeInSeconds)
{
	uint32_t Months = 1+((timeInSeconds/SecondsInMonth)%12);
	parseToCharArray(Months);
        if(Months < 10)
	{
		Display("0", 0,3);
		Display(final,0, 4);	
	}
	else
		Display(final, 0, 3);
        
	Display("/",0, 5);
}

void DisplayYears(uint32_t timeInSeconds)
{
	if(timeInSeconds%SecondsInYear == 0)
		Years++;
	
        parseToCharArray(Years);
	Display(final, 0, 6);
}