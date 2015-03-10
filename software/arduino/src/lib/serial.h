#ifndef SERIAL_H
#define SERIAL_H

void serialBegin();
void serialEnd();

char serialRead(void);
char serialReadCharacter(char);

void serialPrint(const char *);
void serialPrintLine(const char *);
void serialWriteCharacter(char);
void serialPrintCharacterSynchronous(const char);
void serialPrintSynchronous(const char *);
void serialPrintByte(const char);

int8_t serialAvailable();
int8_t outputBufferWalked();
void sleepUntilEmptyOutputBuffer();
void writeCharacterFromBuffer();
void clearBuffer();

#endif // SERIAL_H
