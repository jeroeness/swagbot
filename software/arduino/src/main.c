/*
 * arduino.c
 *
 * Created: 14-3-2015 12:13:05
 *  Author: -
 */

#include "globalincsanddefs.h"
union UID instructionData;
union USD sensorData;

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

	sei();

	//diagnostics();
	
	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode
	
	setEmotion(1);
	
	moveMotors(0, 0);
	
	while(1){
		if(counter++ >= 0x8FFF){ //im there
			counter = 0;
			updateSensors(); //could not create timer for this one.
		}
		updateModeManager();
		updateCommunication();
	}

	return 1998;
}






