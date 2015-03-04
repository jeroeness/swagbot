#define F_CPU 8000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "func_protos.h"

#define TURN_MARGE 5
#define MOVE_MARGE 5

#define ACTION_IDLE 	0
#define ACTION_TURN 	1
#define ACTION_TURN_TO 	2
#define ACTION_MOVE 	3
#define ACTION_MOVE_TO 	4
#define ACTION_WAIT 	5

struct SD sensorData;

uint16_t targetDegrees;
uint16_t targetDistance;

uint8_t action;

uint8_t nextAction;
uint8_t totalActions;
uint8_t** actionList;

void initAutomaticMode() {
	action = ACTION_IDLE;
	nextAction = 0;
	actionList = { {ACTION_MOVE, 20}, 
				   {ACTION_WAIT, 1000},
				   {ACTION_TURN, 180},
				   {ACTION_MOVE_TO, 10} };
}

void updateAutomaticMode() {
	checkCrash();
	switch (action) {
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

void checkCrash() {
	if (sensorData.ultrasoonDistance < 10 || sensorData.bumperLeft || sensorData.bumperRight) {
		stop();
		action = ACTION_IDLE;
	}
}

void executeNextAction() {
	int * next = actionList[nextAction];
	switch (next[0]) {
		case ACTION_MOVE:
			moveDistance(next[1]);
			break;
		case ACTION_MOVE_TO:
			moveToDistance(next[1]);
			break;
		case ACTION_TURN:
			turnByDegrees(next[1]);
			break;
		case ACTION_TURN_TO:
			turnToDegrees(next[1]);
			break;
	}
}

void checkTurn() {
	if (checkFuzzy(targetDegrees, sensorData.compassDegrees, TURN_MARGE)) {
		stop();
		action = ACTION_IDLE;
	} else {
		turn(200);
	}
}

void checkMove() {
	if (checkFuzzy(targetDistance, sensorData.ultrasoonDistance, MOVE_MARGE)) {
		stop();
		action = ACTION_IDLE;
	} else {
		if (targetDistance < sensorData.ultrasoonDistance) {
			drive(200, 0, 1);
		} else {
			drive(200, 0, -1);
		}
	}
}

int checkFuzzy(int value1, int value2, int fuzzyness) {
	return (value1 < value2 + fuzzyness && value1 > value2 - fuzzyness);
}

void turnByDegrees(int degrees) {
	targetDegrees = sensorData.compassDegrees + degrees;
	action = ACTION_TURN;
}

void turnToDegrees(int degrees) {
	targetDegrees = degrees;
	action = ACTION_TURN;
}

void moveDistance(int distance) {
	targetDistance = sensorData.ultrasoonDistance - distance;
	action = ACTION_MOVE;
}

void moveToDistance(int distance) {
	targetDistance = distance;
	action = ACTION_MOVE;
}
