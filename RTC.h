#include <stdint.h>

#define SecondsInMinute 60
#define SecondsInHour 3600
#define SecondsInDay 86400
#define SecondsInMonth 2678400
#define SecondsInYear 32140800
#define DefaultDate 348032

extern uint32_t Years;

void InitRTC(void);
void DisplayClock(void);
void DisplaySeconds(uint32_t timeInSeconds);
void DisplayMinutes(uint32_t timeInSeconds);
void DisplayHours(uint32_t timeInSeconds);
void DisplayDays(uint32_t timeInSeconds);
void DisplayMonths(uint32_t timeInSeconds);
void DisplayYears(uint32_t timeInSeconds);