#define F_CPU 8000000

#include <stdio.h>
#include <stdlib.h>
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
uint16_t** actionList;

void initAutomaticMode() {
	action = ACTION_IDLE;
	nextAction = 0;
	actionList = (uint16_t**) calloc(4, sizeof(uint16_t*));
	for (uint8_t i=0; i<4; i++) {
		actionList[i] = (uint16_t*) calloc(2, sizeof(uint16_t));
	}
	actionList[0][0] = ACTION_MOVE; 
	actionList[0][1] = 20; 
	actionList[1][0] = ACTION_WAIT; 
	actionList[1][1] = 1000; 
	actionList[2][0] = ACTION_TURN; 
	actionList[2][1] = 180; 
	actionList[3][0] = ACTION_MOVE_TO; 
	actionList[3][1] = 10; 
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
	if (sensorData.ultrasonic < 10 || sensorData.bumperLeft || sensorData.bumperRight) {
		stop();
		action = ACTION_IDLE;
	}
}

void executeNextAction() {
	uint16_t * next = actionList[nextAction];
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
	if (checkFuzzy(targetDistance, sensorData.ultrasonic, MOVE_MARGE)) {
		stop();
		action = ACTION_IDLE;
	} else {
		if (targetDistance < sensorData.ultrasonic) {
			drive(200, 0, 1);
		} else {
			drive(200, 0, -1);
		}
	}
}

int checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness) {
	return (value1 < value2 + fuzzyness && value1 > value2 - fuzzyness);
}

void turnByDegrees(int16_t degrees) {
	targetDegrees = sensorData.compassDegrees + degrees;
	action = ACTION_TURN;
}

void turnToDegrees(int16_t degrees) {
	targetDegrees = degrees;
	action = ACTION_TURN;
}

void moveDistance(int16_t distance) {
	targetDistance = sensorData.ultrasonic - distance;
	action = ACTION_MOVE;
}

void moveToDistance(int16_t distance) {
	targetDistance = distance;
	action = ACTION_MOVE;
}
