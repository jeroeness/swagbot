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
	drive(200, 100, -1);
	_delay_ms(3000);
	drive(200, -100, -1);
	_delay_ms(3000);
	stop();
	_delay_ms(3000);
	turn(200);
	_delay_ms(3000);
	turn(100);
	_delay_ms(3000);
}


// negative deflection = left; positive deflection = right
void drive(int speed, int deflection, int direction) {
	int speedL = speed;
	int speedR = speed;
  
	if (deflection > 0) {
	   speedR -= deflection; 
	} else {
	   speedL += deflection; 
	}
	moveMotors(direction, direction, speedL, speedR);
}

void turn(int speed) {
	int speedL = speed;
	int speedR = speed;
	
	int dirL, dirR;
	
	if (speed > 0) {
	     dirL = 1;
	     dirR = -1;
	} else {
	     dirL = -1;
	     dirR = 1;
	     speed = -1 * speed;
	}
  
	moveMotors(dirL, dirR, speed, speed);
}


void stop() {
	moveMotors(0, 0, 0, 0);
}

//dirL, dirR direction of left and right motor. 1=forward, -1=backward
//speedL, speedR movement speed of left and right motor. 0 <= speed <= 200
int moveMotors(int dirL,int dirR,int speedL,int speedR){
	if(speedR < 0 || speedR > 200)
	    return 0;
	if(speedL < 0 || speedL > 200)
	    return 0;

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
	
	OCR1AL = speedR;
	OCR1BL = speedL;
	
	return 1;
}
