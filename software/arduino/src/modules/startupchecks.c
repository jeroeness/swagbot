//startupchecks

#include "../globalincsanddefs.h"

extern union USD sensorData;

void diagnostics(){
	int step = 0;
	while(step < 4){
		i2c_read_sensors(sizeof(sensorData.sensorStruct));
		
		//compass
		if(step==0 && sensorData.sensorStruct.compassDegrees){
			step = 1;
			checkPassed();
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;
			checkPassed();
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;
			checkPassed();
		}
		
		//sonar
		if(step==3 && sensorData.sensorStruct.ultrasonic >= 15){
			step = 4;
			turnByDegrees(360);
			//motor rondje draaien
		}
	}
}

void checkPassed(){
	turnByDegrees(45);
	turnByDegrees(-45);
}