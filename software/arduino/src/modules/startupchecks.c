//startupchecks

#include "../globalincsanddefs.h"
//#include "i2c_lib.h"
extern union USD sensorData;

void diagnostics(){
	int step = 0;
	while(step < 4){
		i2c_read_sensors_wrap();

		//compass checks
		if(step==0 && sensorData.sensorStruct.compassDegrees){	
			step = 1;		//next step		
			setScrollText("/gCompass Check Passed");
			specialDelay();		//wait a few seconds
			clearDisplayData();	//clear the ledgrid
			setScrollText("/bLeft Bumper Check");
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;		//next step
			clearDisplayData();	//clear ledgrid
			checkPassed();		//write "check passed"
			specialDelay();		//wait a few seconds
			clearDisplayData();	//clear ledgrid
			setScrollText("/bRight Bumper Check");
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;		//next step
			clearDisplayData();	//clear ledgrid
			checkPassed();		//write "check passed"
			specialDelay();		//wait a few seconds
			clearDisplayData();	//clear ledgrid
			setScrollText("/bSonar Check");
		}
		
		//sonar
		if(step==3 && sensorData.sensorStruct.ultrasonic >= 15){
			step = 4;		//next step		
			checkPassed();		//write "check passed"
//			turnByDegrees(120);	//check motors by turning
	//		turnByDegrees(120);
		//	turnByDegrees(120);
			specialDelay();		//wait a few seconds
			clearDisplayData();	//clear ledgrid
		}
	}
}

void checkPassed(){
	setScrollText("/gCheck Passed");
}

void specialDelay(){
	//int i;
	//for(i=0;i<30000){}
	_delay_ms(3000);
}
