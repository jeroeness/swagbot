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

	i2c_init(0xA8);
	initAutomaticMode();

	initCommunication();
	initSensors();
	
	uint16_t counter1 = 0;
	uint16_t counter2 = 0;
	
	sei();

	setSteeringMode(manual);
	resetAutomaticMode(); //TODO init automatic mode

	moveMotors(0, 0);
	i2c_write_cmd_wrap();

	while(1)
	{
		
		
		
		
		if(counter1++ >= 0x2FFF){ //im there
			counter1 = 0;
			i2c_read_sensors_wrap();
			
		}else if(counter1 == 0x17FF){ //halfway there
			i2c_write_cmd_wrap();
		}
		
		if(counter2++ >= 0x8FFF){ //im there
			counter2 = 0;
			updateSensors();
		}
		
		updateModeManager();
		updateCommunication();
	}

	return 1998;
}
