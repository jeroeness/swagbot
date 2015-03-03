#ifndef SERIAL_H
#define SERIAL_H

// Thomas implementeerd alle 4 methodes
void serialBegin();
void serialEnd();

char serialRead(void);
void serialWrite(char *);

char wait_until_bit_is_set(char,char);


#endif // SERIAL_H
