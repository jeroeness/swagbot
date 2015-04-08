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
	
	
	
	updateSensors();
	_delay_ms(200);
	if(sensorData.sensorStruct.bumperLeft == 1 && sensorData.sensorStruct.bumperRight == 1){
		diagnostics();
	}
	
	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode
	
	//setScrollText("/gSwagbot /bPro");
	setEmotion(2);
	moveMotors(0, 0);
	
	while(1){
		if(counter++ >= 0x7FFF){ //im there
			counter = 0;
			updateSensors(); //could not create timer for this one.
		}
		updateModeManager();
		updateCommunication();
		
		/*
		if(sensorData.sensorStruct.bumperLeft == 1){
			setEmotion(1);
		}else{
			//setEmotion(2);
			setSubEmotion(sensorData.sensorStruct.compassDegrees / 11);
		}*/
	}

	return 1998;
}






