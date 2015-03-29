#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

#include <stdio.h>
#include <stdlib.h>

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*----------- Automatic Mode functions ------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#define ACTION_IDLE 		0
#define ACTION_TURN 		1
#define ACTION_MOVE 		2
#define ACTION_WAIT 		3

#define F_TURN_BY_DEGREES	0
#define F_TURN_TO_DEGREES	1
#define F_TURN_FOR			2
#define F_MOVE_DISTANCE		3
#define F_MOVE_TO_DISTANCE	4
#define F_MOVE_FOR			5
#define F_WAIT				6


typedef struct {
	uint8_t functionIndex;
	int16_t target;
	int16_t speed;
	int16_t origin;
} Action;

typedef struct {
	Action* list;
	uint8_t size;
	uint8_t nextAction;
	uint8_t usedSize;
} ActionList;



void initAutomaticMode();
void initFunctionList();
void updateAutomaticMode();
void checkCrash();
void executeNextAction();
void checkTurn();
void checkMove();
int checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness);
void initTimer();
void setSpeed(int8_t s);

void beginAutomaticMode();
void stopAutomaticMode();
void resetAutomaticMode();
void resetClock();

void initActionList(uint8_t size);
void fillEmptyActionList();
void addToActionList(uint8_t action, int16_t argument, int16_t tempSpeed);
void doubleActionList();
void destroyActionList();
void testAction(uint8_t action, uint16_t arg1, uint16_t arg2);
void reverseActionTest();
Action getReverse(Action action);
void printAction(Action action);


volatile uint8_t currentAction;

volatile uint16_t targetDegrees;
volatile uint16_t targetDistance;

volatile uint16_t targetMillis;
volatile uint16_t currentMillis;
volatile uint16_t overflowCount;


volatile int8_t speed;
volatile int8_t defaultSpeed;

volatile uint8_t findingAngleToPoint;

//////////////////////////////////////////////////////
struct SD{
	uint8_t bumperRight:1;
	uint8_t bumperLeft:1;
	uint16_t compassDegrees;
	int8_t motorLeft;
	int8_t motorRight;
	uint16_t ultrasonic;
};

struct SD sensorData;
//////////////////////////////////////////////////////

#include "move_functions.h"
#include "route_finding_functions.h"

#endif // AUTOMATIC_MODE_H
