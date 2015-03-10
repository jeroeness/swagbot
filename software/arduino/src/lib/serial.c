
#ifndef BAUD
#define BAUD 9600
#endif

#ifndef F_CPU
#ifdef __AVR_ATmega2560__
#define F_CPU 8000000UL
#endif // __AVR_ATmega2560__
#ifdef __AVR_ATmega328P__
#define F_CPU 16000000UL
#endif // __AVR_ATmega328P__
#endif // F_CPU

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>
//#include <USART.h>
#include <util/setbaud.h>
#include "serial.h"
#include <stdlib.h>

#ifndef BAUD_PRESCALLER
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)
#endif

#define OUTPUTBUFFER_SIZE 1600

const char *newLineCharacters = "\r\n";

volatile char outputBuffer[OUTPUTBUFFER_SIZE];
int16_t outputBufferLength;
volatile int8_t outputBufferPtr;
volatile char inputBuffer;

void serialBegin(){
    UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B |= 1 << TXEN0 | 1 << RXEN0 | 1 << RXCIE0 | 1 << TXCIE0; //Enable RX and TX and their interrupts
    UCSR0C |= (1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00); //1 stopbit(USBS0) 8 databits(UCSZ00 & UCSZ01)

    outputBufferPtr = 0;
	outputBufferLength = 0;
}

void serialEnd(){
    UCSR0A &= ~(1 << U2X0);
    UCSR0B &= ~(1 << TXEN0 | 1 << RXEN0);
    UCSR0C &= ~(1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00);
}

ISR(USART0_RX_vect) {
	inputBuffer = UDR0;

	//TODO Write callbacks here
}

ISR(USART0_TX_vect) {
	writeCharacterFromBuffer();
}

int8_t serialAvailable () {
	return UDR0;
}

char serialRead(void){
	char d = inputBuffer;
	if (d) {
		inputBuffer = 0;
	}
    return d;
}

void serialPrint(const char *c){

    int8_t len = strlen((char*)c);

    if (len + outputBufferLength >= OUTPUTBUFFER_SIZE) {
        //TODO stressled
        return;
    }

    memcpy((char*)outputBuffer + outputBufferLength, c, len);
    outputBufferLength += len;

    if (outputBufferLength == len) {
        writeCharacterFromBuffer();
    }
}

void serialPrintByte(const char c) {
	char *cp = (char*)malloc(2 * sizeof(char));
	cp[0] = c;
	cp[1] = 0;
    serialPrint(ln);
}

void serialPrintCharacterSynchronous (const char c) {
	serialPrintByte(c);
	sleepUntilEmptyOutputBuffer();
}

void serialPrintSynchronous (const char *c) {
	serialPrint(c);
	sleepUntilEmptyOutputBuffer();
}

void serialPrintLine(const char *c) {
	char *ln = (char*)malloc((strlen(c) + 3) * sizeof(char));
	memcpy(ln, c, strlen(c) + 1);
	strcat(ln, newLineCharacters);
    serialPrint(ln);
}

void writeCharacterFromBuffer() {
	if (!outputBufferWalked()) {
		UDR0 = outputBuffer[outputBufferPtr++];
	}
}

int8_t outputBufferWalked() {
    return outputBuffer[outputBufferPtr] == 0;
}

void sleepUntilEmptyOutputBuffer() {
	while (!outputBufferWalked());
	clearBuffer();
}

void clearBuffer() {
    outputBufferPtr = 0;
    outputBuffer[0] = '\0';
    outputBufferLength = 0;
}
