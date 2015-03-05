#define F_CPU 8000000
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "func_protos.h"

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

//dirL, dirR direction of left and right motor. 1=forward, -1=backward
//speedL, speedR movement speed of left and right motor. 0 <= speed <= 200
int moveMotors(int8_t speedL, int8_t speedR){
	if(speedR < -100 || speedR > 100)
	    return 0;
	if(speedL < -100 || speedL > 100)
	    return 0;

	//direction
	DDRC |= (1 << PINC2) | (1 << PINC3);
	if(speedL > 0){
		PORTC &= ~(1 << PINC2);
	} else{
		PORTC |= (1 << PINC2);
		speedL = -1 * speedL;
	}
	
	if(speedR > 0){
		PORTC &= ~(1 << PINC3);
	} else{
		PORTC |= (1 << PINC3);
		speedR = -1 * speedR;
	}
	
	OCR1AL = 2 * speedR;
	OCR1BL = 2 * speedL;
	
	return 1;
}
