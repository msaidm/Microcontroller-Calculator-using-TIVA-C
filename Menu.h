#include <stdint.h>

#define RTC 0
#define Calculator 1
#define List 2
#define Max_Modules 3

extern uint8_t Module;
extern void (*CurrentModule)(void);

void MenuInit(void); 
void RunCurrentModule(void);
void RTCModule(void);
void CalculatorModule(void);
void ListModule(void);
void SwitchModule(void);


