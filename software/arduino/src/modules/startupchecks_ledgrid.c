//startupchecks

#include "../globalincsanddefs.h"
extern union USD sensorData;

void diagnosticsLedgrid(){
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
				step = 1;									//next step	
				checkPassed();
				specialDelay();								//wait a few seconds
				clearDisplayData();							//clear the ledgrid
				setScrollText("/rleft bumper check");
			}
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;										//next step
			clearDisplayData();								//clear ledgrid
			checkPassed();									//write "check passed"
			specialDelay();									//wait a few seconds
			clearDisplayData();								//clear ledgrid
			setScrollText("/rright bumper check");
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;										//next step
			clearDisplayData();								//clear ledgrid
			checkPassed();									//write "check passed"
			specialDelay();									//wait a few seconds
			clearDisplayData();								//clear ledgrid
			setScrollText("/rsonar check");
		}
		
		//sonar
		if(step==3){
			updateSensors();
			_delay_ms(200);
			if(sensorData.sensorStruct.ultrasonic <= 15){
				step = 4;									//next step	
				checkPassed();								//write "check passed"
				turn(100);
				_delay_ms(1000);
				stop();
				specialDelay();								//wait a few seconds
				clearDisplayData();							//clear ledgrid
			}
		}
	}
}

void checkPassed(){
	setScrollText("/gcheck passed");
}

void specialDelay(){
	_delay_ms(8000);
}

/*
void fullTurn(){
	int compassTemp2 = sensorData.sensorStruct.compassDegrees;
	turn(100);
	_delay_ms(100);
	while(sensorData.sensorStruct.compassDegrees != compassTemp2){}
	stop();
}*/

