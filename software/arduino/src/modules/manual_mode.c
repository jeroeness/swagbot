#include "manual_mode.h"
#include "motor.h"
#include "../lib/sensor.h"
#include "../lib/serial.h"

void inputRight() {
	turn(100);
}

void inputLeft() {
	turn(100);
}

void inputBackward() {
	moveMotors(-100, -100);
}

void inputForward() {
	if(sensorData.bumperRight == 1 || sensorData.bumperLeft == 1){
        inputStop();
    }else {
        moveMotors(100, 100);
    }
}

void inputStop() {
	moveMotors(0, 0);
}

void stopManualMode() {
	inputStop();
}

void beginManualMode() {
	//Do nothing
}
