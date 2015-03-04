#define F_CPU 8000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "func_protos.h"

struct SD sensorData;


void initSensors(){
	DDRC |= 1<<PC6 | 1<<PC5 | 1<<PC4; //set leds as output (Right)
	DDRB |= 1<<PB7 | 1<<PB1 | 1<<PB0; //set leds as output (Left)
}


//Use it like this to turn SL5 on: setLed(5,1);
//Use it like this to turn SL3 off: setLed(3,0);
void setLed(uint8_t uLed, uint8_t uOn){
	//PWRON is on PB4, Yellow power led.
	
	uLed |= uOn<<4;
	switch (uLed){
		case 0x1: //SL1 off
			PORTC &= ~(1<<PC4);
			break;
			
		case 0x2: //SL2 off
			PORTC &= ~(1<<PC5);
			break;
			
		case 0x3: //SL3 off
			PORTC &= ~(1<<PC6);
			break;
			
		case 0x4: //SL4 off
			PORTB &= ~(1<<PB7);
			break;
			
		case 0x5: //SL5 off
			PORTB &= ~(1<<PB1);
			break;
			
		case 0x6: //SL6 off
			PORTB &= ~(1<<PB0);
			break;
			
		case 0x11: //SL1 on
			PORTC |= (1<<PC4);
			break;
			
		case 0x12: //SL2 on
			PORTC |= (1<<PC5);
			break;
			
		case 0x13: //SL3 on
			PORTC |= (1<<PC6);
			break;
			
		case 0x14: //SL4 on
			PORTB |= (1<<PB7);
			break;
			
		case 0x15: //SL5 on
			PORTB |= (1<<PB1);
			break;
			
		case 0x16: //SL6 on
			PORTB |= (1<<PB0);
			break;
		
	}
}


void readBumperL(){
	int DDRCurrent = DDRB;
	int PORTCurrent = PORTB;

	DDRB &= ~(1<<PB0);
	PORTB &= ~(1<<PB0);
	
	_delay_us(3);

	if(PINB & (1<<PB0)){
		sensorData.bumperLeft = 1;
	}else{
		sensorData.bumperLeft = 0;
	}
	
	
	DDRB = DDRCurrent;
	PORTB = PORTCurrent;

}

void readBumperR(){
	int DDRCurrent = DDRC;
	int PORTCurrent = PORTC;

	DDRC &= ~(1<<PC6);
	PORTC &= ~(1<<PC6);
	
	_delay_us(3);

	if(PINB & (1<<PC6)){
		sensorData.bumperRight = 1;
	}else{
		sensorData.bumperRight = 0;
	}
	
	DDRC = DDRCurrent;
	PORTC = PORTCurrent;

}



void readSensors(){
	readBumperR();
	readBumperL();
	
	
}