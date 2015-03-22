/*
 * arduino.c
 *
 * Created: 14-3-2015 12:13:05
 *  Author: -
 */ 

#include "globalincsanddefs.h"

//extern union UID instructionData;
//extern union USD sensorData;
//struct ID instructionData;
//struct SD sensorData;

int main(void)
{
	cli();

	PORTD = 3;

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
		//sei();
//		serialPrintSynchronous("out of auto update");
		//moveMotors(50,50);
		updateModeManager();
		updateCommunication();
//		serialPrintSynchronous("out of commu update");
	}

	return 1998;
}
