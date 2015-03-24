// ricardo is super cool
#include "../globalincsanddefs.h"

extern union UID instructionData;
extern union USD sensorData;

uint16_t updateTimer = 1;
uint8_t ledsOn = 0;


void updateBatteryLeds(){
	
	if(updateTimer-- == 0){
		updateTimer = 0x4FFF;
		
		if(ledsOn == 1 || sensorData.sensorStruct.batteryPercentage > 50){
			instructionData.instructionstruct.ledStatus &= ~(1<<1 | 1<<2 | 1<<4 | 1<<5);
			ledsOn = 0;
		}else{
			instructionData.instructionstruct.ledStatus |= (1<<1 | 1<<2 | 1<<4 | 1<<5);
			
			ledsOn = 1;
		}
		
	}

	
}