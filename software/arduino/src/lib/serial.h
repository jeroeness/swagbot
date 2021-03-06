// serial.h

#ifndef SERIAL_H
#define SERIAL_H

#include "../globalincsanddefs.h"

void serialBegin();
void serialEnd();

char serialRead(void);
char serialReadCharacter(char);

//void serialPrintStr(const char *);
void serialPrint(const char * c, uint8_t len);
void serialPrintUnsigned(uint8_t c[], uint8_t len);
//void serialPrintLine(const char *);
void serialPrintLine(const char *, int8_t);
//void serialPrintSynchronous(const char *);
void serialPrintSynchronous(const char *, int8_t);
void serialPrintCharacter(const char);
void serialPrintCharacterSynchronous(const char);
void serialPrintByte(const uint8_t);
void serialPrintByteSynchronous(const uint8_t);

uint16_t serialAvailable();
int8_t outputBufferWalked();
void sleepUntilEmptyOutputBuffer();
void writeCharacterFromBuffer();
void clearBuffer();
void clearInputBuffer();

#endif // SERIAL_H
