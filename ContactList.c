#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"

#include "ContactList.h"
#include "LCD.h"
#include "Delay.h"

char Name[14];
char Telephone[14];
uint32_t CurrentEEPROMAddress = EEPROMStart;
uint32_t LoadingEEPROMAddress = EEPROMStart;

void InitContactList(void)
{
    uint32_t ui32EEPROMInit;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)){}
  ui32EEPROMInit = EEPROMInit();
  
  if(ui32EEPROMInit != EEPROM_INIT_OK)
    while(1)
    {
      Display("EEPROM Initialization", 0,0);
      Display("failed.", 1,0);
    }
  
  Delay(200);
}

void New(void)
{
  ClearDisplay();
  LCD_Command(DispOn2);
  Display("N:",0,0);
  Display("T:",1,0);
  LCD_Command(Home);
  LCD_Command(shiftCursorRight);
  LCD_Command(shiftCursorRight);
}

void Save(void)
{
  ClearDisplay();
  if(isEmptyContact(Name) || isEmptyContact(Telephone))
  {
    Display("Error", 0, 0);
    Display("Press * or D", 1,0);
    return;
  }
  
  for(int i=0 ; i < 14 ; i++)
  {
    if(Name[i] == '\0')
      Name[i] = ' ';
    
    if(Telephone[i] == '\0')
      Telephone[i] = ' ';
  }
  
  uint32_t Name2[14];
  uint32_t Telephone2[14];
  
  for(int i=0 ; i < 14 ; i++)
  {
    Name2[i] = (uint32_t)Name[i];
    Telephone2[i] = (uint32_t)Telephone[i];
  }
  
  EEPROMProgram(Name2, CurrentEEPROMAddress, sizeof(Name2));
  CurrentEEPROMAddress += sizeof(Name2);
  Delay(100);
  
  EEPROMProgram(Telephone2, CurrentEEPROMAddress, sizeof(Telephone2));
  CurrentEEPROMAddress += sizeof(Telephone2);
  Delay(100);
 
  Display("Contact saved", 0, 0);
  Display("Press * or D", 1, 0); 
}

void Load(void)
{
  if(CurrentEEPROMAddress == EEPROMStart)
  {
    Display("No contacts", 0, 0);
    Display("Press *", 1, 0);
    return;
  }
  
  uint32_t Name2[14];
  uint32_t Telephone2[14];
  
  EEPROMRead(Name2, LoadingEEPROMAddress, sizeof(Name2));
  LoadingEEPROMAddress += sizeof(Name2);
  Delay(100);
  
  EEPROMRead(Telephone2, LoadingEEPROMAddress, sizeof(Telephone2));
  LoadingEEPROMAddress += sizeof(Telephone2);
  Delay(100);
  
  if(LoadingEEPROMAddress == CurrentEEPROMAddress)
    LoadingEEPROMAddress = EEPROMStart;
  
  for(int i=0 ; i < 14 ; i++)
  {
    Name[i] = (char)Name2[i];
    Telephone[i] = (char)Telephone2[i];
  }
  
  Display("N:",0,0);
  Display("T:",1,0);
  Display(Name,0,2);
  Display(Telephone,1,2);
}

bool isEmptyContact(char* info)
{
  for(int i=0 ; i < 14 ; i++)
    if(info[i] != '\0')
      return false;
  
  return true;
}