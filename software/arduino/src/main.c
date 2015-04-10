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

	i2c_init();
	initAutomaticMode();

	initCommunication();
	initSensors();
	initLedGrid();

	sei();
	
	_delay_ms(100);
	if(sensorData.sensorStruct.bumperLeft == 1 && sensorData.sensorStruct.bumperRight == 1){
		while(sensorData.sensorStruct.bumperLeft > 0 || sensorData.sensorStruct.bumperRight > 0){
			_delay_ms(100);
		}
		_delay_ms(100);
		diagnosticsLedgrid();
	}
	
	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode
	
	moveMotors(0, 0);
	
	displayText("/g14");
	
	while(1){
		if(counter++ >= 0x4FFF){ //im there
			counter = 0;
			updateSensors(); //could not create timer for this one.
		}
		updateModeManager();
		updateCommunication();
		
	}

	return 1998;
}






