#include "automatic_mode.h"

volatile ActionList * actionList;
void (*functionList[7])(Action *);

extern volatile uint8_t currentAction;

extern volatile uint16_t targetDegrees;
extern volatile uint16_t targetDistance;

extern volatile uint16_t targetMillis;
extern volatile uint16_t currentMillis;
extern volatile uint16_t overflowCount;

extern volatile int8_t speed;
extern volatile int8_t defaultSpeed;

int main() {
	initActionList(2);

	addToActionList(F_TURN_BY_DEGREES, 50, 50);
	addToActionList(2, 50, -50);
	addToActionList(3, 100, 0);
	addToActionList(4, 50, 0);
	addToActionList(5, 50, 50);
	addToActionList(6, 50, -80);
	addToActionList(7, 10, 0);
	addToActionList(8, 50, 50);
	addToActionList(9, 50, 50);

	Action tmpAction = actionList->list[5];

	initFunctionList();

	turnByDegrees(&(actionList->list[0]));

//	printf("%d\n", currentAction);
//	printf("%d\n", targetDegrees);

	reverseActionTest();

//	scanf("\n");

//	destroyActionList(actionList);

	return 0;
}

void reverseActionTest() {
	Action a1, a2, a3;

	a1.functionIndex = F_TURN_BY_DEGREES;
	a1.target = 10;
	a1.speed = 50;
	functionList[F_TURN_BY_DEGREES](&a1);

	a2.functionIndex = F_TURN_FOR;
	a2.target = 20;
	a2.speed = 60;
	functionList[F_TURN_FOR](&a2);

	a3.functionIndex = F_TURN_TO_DEGREES;
	a3.target = 30;
	a3.speed = 70;
	functionList[F_TURN_TO_DEGREES](&a3);

	printf("----------------------------\n");
	printAction(a1);
	printAction(getReverse(a1));
	printf("----------------------------\n");
	printAction(a2);
	printAction(getReverse(a2));
	printf("----------------------------\n");
	printAction(a3);
	printAction(getReverse(a3));
	printf("----------------------------\n");

}

void initActionList(uint8_t size) {
	ActionList newActionList;
	actionList = &newActionList;

	actionList->list = (Action*) malloc(size * sizeof(Action));
	actionList->size = size;
	actionList->nextAction = 0;
	actionList->usedSize = 0;

	fillEmptyActionList();
}

void initFunctionList() {
	functionList[0] = turnByDegrees;
	functionList[1] = turnToDegrees;
	functionList[2] = turnFor;
	functionList[3] = moveDistance;
	functionList[4] = moveToDistance;
	functionList[5] = moveFor;
	functionList[6] = waitFor;

}

void fillEmptyActionList() {
	for (uint8_t i=actionList->usedSize; i<actionList->size; i++) {
		Action* action = &(actionList->list[i]);
		action->functionIndex = 0;
		action->target = 0;
		action->speed = 0;
	}
}

void addToActionList(uint8_t functionIndex, int16_t target, int16_t speed) {
	if (actionList->usedSize >= actionList->size) {
		doubleActionList();
	}

	Action * newAction = &(actionList->list[actionList->usedSize++]);
	newAction->functionIndex = functionIndex;
	newAction->target = target;
	newAction->speed = speed;
}

void addReverseAction(Action action) {
	//addToActionList(action.action, action.)
}

void doubleActionList() {
	printf("aww yiss, doubling zee list\n");

	Action * oldList = actionList->list;

	actionList->size = actionList->size * 2;

	actionList->list = (Action*) malloc(actionList->size * sizeof(Action));

	for(uint8_t i=0; i<actionList->usedSize; i++) {
		*(actionList->list + i) = *(oldList + i);
	}

	fillEmptyActionList();
}

void destroyActionList(ActionList * oldActionList) {
	free(oldActionList->list);
}

void testAction(uint8_t action, uint16_t arg1, uint16_t arg2) {

}


void updateAutomaticMode() {
	//checkCrash();
	if (findingRoute) {
		if (currentAction == ACTION_IDLE && checkFuzzy(totalDeviation, 0, 5)) { // TODO change 5 to correct value
			// TODO return original actionList
			findingRoute = 0;
			routeFindingDepth = 0; // TODO combine this shit man

			// TODO add action to complete progression

			currentAction = ACTION_IDLE;
		} else {
			// TODO find the new angle and continue route finding.
			
		}
	} else {
		checkObstacle();
	}

	switch (currentAction) {
		case ACTION_TURN:
		case ACTION_FINDING_ANGLE:
			//checkTurn();
			break;
		case ACTION_MOVE:
			//checkMove();
			break;
		case ACTION_IDLE:
			//executeNextAction();
			break;
	}
}

void checkTurn() {
	if (checkFuzzy(targetDegrees, sensorData.compassDegrees, TURN_MARGIN)) {
		stop();
		if (currentAction == ACTION_FINDING_ANGLE) {
			findAngleToPoint();
		} else {
			currentAction = ACTION_IDLE;
		}
	} else {
		turn(speed);
	}
}

void executeNextAction() {
	if (actionList->nextAction >= actionList->usedSize)
		actionList->nextAction = 0;

	Action next = actionList->list[actionList->nextAction++];

	setSpeed(next.speed);

	functionList[next.functionIndex](&next);
}

void setSpeed(int8_t s) {
	speed = (s == 0) ? defaultSpeed : s;
}

Action getReverse(Action action) {
	Action reverse;

	reverse.functionIndex = action.functionIndex;

	if (action.functionIndex == F_TURN_FOR || action.functionIndex == F_MOVE_FOR) {
		reverse.target = action.target;
		reverse.speed = -1 * action.speed;
	} else {
		reverse.target = action.origin;
		reverse.speed = action.speed;
	}

	return reverse;
}

void printAction(Action action) {
	printf("functionIndex = %d\n", action.functionIndex);
	printf("target = %d\n", action.target);
	printf("speed = %d\n", action.speed);
	printf("origin = %d\n\n", action.origin);
}

void setTargetDegrees(int16_t newTarget) {
	if (newTarget > 360) {
		newTarget -= 360;
	} else if (newTarget < 0) {
		newTarget += 360;
	}
	targetDegrees = newTarget;
}

void intsr() {
	if ((++overflowCount) == 2) {
		overflowCount = 0;
		if (targetMillis != 0 && checkFuzzy(targetMillis, ++currentMillis, TIME_MARGIN)) {
			stop();
			resetClock();
			if (currentAction == ACTION_WAIT) {
				currentAction = ACTION_IDLE;
			} else {

			}
		}
	}
}