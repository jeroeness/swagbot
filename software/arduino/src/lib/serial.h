#ifndef SERIAL_H
#define SERIAL_H

// Thomas implementeerd alle 4 methodes
void serialBegin();
void serialEnd();

char serialRead(void);
char serialReadCharacter(char);

void serialPrint(const char *);
void serialPrintLine(const char *);
void serialWriteCharacter(char);

void serialWriteCharacterFromBuffer();
int8_t serialAvailable();

//char wait_until_bit_is_set(char,char);


#endif // SERIAL_H
