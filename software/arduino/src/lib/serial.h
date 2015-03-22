// serial.h

#ifndef SERIAL_H
#define SERIAL_H

#include "../globalincsanddefs.h"

void serialBegin();
void serialEnd();

char serialRead(void);
char serialReadCharacter(char);

void serialPrint(const char *);
void serialPrintLine(const char *);
void serialPrintSynchronous(const char *);
void serialPrintCharacter(const char);
void serialPrintCharacterSynchronous(const char);
void serialPrintByte(const uint8_t);
void serialPrintByteSynchronous(const uint8_t);

int8_t serialAvailable();
int8_t outputBufferWalked();
void sleepUntilEmptyOutputBuffer();
void writeCharacterFromBuffer();
void clearBuffer();

#endif // SERIAL_H
