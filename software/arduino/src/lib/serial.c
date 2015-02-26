#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <stdio.h>
//#include <USART.h>
#include <util/setbaud.h>
#include "lib/serial.h"


void serialBegin(){
	UCSR0A |= (1 << U2X0);     // Double the USART Transmission Speed
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //Enable RX and TX
    UCSR0C |= (1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00); //1 stopbit(USBS0) 8 databits(UCSZ00 & UCSZ01)
}

void serialEnd(){
    UCSR0A &= ~(1 << U2X0);
    UCSR0B &= ~(1 << TXEN0 | 1 << RXEN0);
    UCSR0C &= ~(1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00);
}


char *serialRead();
void serialWrite(char *);

//www.appelsiini.net/2011/simple-usart-with-avr-libc
//De code hieronder komt uit de arduino lib moet dit nog aanpassen
/*
void transmitByte(uint8_t data) {
                                     // Wait for empty transmit buffer
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;                                            // send data
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);       // Wait for incoming data
  return UDR0;                                // return register value
}
*/
