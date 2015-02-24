#ifndef SERIAL_H
#define SERIAL_H

// Thomas implementeerd alle 4 methodes
void serialBegin(int baud);
void serialEnd();

char *serialRead();
void serialWrite(char *);


#endif // SERIAL_H
