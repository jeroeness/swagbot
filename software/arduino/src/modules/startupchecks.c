//startupchecks

#include "../globalincsanddefs.h"
extern union USD sensorData;

void diagnostics(){
	int step = 0;
	int compassTemp;
	
	while(step < 4){
		//compass checks
		if(step==0){	
			compassTemp = sensorData.sensorStruct.compassDegrees;
			turn(-100);
			_delay_ms(100);
			stop();
			if(sensorData.sensorStruct.compassDegrees != compassTemp){
				step = 1;		//next step	
				turnFunction();
				//setScrollText("/gCompass Check Passed");
				//specialDelay();		//wait a few seconds
				//clearDisplayData();	//clear the ledgrid
				//setScrollText("/bLeft Bumper Check");
			}
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;		//next step
			turnFunction();
			//clearDisplayData();	//clear ledgrid
			//checkPassed();		//write "check passed"
			//specialDelay();		//wait a few seconds
			//clearDisplayData();	//clear ledgrid
			//setScrollText("/bRight Bumper Check");
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;			//next step
			turnFunction();
			//clearDisplayData();	//clear ledgrid
			//checkPassed();		//write "check passed"
			//specialDelay();		//wait a few seconds
			//clearDisplayData();	//clear ledgrid
			//setScrollText("/bSonar Check");
		}
		
		//sonar
		if(step==3 && sensorData.sensorStruct.ultrasonic >= 15){
			step = 4;			//next step		
			turnFunction();
			//checkPassed();		//write "check passed"
			//turnByDegrees(120);	//check motors by turning
			//turnByDegrees(120);
			//turnByDegrees(120);
			//specialDelay();		//wait a few seconds
			//clearDisplayData();	//clear ledgrid
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

void turnFunction(){
	turn(100);
	_delay_ms(500);
	stop();
}

