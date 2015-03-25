// manual_mode.c

#include "../globalincsanddefs.h"

//extern union UID instructionData;
extern union USD sensorData;

int8_t forward;
int8_t direction;
uint8_t collision;

void inputRight() {
	direction = 60;
}

void inputLeft() {
	direction = -60;
}

void inputBackward() {
	forward = -90;
	collision = 0;
}

void inputForward() {
    forward = 90;
    collision = 0;
}


void stopManualMode() {
	stop();
}

void beginManualMode() {
	forward = 0;
	direction = 0;
	collision = 0;
	//Do nothing
}

void stopForward() {
	forward = forward > 0 ? 0 : forward;
}
void stopLeft() {
	direction = direction < 0 ? 0 : direction;
}
void stopBackward() {
	forward = forward < 0 ? 0 : forward;
}
void stopright() {
	direction = direction > 0 ? 0 : direction;
}

void alterCourse () {
    moveMotors(min(forward + direction, 100), min(forward - direction, 100));
}

void manualModecheckCollision () {
	uint8_t c = sensorData.sensorStruct.bumperRight == 1 || sensorData.sensorStruct.bumperLeft == 1;
	if (c != collision && c) {
		//TODO when we know for sure the bumperdata is correct we can uncomment this line
        //forward = min(0, forward);
		alterCourse();
		collision = c;
	}

}
