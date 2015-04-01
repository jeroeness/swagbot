#include "../globalincsanddefs.h"

#define FORWARDSPEED 90 // Accepted values: (0 < FORWARDSPEED <= 100)
#define STEERINGSPEED 120 // Accepted values: (0 < STEERINGSPEED <= 200)


extern union USD sensorData;

int8_t forward;
int8_t direction;
uint8_t collision;
int8_t forwardKey = 0;

void inputRight() {
	direction = STEERINGSPEED;
}

void inputLeft() {
	direction = -STEERINGSPEED;
}

void inputBackward() {
	forward = -FORWARDSPEED;
}

void inputForward() {
	forwardKey = 1;
	manualModecheckCollision();
	if (!collision) {
		forward = FORWARDSPEED;
	}
}


void stopManualMode() {
	stop();
}

void beginManualMode() {
	forward = 0;
	direction = 0;
	collision = 0;
}

void stopForward() {
	forwardKey = 0;
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
	if (forward == FORWARDSPEED) {
		moveMotors(min(forward + direction, 100), min(forward - direction, 100));
	} else if (forward == -FORWARDSPEED) {
		moveMotors(max(forward + direction, -100), max(forward - direction, -100));
	} else  {
		moveMotors(max(min(direction, 100), -100), max(min(-direction, 100), -100));
	}
}

void manualModecheckCollision () {
	uint8_t c = sensorData.sensorStruct.bumperRight || sensorData.sensorStruct.bumperLeft;
	if (c != collision) {
		if (c) {
			forward = min(0, forward);
			alterCourse();
		} else if (forwardKey) {
			forward = FORWARDSPEED;
		}
		collision = c;
	}

}
