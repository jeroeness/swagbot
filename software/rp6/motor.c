//motor.c
#include "func_protos.h"

volatile int8_t
	destSpeedL = 0,	
	destSpeedR = 0,
	speedL = 0,
	speedR = 0;

void initMotor(){
	TCNT1 = 0x00;
	TCCR1A = (0 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B = (1 << WGM13) | (0 << WGM12) | (1 << CS10);
	
	ICR1 = 0x00FF;
	OCR1A = 0x00;
	OCR1B = 0x00;
	
	TIMSK &= ~(1<< TICIE1) &~(1<< OCIE1A) &~(1<< OCIE1B) &~(1<< TOIE1);
	

	TCCR2 |= (1 << CS22); //prescaler 256
	TCNT2 = 0;
	TIMSK |= (1 << TOIE2);


	DDRC |= (1 << PINC2) | (1 << PINC3);
	PORTC |= (1 << PINC2);
	PORTC &= ~(1 << PINC3);
}

ISR(TIMER2_OVF_vect) {
	if (speedL < destSpeedL) speedL++;
	else if (speedL > destSpeedL) speedL--;

	if (speedR < destSpeedR) speedR++;
	else if (speedR > destSpeedR) speedR--;

	moveMotors(speedL, speedR);
}


int changeCourse (int8_t sl, int8_t sr) {
	destSpeedL = min(max(sl, -100), 100);
	destSpeedR = min(max(sr, -100), 100);
	return 1;
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
