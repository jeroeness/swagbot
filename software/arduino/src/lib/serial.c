// serial.c

#include "../globalincsanddefs.h"

#ifndef BAUD
#define BAUD 19200
#endif

#ifndef BAUD_PRESCALER
#define BAUD_PRESCALER (((F_CPU / (BAUD * 16UL))) - 1)
#endif

#define OUTPUTBUFFER_SIZE 600
#define INPUTBUFFER_SIZE 100

const char *newLineCharacters = "\r\n";

volatile char outputBuffer[OUTPUTBUFFER_SIZE];
volatile int16_t outputBufferLength;
volatile int8_t outputBufferPtr;
volatile char inputBuffer[INPUTBUFFER_SIZE];
volatile uint16_t inputBufferLength;
volatile int8_t inputBufferPtr;


void serialBegin() {
	UBRR0H = (uint8_t)(BAUD_PRESCALER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALER);
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0) | (1 << TXCIE0); //Enable RX and TX and their interrupts
	UCSR0C |= (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00); //1 stopbit(USBS0) 8 databits(UCSZ00 & UCSZ01)

	outputBufferPtr = 0;
	outputBufferLength = 0;
}

void serialEnd() {
	UCSR0A &= ~(1 << U2X0);
	UCSR0B &= ~((1 << TXEN0) | (1 << RXEN0));
	UCSR0C &= ~((1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00));
}

ISR(USART0_RX_vect) {
	
	if (inputBufferLength < INPUTBUFFER_SIZE) {
		inputBuffer[inputBufferLength++] = UDR0;
	}else{
		inputBufferLength = 0;
	}
	//TODO Write callbacks here
	//readInputs(UDR0);
}

ISR(USART0_TX_vect) {
	writeCharacterFromBuffer();
}

uint16_t serialAvailable() {
	return inputBufferLength;
}

char serialRead(void) {
	uint16_t i = 0;
	if(inputBufferLength <= 0) return 0;

	char d = inputBuffer[0];

	//get the first char and shift the rest of the buffer to the beginning.
	for(i = 1; i < inputBufferLength; i++){
		inputBuffer[i-1] = inputBuffer[i];
	}
	inputBufferLength--; //we just took one char so decrease the buffer size

	return d;
}



//void serialPrintStr(const char *c) {
//	serialPrint(c, strlen((char*)c));
//}

void serialPrint(const char *c, uint8_t len) {

	if (len + outputBufferLength >= OUTPUTBUFFER_SIZE) {
		//TODO stressled
		return;
	}

	memcpy((char*)outputBuffer + outputBufferLength, c, len + 1);
	outputBufferLength += len;

	if (outputBufferLength == len) {
		writeCharacterFromBuffer();
	}
}

void serialPrintUnsigned(uint8_t c[], uint8_t len) {

	if (len + outputBufferLength >= OUTPUTBUFFER_SIZE) {
		//TODO stressled
		return;
	}

	memcpy((char*)outputBuffer + outputBufferLength, c, len + 1);
	outputBufferLength += len;

	if (outputBufferLength == len) {
		writeCharacterFromBuffer();
	}
}

void serialPrintByte(const uint8_t byte) {
	uint8_t c = byte >> 4;

	if (c < 10) {
		serialPrintCharacter(c + 48);
	} else{
		serialPrintCharacter(c + 55);
	}

	c = byte & 0x0F;
	if (c < 10) {
		serialPrintCharacter(c + 48);
	} else {
		serialPrintCharacter(c + 55);
	}
}

void serialPrintByteSynchronous(const uint8_t byte) {
	serialPrintByte(byte);
	sleepUntilEmptyOutputBuffer();
}

void serialPrintCharacter(const char c) {
	char cp [2];
	cp[0] = c;
	cp[1] = 0;
	serialPrint(cp, 1);
}

void serialPrintCharacterSynchronous (const char c) {
	serialPrintCharacter(c);
	sleepUntilEmptyOutputBuffer();
}


void serialPrintSynchronous (const char *c, int8_t len) {
	serialPrint(c, len);
	sleepUntilEmptyOutputBuffer();
}


void serialPrintSynchronous (const char *c) {
	serialPrintSynchronous(c, strlen(c));
}

void serialPrintLine(const char *c, int8_t len) {
	char *ln = (char*)malloc((len + 3) * sizeof(char));
	memcpy(ln, c, len + 1);
	strcat(ln, newLineCharacters);
	serialPrint(ln, len);
	free(ln);
}

/*
void serialPrintLine(const char *c) {
	serialPrintLine(c, strlen(c));
}*/

void writeCharacterFromBuffer() {
	if (!outputBufferWalked()) {
		UDR0 = outputBuffer[outputBufferPtr++];
	} else {
		clearBuffer();
	}
}

int8_t outputBufferWalked() {
	return outputBufferPtr >= outputBufferLength;
}

void sleepUntilEmptyOutputBuffer() {
	while (!outputBufferWalked());
	clearBuffer();
}

void clearInputBuffer(){
	inputBufferLength = 0;

}

void clearBuffer() {
	outputBufferPtr = 0;
	outputBuffer[0] = '\0';
	outputBufferLength = 0;
}
