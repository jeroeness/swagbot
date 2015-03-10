#include "manual_mode.h"
#include "motor.h"
#include "../lib/sensor.h"
#include "../lib/serial.h"

extern struct SD sensorData;

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
        stop();
    }else {
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
