
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
#include <util/delay.h>
#include "serial.h"
#include <stdlib.h>

#ifndef BAUD_PRESCALLER
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)
#endif

const char *newLineCharacters = "\r\n";

volatile char * outputBuffer;
int8_t outputBufferLength;
volatile int8_t outputBufferPtr;
volatile int8_t transmitting = 0;
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
	serialWriteCharacterFromBuffer();
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
	int8_t len = strlen(c) + 1;
	char *msg;
	if (outputBuffer == NULL || outputBuffer[outputBufferPtr] == '\0') {
		free((void*)outputBuffer);
		outputBuffer = (char*) malloc(len * sizeof(char));
		if (outputBuffer == NULL) {
			//TODO flash stressled
			const char* stressMsg = "**ERROR_MSG_TO_LONG**";
			msg = (char*)stressMsg;
			len = strlen(msg) + 1;
			outputBuffer = (char*) malloc(len * sizeof(char));

		} else {
			msg = (char*)c;
		}
		memcpy((void*)outputBuffer, msg, len - 1);
		outputBuffer[len-1] = '\0';
		outputBufferLength = len - 1;
		outputBufferPtr = 0;
		serialWriteCharacterFromBuffer();
	} else {
		outputBuffer = (char*) realloc((void*)outputBuffer, (outputBufferLength + len) * sizeof(char));
		if (outputBuffer == NULL) {
			//TODO flash stressled
			free((void*)outputBuffer);
			serialPrint(c);
			return;
		}
		outputBufferLength += len - 1;
		strcat((char*)outputBuffer, c);
	}
}

void serialPrintLine(const char *c) {
	char *ln = (char*)malloc((strlen(c) + 3) * sizeof(char));
	memcpy(ln, c, strlen(c) + 1);
	strcat(ln, newLineCharacters);
    serialPrint(ln);
}

void serialWriteCharacterFromBuffer() {
	transmitting = outputBuffer[outputBufferPtr] != 0;
	if (transmitting) {
		UDR0 = outputBuffer[outputBufferPtr++];
	}
}

//TODO outputBufferEmpty();
//TODO sleepUntilEmptyOutputBuffer();
