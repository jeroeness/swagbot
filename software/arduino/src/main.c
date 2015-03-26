/*
 * arduino.c
 *
 * Created: 14-3-2015 12:13:05
 *  Author: -
 */

#include "globalincsanddefs.h"
#include "avr/interrupt.h"
union UID instructionData;
union USD sensorData;

extern uint8_t currentFace;

volatile uint8_t OverFlowToggle = 0; //for timer overflow

void initTimersMain(){
	//timer0: set prescaler of 1024
	TCCR3B |= (1 << CS31) | (0<<CS30);
	
	//timer0: init counter
	TCNT3 = 63000;
	
	//timer0: enable overflow interrupt
	TIMSK3 |= (1 << TOIE3);
	
	
	/*
	TCCR1B |= (1 << CS12) | (0<<CS10);
	
	//timer0: init counter
	TCNT1 = 30000;
	
	//timer0: enable overflow interrupt
	TIMSK1 |= (1 << TOIE1);*/
	
	/* timer4 not using because of updatesensors()
	TCCR4B |= (1 << CS42) | (0<<CS40);
	
	//timer4: init counter differently than others to prevent simontaineously execution
	TCNT4 = 0;
	
	//timer0: enable overflow interrupt
	TIMSK4 |= (1 << TOIE4);*/
}


int main(void)
{
	uint16_t counter1 = 0;
	uint16_t counter2 = 0;
	//uint16_t counter3 = 0;
	
	cli();
	
	PORTD = 3;

	i2c_init(0xA8);
	initAutomaticMode();

	initCommunication();
	initSensors();
	initLedGrid();
	initTimersMain();
	
	sei();
	currentFace = 5;

	//diagnostics();
	
	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode

	moveMotors(0, 0);
	i2c_write_cmd_wrap();

	while(1)
	{
		/*
		if(counter1++ >= 0x2FFF){ //im there
			counter1 = 0;
			i2c_read_sensors_wrap();
			
		}else if(counter1 == 0x17FF){ //halfway there
			i2c_write_cmd_wrap();
		}
		*/
		
		if(counter2++ >= 0x8FFF){ //im there
			counter2 = 0;
			updateSensors(); //could not create timer for this one.
			//it blocks the smoothness for the display
		}
		
		/*
		if(counter3++ >= 0x2FFF){ //im there
			counter3 = 0;
			updateSensors(); //could not create timer for this one.
			//it blocks the smoothness for the display
		}*/
		
		updateModeManager();
		updateCommunication();

	}

	return 1998;
}



ISR(TIMER3_OVF_vect)
{

	uint16_t i = 0;
	i = updateLedGrid();
	TCNT3 = 61000;
	
	/*if (i > 8) i = 8;
	
	i = 62000 - (i * 500);
	TCNT3 = i;
	*/
	/*
	if( > 5){
		TCNT3 = 55000;
	if(updateLedGrid() > 5){
		TCNT3 = 55000;
	}else{
		TCNT3 = 63000;
		
	}*/
	
}

/*
ISR(TIMER4_OVF_vect)
{
	updateSensors();
	TCNT4 = 21000;
}*/



ISR(TIMER1_OVF_vect)
{
	OverFlowToggle ^= 1;
	if(OverFlowToggle == 1){
		i2c_write_cmd_wrap();
	}else{
		i2c_read_sensors_wrap();
	}
	TCNT1 = 30000;
}
