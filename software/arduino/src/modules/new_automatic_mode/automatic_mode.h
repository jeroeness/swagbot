#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

#include <stdio.h>
#include <stdlib.h>

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*----------- Automatic Mode functions ------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#define ACTION_IDLE 			0
#define ACTION_TURN 			1
#define ACTION_MOVE 			2
#define ACTION_WAIT 			3
#define ACTION_FINDING_ANGLE	4

#define F_TURN_BY_DEGREES	0
#define F_TURN_TO_DEGREES	1
#define F_TURN_FOR			2
#define F_MOVE_DISTANCE		3
#define F_MOVE_TO_DISTANCE	4
#define F_MOVE_FOR			5
#define F_WAIT				6

#define TURN_MARGIN 5
#define MOVE_MARGIN 5
#define TIME_MARGIN 5

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
void updateAutomaticMode();

void initActionList(uint8_t size);
void initFunctionList();
void initTimer0(); // TODO add this
void fillEmptyActionList();
void clearActionList();
void addToActionList(uint8_t action, int16_t argument, int16_t tempSpeed);
void addReverseAction(Action action);

void doubleActionList();
void destroyActionList(ActionList * oldActionList);

uint8_t actionListCompleted();

void checkTurn();
void checkMove(); 
uint8_t checkCrash(); // TODO add this
uint8_t checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness); // TODO add this
void executeNextAction();
void setSpeed(int8_t s);

void getReverse(Action action, Action * reverse);

void setTargetDegrees(int16_t newTarget);


void beginAutomaticMode(); // TODO add this
void stopAutomaticMode(); // TODO add this
void resetAutomaticMode(); // TODO add this
void resetClock(); // TODO add this


extern volatile ActionList * actionList;
extern volatile uint8_t currentAction;

extern volatile uint16_t targetDegrees;
extern volatile uint16_t targetDistance;

extern volatile uint16_t targetMillis;
extern volatile uint16_t currentMillis;
extern volatile uint16_t overflowCount;

extern volatile int8_t speed;
extern volatile int8_t defaultSpeed;

extern volatile ActionList normalActionList;
extern volatile ActionList routeFindingActionList;

#include "move_functions.h"
#include "route_finding_functions.h"

#endif // AUTOMATIC_MODE_H
