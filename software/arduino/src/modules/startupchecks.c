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
				step = 1;		
				turnFunction();
			}
		}
		
		//bumper L
		if(step==1 && sensorData.sensorStruct.bumperLeft){
			step = 2;		
			turnFunction();
		}
		
		//bumper R
		if(step==2 && sensorData.sensorStruct.bumperRight){
			step = 3;			
			turnFunction();
		}
		
		//sonar
		if(step==3){
			updateSensors();
			_delay_ms(200);
			if(sensorData.sensorStruct.ultrasonic <= 15){
				step = 4;				
				turn(-100);
				_delay_ms(500);
				stop();
			}
		}
	}
}

void turnFunction(){
	turn(100);
	_delay_ms(500);
	stop();
}

