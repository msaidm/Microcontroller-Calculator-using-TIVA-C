#include <stdbool.h>

#define EEPROMStart 0x400

extern char Name[14];
extern char Telephone[14];

void InitContactList(void);
void Save(void);
void Load(void);
#include <stdbool.h>
void New(void);

bool isEmptyContact(char* info);