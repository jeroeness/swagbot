#define F_CPU 8000000 //Base: 8.00MHz - DO NOT CHANGE! // CPU works @ 8.0Mhz;

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> // I/O Port definitions
#include <avr/interrupt.h> // Interrupt macros (e.g. cli(), sei())

#include "func_protos.h"

/*****************************************************************************/
#define BAUD_LOW 38400 //Low speed - 38.4 kBaud
#define UBRR_BAUD_LOW ((F_CPU/(16*BAUD_LOW))-1)
#define BAUD_HIGH 500000 //High speed - 500 kBaud
#define UBRR_BAUD_HIGH ((F_CPU/(16*BAUD_HIGH))-1)
/*****************************************************************************/

void initMotor(){
	TCNT1=0x00;
	TCCR1A = (0 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B = (1 << WGM13) | (0 << WGM12) | (1 << CS10);
	
	ICR1=0x00FF;
	OCR1A=0x0050;
	OCR1B=0x0050;
	
	TIMSK &= ~(1<< TICIE1) &~(1<< OCIE1A) &~(1<< OCIE1B) &~(1<< TOIE1);
	
	DDRC |= (1 << PINC2) | (1 << PINC3);
	PORTC |= (1 << PINC2);
	PORTC &= ~(1 << PINC3);
}

ISR(TIMER1_COMPA_vect){
}

ISR(TIMER1_COMPB_vect){
}

void motorTest() {
  
  
}


// -bend = left; +bend = right
void drive(int speed, int bend, int direction) {
	moveMotors(direction, direction, speed + bend, speed - bend);
}


void stop() {
	moveMotors(0, 0, 0, 0);
}

//dirL, dirR direction of left and right motor. 1=forward, -1=backward
//speedL, speedR movement speed of left and right motor. 0 <= speed <= 200
void moveMotors(int dirL,int dirR,int speedL,int speedR){
	//direction
	DDRC |= (1 << PINC2) | (1 << PINC3);
	if(dirL == 1){
		PORTC &= ~(1 << PINC2);
	}
	
	else{
		PORTC |= (1 << PINC2);
	}
	
	if(dirR == 1){
		PORTC &= ~(1 << PINC3);
	}
	
	else{
		PORTC |= (1 << PINC3);
	}
	
	//speed
	if(speedR >= 0 && speedR <= 200){
		OCR1AL=speedR;
	}
	
	if(speedL >= 0 && speedL <= 200){
		OCR1BL=speedL;
	}
}
