
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "sensor.h"

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
	drive(100, 50, -1);
	_delay_ms(3000);
	drive(100, -50, -1);
	_delay_ms(3000);
	stop();
	_delay_ms(3000);
	turn(100);
	_delay_ms(3000);
	turn(50);
	_delay_ms(3000);
}


// negative deflection = left; positive deflection = right
void drive(int8_t speed, int8_t deflection, int8_t direction) {
	int speedL = speed;
	int speedR = speed;
  
	if (deflection > 0) {
	   speedR -= deflection; 
	} else {
	   speedL += deflection; 
	}
	moveMotors(direction * speedL, direction * speedR);
}

void turn(int8_t speed) {
	moveMotors(speed, -speed);
}

void stop() {
	moveMotors(0, 0);
}

//dirL, dirR direction of left and right motor. 1=forward, -1=backward
//speedL, speedR movement speed of left and right motor. 0 <= speed <= 200
int moveMotors(int8_t speedL, int8_t speedR){
	if(speedR < -100 || speedR > 100)
	    return 0;
	if(speedL < -100 || speedL > 100)
	    return 0;

	sensorData.motorLeft = speedL;
	sensorData.motorRight = speedR;
	
	return 1;
}
