// manual_mode.c

#include "../globalincsanddefs.h"

//extern union UID instructionData;
extern union USD sensorData;

void inputRight() {
	turn(100);
}

void inputLeft() {
	turn(-100);
}

void inputBackward() {
	moveMotors(-100, -100);
}

void inputForward() {
	if(sensorData.sensorStruct.bumperRight == 1 || sensorData.sensorStruct.bumperLeft == 1) {
        stop();
    } else {
        moveMotors(100, 100);
    }
}

void inputStop(){
	stop();
}

void stopManualMode() {
	stop();
}

void beginManualMode() {
	//Do nothing
}
