#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "automatic_mode.h"
#include "motor.h"
#include "sensor.h"
//#include "mode_manager.h"

#define TURN_MARGIN 5
#define MOVE_MARGIN 5
#define TIME_MARGIN 5

#define ACTION_IDLE 		0
#define ACTION_TURN 		1
#define ACTION_TURN_TO 		2
#define ACTION_TURN_FOR		3
#define ACTION_MOVE 		4
#define ACTION_MOVE_TO 		5
#define ACTION_MOVE_FOR		6
#define ACTION_WAIT 		7
#define ACTION_SET_SPEED 	8
#define ACTION_SET_DIRECTION 	9

struct SD sensorData;

uint16_t targetDegrees;
uint16_t targetDistance;

volatile uint16_t targetMillis;
volatile uint16_t currentMillis;
volatile uint16_t overflowCount;

uint8_t action;

uint8_t speed;
uint8_t direction;

uint8_t nextAction;
uint8_t totalActions;
int16_t** actionList;

void initAutomaticMode() {
	resetClock();

	setSpeed(200);
	setDirection(1);

	action = ACTION_IDLE;
	nextAction = 0;

	actionList = (int16_t**) calloc(4, sizeof(int16_t*));
	for (uint8_t i=0; i<4; i++) {
		actionList[i] = (int16_t*) calloc(2, sizeof(int16_t));
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

void initTimer() {
	TIMSK0=(1<<TOIE0);
	TCCR0B = (1<<CS02); // prescaler 256; fcpu 8000000 = 122 overflows per second
}

ISR(TIMER0_OVF_vect)
{
	if ((overflowCount++) % 1.2 == 0) {
		overflowCount = 1;
		if (targetMillis != 0 && checkFuzzy(targetMillis, ++currentMillis, TIME_MARGIN)) {
			stop();
			action = ACTION_IDLE;
			resetClock();
		}
	}
}

void checkCrash() {
	if (sensorData.ultrasonic < 10 || sensorData.bumperLeft || sensorData.bumperRight) {
		stop();
		setSteeringMode(SteeringMode.manual);
		resetAutomaticMode();
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
		case ACTION_MOVE_FOR:
			moveFor(next[1], direction);
			break;
		case ACTION_TURN:
			turnByDegrees(next[1]);
			break;
		case ACTION_TURN_TO:
			turnToDegrees(next[1]);
			break;
		case ACTION_TURN_FOR:
			turnFor(next[1]);
			break;
		case ACTION_WAIT:
			resetClock();
			targetMillis = next[1];
			break;
		case ACTION_SET_SPEED:
			setSpeed(next[1]);
			action = ACTION_IDLE;
			break;
		case ACTION_SET_DIRECTION:
			setDirection(next[1]);
			action = ACTION_IDLE;
			break;
	}
}

void checkTurn() {
	if (checkFuzzy(targetDegrees, sensorData.compassDegrees, TURN_MARGIN)) {
		stop();
		action = ACTION_IDLE;
	} else {
		turn(200);
	}
}

void checkMove() {
	if (checkFuzzy(targetDistance, sensorData.ultrasonic, MOVE_MARGIN)) {
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

void turnFor(int16_t milliseconds) {
	action = ACTION_TURN_FOR;
	resetClock();
	targetMillis = milliseconds;
	turn(speed);
}

void moveFor(int16_t milliseconds, int8_t direction) {
	action = ACTION_MOVE_FOR;
	resetClock();
	targetMillis = milliseconds;
	drive(speed, 0, direction);
}

inline void resetClock() {
	currentMillis = 0;
	overflowCount = 1;
}

void resetAutomaticMode() {
	nextAction = 0;
	action = ACTION_IDLE;
}

inline void setSpeed(int8_t s) {
	speed = s;
}

inline void setDirection(int8_t d) {
	direction = d;
}

void moveDistance(int16_t distance) {
	targetDistance = sensorData.ultrasonic - distance;
	action = ACTION_MOVE;
}

void moveToDistance(int16_t distance) {
	targetDistance = distance;
	action = ACTION_MOVE;
}

void beginAutomaticMode(){
	// do nothing
}

void stopAutomaticMode(){
	stop();
}
