#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "automatic_mode.h"
#include "motor.h"
#include "sensor.h"
#include "mode_manager.h"
#include "../lib/serial.h"

#define TURN_MARGIN 5
#define MOVE_MARGIN 5
#define TIME_MARGIN 5

extern struct SD sensorData;

volatile uint16_t targetDegrees;
volatile uint16_t targetDistance;

volatile uint16_t targetMillis;
volatile uint16_t currentMillis;
volatile uint16_t overflowCount;


volatile int8_t speed;
volatile int8_t defaultSpeed;

volatile uint8_t currentAction;
volatile uint8_t totalActions;
volatile ActionList * actionList;
volatile ActionList actionListList;

void initAutomaticMode() {
	resetClock();
	initTimer();

	setDefaultSpeed(100);

	currentAction = ACTION_IDLE;

	initActionList(10);

	addToActionList(ACTION_MOVE_FOR, 50, 50);
	addToActionList(ACTION_MOVE_FOR, 50, -50);
	addToActionList(ACTION_WAIT, 100, 0);
	addToActionList(ACTION_TURN_FOR, 50, 0);
	addToActionList(ACTION_TURN_FOR, 50, 50);
	addToActionList(ACTION_TURN_FOR, 50, -80);
	addToActionList(ACTION_MOVE_TO, 10, 0);
	addToActionList(ACTION_MOVE_TO, 50, 50);
}

void updateAutomaticMode() {
	checkCrash();
	switch (currentAction) {
		case ACTION_TURN:
			checkTurn();
			break;
		case ACTION_MOVE:
			checkMove();
			break;
		case ACTION_IDLE:
			executeNextAction();
			break;
	}
}

void initActionList(uint8_t size) {
	actionList = &actionListList;

	actionList->list = (Action*) malloc(size * sizeof(Action));
	actionList->size = size;
	actionList->nextAction = 0;
	actionList->usedSize = 0;

	for (uint8_t i=0; i<size; i++) {
		Action* action = &(actionList->list[i]);
		action->action = ACTION_IDLE;
		action->argument = 0;
		action->tempSpeed = 0;
	}
}

void addToActionList(int16_t action, int16_t argument, int16_t tempSpeed) {
	if (actionList->usedSize >= actionList->size) return;

	Action * newAction = &(actionList->list[actionList->usedSize++]);
	newAction->action = action;
	newAction->argument = argument;
	newAction->tempSpeed = tempSpeed;

	serialPrintByte(newAction->action);
}

void initTimer() {
	TIMSK0=(1<<TOIE0);
	TCCR0B = (1<<CS02) | (1<<CS00); // prescaler 1024; fcpu 16000000 = 61 overflows per second
}

ISR(TIMER0_OVF_vect)
{
	if ((++overflowCount) == 2) {
		overflowCount = 0;
		if (targetMillis != 0 && checkFuzzy(targetMillis, ++currentMillis, TIME_MARGIN)) {
			stop();
			currentAction = ACTION_IDLE;
			resetClock();
		}
	}
}

void checkCrash() {
	if (/*sensorData.ultrasonic < 10 ||*/ sensorData.bumperLeft || sensorData.bumperRight) {
		stop();
		SteeringMode s = manual;
		setSteeringMode(s);
		resetAutomaticMode();
	}
}

void executeNextAction() {
	if (actionList->nextAction >= actionList->usedSize)
		actionList->nextAction = 0;

	Action next = actionList->list[actionList->nextAction++];

	if (next.tempSpeed != 0) {
		setSpeed(next.tempSpeed);
	} else if (next.tempSpeed == -1) {
		setSpeed(defaultSpeed * -1);
	} else {
		resetSpeed();
	}

	switch (next.action) {
		case ACTION_MOVE:
			moveDistance(next.argument);
			break;
		case ACTION_MOVE_TO:
			moveToDistance(next.argument);
			break;
		case ACTION_MOVE_FOR:
			moveFor(next.argument);
			break;
		case ACTION_TURN:
			turnByDegrees(next.argument);
			break;
		case ACTION_TURN_TO:
			turnToDegrees(next.argument);
			break;
		case ACTION_TURN_FOR:
			turnFor(next.argument);
			break;
		case ACTION_WAIT:
			resetClock();
			stop();
			currentAction = ACTION_WAIT;
			targetMillis = next.argument;
			break;
		case ACTION_SET_SPEED:
			setDefaultSpeed(next.argument);
 			currentAction = ACTION_IDLE;
			break;
	}
}

void checkTurn() {
	if (checkFuzzy(targetDegrees, sensorData.compassDegrees, TURN_MARGIN)) {
		stop();
		currentAction = ACTION_IDLE;
	} else {
		turn(speed);
	}
}

void checkMove() {
	if (checkFuzzy(targetDistance, sensorData.ultrasonic, MOVE_MARGIN)) {
		stop();
		currentAction = ACTION_IDLE;
	} else {
		if (targetDistance < sensorData.ultrasonic) {
			drive(speed, 0);
		} else {
			drive(-1 * speed, 0);
		}
	}
}

int checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness) {
	return (value1 < value2 + fuzzyness && value1 > value2 - fuzzyness);
}

void turnByDegrees(int16_t degrees) {
	targetDegrees = sensorData.compassDegrees + degrees;
	currentAction = ACTION_TURN;
}

void turnToDegrees(int16_t degrees) {
	targetDegrees = degrees;
	currentAction = ACTION_TURN;
}

void turnFor(int16_t milliseconds) {
	currentAction = ACTION_TURN_FOR;
	resetClock();
	targetMillis = milliseconds;
	turn(speed);
}

void moveFor(int16_t milliseconds) {
	currentAction = ACTION_MOVE_FOR;
	resetClock();
	targetMillis = milliseconds;
	drive(speed, 0);
}

inline void resetClock() {
	currentMillis = 0;
	overflowCount = 0;
}

void resetAutomaticMode() {
	actionList->nextAction = 0;
	currentAction = ACTION_IDLE;
}

inline void setSpeed(int8_t s) {
	speed = s;
}

inline void resetSpeed() {
	speed = defaultSpeed;
}

inline void setDefaultSpeed(int8_t s) {
	defaultSpeed = s;
}

void moveDistance(int16_t distance) {
	targetDistance = sensorData.ultrasonic - distance;
	currentAction = ACTION_MOVE;
}

void moveToDistance(int16_t distance) {
	targetDistance = distance;
	currentAction = ACTION_MOVE;
}

void beginAutomaticMode(){
	resetAutomaticMode();
}

void stopAutomaticMode(){
	stop();
}
