#define F_CPU 8000000 //Base: 8.00MHz - DO NOT CHANGE! // CPU works @ 8.0Mhz;

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> // I/O Port definitions
#include <avr/interrupt.h> // Interrupt macros (e.g. cli(), sei())

#include "func_protos.h"

struct sD sensorData;



void testGlobalVariable(){
	
	if(sensorData.bumperLeft == 1){
		setLed(1,1);
		setLed(2,0);
		setLed(3,1);
		setLed(4,0);
		setLed(5,1);
		setLed(6,0);
	}else{
		setLed(1,0);
		setLed(2,1);
		setLed(3,0);
		setLed(4,1);
		setLed(5,0);
		setLed(6,1);
	}
	
}






int main(void) {
	cli();
	initMotor();
	sei();
	
	initSensors();
	
	//setLed(2,1);
	
	//DDRB |= 1<<PB3; //green led as output

	stop();
	
	while(1) {
		readSensors();
		testGlobalVariable();
	}
	
	return 0;
}

