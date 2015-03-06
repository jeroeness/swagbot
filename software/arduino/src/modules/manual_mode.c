#include "manual_mode.h"
#include "motor.h"

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
	moveMotors(100, 100);
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
