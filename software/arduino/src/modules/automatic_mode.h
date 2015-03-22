// automatic_mode.h

#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*----------- Automatic Mode functions ------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#include "../globalincsanddefs.h"

#define ACTION_IDLE 		0// todo: enum?
#define ACTION_TURN 		1
#define ACTION_TURN_TO 		2
#define ACTION_TURN_FOR		3
#define ACTION_MOVE 		4
#define ACTION_MOVE_TO 		5
#define ACTION_MOVE_FOR		6
#define ACTION_WAIT 		7
#define ACTION_SET_SPEED 	8

void initAutomaticMode();
void updateAutomaticMode();
void checkCrash();
void executeNextAction();
void checkTurn();
void checkMove();
int checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness);
void turnByDegrees(int16_t degrees);
void turnToDegrees(int16_t degrees);
void turnFor(int16_t milliseconds);
void moveDistance(int16_t distance);
void moveToDistance(int16_t distance);
void resetClock();
void moveFor(int16_t milliseconds);
void initTimer0();
void resetSpeed();
void setDefaultSpeed(int8_t s);
void setSpeed(int8_t s);
void setDirection(int8_t d);
void initActionList(uint8_t size);
void addToActionList(int16_t action, int16_t argument, int16_t tempSpeed);
void beginAutomaticMode();
void stopAutomaticMode();
void resetAutomaticMode();
void resetClock();


typedef struct {
	uint8_t action;
	int16_t argument;
	int16_t tempSpeed;	
} Action;

typedef struct {
	Action* list;
	uint8_t size;
	uint8_t nextAction;
	uint8_t usedSize;
} ActionList;

#endif // AUTOMATIC_MODE_H
