#include "../globalincsanddefs.h"

volatile ActionList * actionList;

volatile uint8_t currentAction;

volatile uint16_t targetDegrees = 0;
volatile uint16_t targetDistance = 0;

volatile uint16_t targetMillis = 0;
volatile uint16_t currentMillis = 0;
volatile uint16_t overflowCount = 0;


volatile int8_t speed = 0;
volatile int8_t defaultSpeed = 100;

volatile ActionList normalActionList;
volatile ActionList routeFindingActionList;

void (*functionList[7])(Action *);


void initAutomaticMode() {
	initFunctionList();
	initActionList(2);
	initTimer0();

	currentAction = ACTION_IDLE;

	addToActionList(F_TURN_FOR, 50, 50);
	addToActionList(F_MOVE_FOR, 100, 200);
}

void updateAutomaticMode() {
	checkCrash();
	
	
	if (routeFindingDepth > 0) {
		if (currentAction == ACTION_IDLE && checkFuzzy(totalDeviation, 0, 5)) { // TODO gauge 5 to correct value
			// TODO return original actionList
			if(actionListCompleted())
				finishRouteFinding();
			else 
				endRouteFinding();
		} else {
			// TODO find the new angle and continue route finding.
			findAngleToPoint();
		}
	} else {
		checkObstacle();
	}
	

	switch (currentAction) {
		case ACTION_TURN:
		case ACTION_FINDING_ANGLE:
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
	actionList = &normalActionList;

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

void initTimer0() {
	TIMSK0 = (1 << TOIE0);
	TCCR0B = (1 << CS02) | (1 << CS00); // prescaler 1024; fcpu 16000000 = 61 overflows per second
}

void fillEmptyActionList() {
	for (uint8_t i=actionList->usedSize; i<actionList->size; i++) {
		Action* action = &(actionList->list[i]);
		action->functionIndex = 0;
		action->target = 0;
		action->speed = 0;
	}
}

void clearActionList() {
	free(actionList->list);

	actionList->list = (Action*) malloc(actionList->size * sizeof(Action));
	actionList->nextAction = 0;
	actionList->usedSize = 0;

	fillEmptyActionList();
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
	// TODO implement this
}

void doubleActionList() {
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

uint8_t actionListCompleted() {
	return (actionList->nextAction >= actionList->usedSize);
}


void checkTurn() {
	static uint8_t turning = 0;

	if (checkFuzzy(targetDegrees, sensorData.sensorStruct.compassDegrees, TURN_MARGIN)) {
		turning = 0;
		stop();
		if (currentAction == ACTION_FINDING_ANGLE) {
			findAngleToPoint();
		} else {
			currentAction = ACTION_IDLE;
		}
	} else if (!turning) {
		turning = 1;
		turn(speed); // TODO do deze shit niet elke keer man, wtf.
	}
}

void checkMove() {
	if (checkFuzzy(targetDistance, sensorData.sensorStruct.ultrasonic, MOVE_MARGIN)) {
		stop();
		currentAction = ACTION_IDLE;
	} else {
		if (targetDistance < sensorData.sensorStruct.ultrasonic) {
			drive(speed, 0);
		} else {
			drive(-1 * speed, 0);
		}
	}
}

uint8_t checkCrash() {
		// TODO implement code
	return 0;
}

uint8_t checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness) {
	return (value1 < value2 + fuzzyness && value1 > value2 - fuzzyness);
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
	// TODO implement waitFor reverse
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

void setTargetDegrees(int16_t newTarget) {
	if (newTarget > 360) {
		newTarget -= 360;
	} else if (newTarget < 0) {
		newTarget += 360;
	}
	targetDegrees = newTarget;
}


void resetClock() {
	currentMillis = 0;
	overflowCount = 0;
}

void resetAutomaticMode() {
	actionList->nextAction = 0;
	currentAction = ACTION_IDLE;
}

void beginAutomaticMode(){
	resetAutomaticMode();
}

void stopAutomaticMode(){
	stop();
}



// ISR

ISR(TIMER0_OVF_vect) {
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
