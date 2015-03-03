#define F_CPU 8000000 //Base: 8.00MHz - DO NOT CHANGE! // CPU works @ 8.0Mhz;

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> // I/O Port definitions
#include <avr/interrupt.h> // Interrupt macros (e.g. cli(), sei())

#include "func_protos.h"

struct sD sensorData;

void testGlobalVariable(){
	DDRC |= 1<<PC4; //green led as output
	
	if(sensorData.bumperLeft == 1){
		PORTC |= 1<<PC4; //green led on
	}else{
		PORTC &= ~(1<<PC4); //green led off
	}
	
}


int main(void) {
	cli();
	initMotor();
	sei();
	
	loadSensors();
	
	while(1) {
		testGlobalVariable();
	}
	
	return 0;
}

