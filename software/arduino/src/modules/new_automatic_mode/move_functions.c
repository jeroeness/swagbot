#include "../globalincsanddefs.h"

extern volatile uint8_t currentAction;

extern volatile uint16_t targetDegrees;
extern volatile uint16_t targetDistance;

extern volatile uint16_t targetMillis;

extern volatile int8_t speed;

extern union USD sensorData; 

void turnByDegrees(Action * action) {
	action->origin = -1 * action->target;

	setTargetDegrees(((int16_t) sensorData.sensorStruct.compassDegrees + action->target));

	currentAction = ACTION_TURN;
}


void turnToDegrees(Action * action) {
	action->origin = sensorData.sensorStruct.compassDegrees;

	setTargetDegrees(action->target);
	

	// TODO check which way to turn

	currentAction = ACTION_TURN;
}

void turnFor(Action * action) {
	currentAction = ACTION_WAIT;
	resetClock();
	targetMillis = action->target;
	turn(speed);
}

void moveDistance(Action * action) {
	targetDistance = sensorData.sensorStruct.ultrasonic - action->target;
	action->origin = sensorData.sensorStruct.ultrasonic;
	currentAction = ACTION_MOVE;
}

void moveToDistance(Action * action) {
	targetDistance = action->target;
	action->origin = sensorData.sensorStruct.ultrasonic;
	currentAction = ACTION_MOVE;
}

void moveFor(Action * action) {
	currentAction = ACTION_WAIT;
	resetClock();
	targetMillis = action->target;
	drive(speed, 0);
}

void waitFor(Action * action) {
	resetClock();
	stop();
	currentAction = ACTION_WAIT;
	targetMillis = action->target;
}
