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
	cli();
	
	PORTD = 3;
	sensorData.sensorStruct.ultrasonic = 1;
	
	i2c_init(0xA8);
	initAutomaticMode();

	initCommunication();
	
	
	
	sei();

	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode

	moveMotors(20, 20);
	i2c_write_cmd_wrap();

	while(1)
	{
		//i2c_read_sensors(sizeof(sensorData));
		//updateAutomaticMode();
		//moveMotors(50,50);
		updateModeManager();
		updateCommunication();
		updateBatteryLeds();
	}

	return 1998;
}
