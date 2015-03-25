//startupchecks

#include "../globalincsanddefs.h"

extern union USD sensorData;

void diagnostics(){
	int step = 4;
	while(step < 4){
		i2c_read_sensors(sizeof(sensorData.sensorStruct));
		
		//compass
		if(step==0 && sensorData.sensorStruct.compassDegrees){
			step = 1;
			//actie: print, motors draaien
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;
			//actie: print, motors draaien
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;
			//actie: print, motors draaien
		}
		
		//sonar
		/*if(step==3 && sensorData.sensorStruct.ultrasonic >= NOT DEFINED){
			step = 4;
			//actie: print, motors draaien
		}*/
	}
}
