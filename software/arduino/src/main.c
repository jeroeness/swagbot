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
extern uint8_t currentSubFace;


volatile uint8_t OverFlowToggle = 0; //for timer overflow

void initTimersMain(){
	//timer3: set prescaler of 1024
	TCCR3B |= (1 << CS31) | (0<<CS30);
	//timer3: init counter
	TCNT3 = 63000;
	//timer3: enable overflow interrupt
	TIMSK3 |= (1 << TOIE3);
	
	
	/*
	TCCR1B |= (1 << CS12) | (0<<CS10);
	//timer0: init counter
	TCNT1 = 30000;
	//timer0: enable overflow interrupt
	TIMSK1 |= (1 << TOIE1);*/
	
	
	//timer 4: prescaler
	TCCR4B |= (1 << CS42) | (0<<CS40);
	//timer4: init counter differently than others to prevent simultaneously execution
	TCNT4 = 58000;
	//timer4: enable overflow interrupt
	TIMSK4 |= (1 << TOIE4);
}


int main(void)
{
	uint16_t counter = 0;
	
	cli();
	
	PORTD = 3;

	i2c_init(0xA8);
	initAutomaticMode();

	initCommunication();
	initSensors();
	initLedGrid();
	initTimersMain();
	
	sei();

	//diagnostics();
	
	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode

	moveMotors(0, 0);
	i2c_write_cmd_wrap();
	
	currentFace = 5;
	
	setScrollText("/rSwag/gBot/b420/gBlazit   /r[JST]/bJucko/g13");
	
	while(1)
	{

		if(counter++ >= 0x8FFF){ //im there
			counter = 0;
			updateSensors(); //could not create timer for this one.
		}

		
		updateModeManager();
		updateCommunication();

	}

	return 1998;
}



ISR(TIMER3_OVF_vect)
{
	uint16_t i = 0;
	i = updateLedGrid();
	TCNT3 = 65000;
	//TCNT3 = 40000;
}


ISR(TIMER4_OVF_vect)
{	
	updateScrollText();
	TCNT4 = 58000;
}



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
