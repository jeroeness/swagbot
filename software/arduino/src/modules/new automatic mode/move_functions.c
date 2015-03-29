#include "automatic_mode.h"

extern volatile uint8_t currentAction;

extern volatile uint16_t targetDegrees;
extern volatile uint16_t targetDistance;

extern volatile uint16_t targetMillis;

extern volatile int8_t speed;

extern struct SD sensorData; 

void turnByDegrees(Action * action) {
	action->origin = -1 * action->target;

	setTargetDegrees(((int16_t) sensorData.compassDegrees + action->target));

	currentAction = ACTION_TURN;
	printf("%d\n", action->target);
}

void turnToDegrees(Action * action) {
	action->origin = sensorData.compassDegrees;

	setTargetDegrees(action->target);

	// TODO check which way to turn

	currentAction = ACTION_TURN;
	printf("%d\n", action->target);
}

void turnFor(Action * action) {
	currentAction = ACTION_WAIT;
	// resetClock();
	// targetMillis = milliseconds;
	// turn(speed);
	printf("%d\n", action->target);
}

void moveDistance(Action * action) {
	targetDistance = sensorData.ultrasonic - action->target;
	currentAction = ACTION_MOVE;
	printf("%d\n", action->target);
}

void moveToDistance(Action * action) {
	targetDistance = action->target;
	currentAction = ACTION_MOVE;
	printf("%d\n", action->target);
}

void moveFor(Action * action) {
	currentAction = ACTION_WAIT;
	// resetClock();
	targetMillis = action->target;
	// drive(speed, 0);
	printf("%d\n", action->target);
}

void waitFor(Action * action) {
	// resetClock();
	// stop();
	currentAction = ACTION_WAIT;
	targetMillis = action->target;
	printf("%d\n", action->target);
}