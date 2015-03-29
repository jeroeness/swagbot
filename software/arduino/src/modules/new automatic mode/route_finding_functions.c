#include "automatic_mode.h"
#include <math.h>


extern volatile uint8_t currentAction;

extern volatile uint16_t targetDegrees;
extern volatile uint16_t targetDistance;

extern volatile uint16_t targetMillis;
extern volatile uint16_t currentMillis;

extern volatile int8_t speed;

extern struct SD sensorData; 

extern volatile uint8_t findingAngleToPoint;
extern volatile uint8_t findingRoute;

uint8_t previousDirection; // TODO implement the use of this.

uint8_t routeFindingDepth;				// TODO combine with findingRoute

int16_t totalDeviation;
int16_t desiredProgression;

ActionList * backupActionList;

uint8_t checkObstacle() {
	if (sensorData.ultrasonic > MIN_DISTANCE)
		return 0;

	desiredProgression = targetMillis - currentMillis;

	backupActionList = actionList;
	ActionList newActionList;
	actionList = &newActionList;

	routeFindingDepth = 1;

	findAngleToPoint();
}

uint8_t findRoute(int16_t angleToPoint, int16_t turnedAngle, uint16_t distance) {
	int16_t a, a1, a2, a3, s, s1, dv, dv1, p;
	uint8_t direction = (angleToPoint < 0) ? -1 : 1; 

	a1 = abs(angleToPoint);
	angleToPoint = 0;
	s1 = convertToTime(distance);

	if (direction == previousDirection) {
		p = s1 * cos(a1);				// progression
		dv1 = p * tan(a1);				// deviation part 1
	} else {
		p = s1 * sin(a1);
		dv1 = p / tan(a1);				// deviation part 1
	}

	dv = dv1 + OUTSIDE_MARGIN_RP6; 	// deviation to match size RP6

	if (direction == previousDirection) {
		a = atan(dv / p);				// the total angle. // TODO implement different direction
	} else {
		a = atan(p / dv);				// the total angle. // TODO implement different direction
	}
	a2 = a - a1;					// the angle to turn for margin
	a3 = a - turnedAngle;			// the angle that has to be turned to reach total angle
		
	if ((totalDeviation + dv) * direction > 0) { // TODO be weary of >
		dv = abs(totalDeviation);
	}

	if (direction == previousDirection) {
		s = dv / sin(a);				// the distance that has to be traveled to arrive at the point
	} else {
		s = dv / cos(a);				// the distance that has to be traveled to arrive at the point
	}

	if (abs(totalDeviation) == abs(dv)) { 
		if (direction == previousDirection) {
			p = s * cos(a);				// progression
		} else {
			p = s * sin(a);
		}
	}

	totalDeviation += dv * direction;			// increment the totalDeviation to be able to find a way back to the original path (dv is negative if the turn was to the left.)

	desiredProgression -= p;

	currentAction = ACTION_IDLE;

	addToActionList(F_TURN_BY_DEGREES, direction * a2), 0); 	// add action turn(a2)
	addToActionList(F_MOVE_FOR, s, 0);
	addToActionList(F_TURN_BY_DEGREES, direction * a, 0);
}

void findAngleToPoint() {
	static int16_t angleToPoint, previousAngleToPoint;
	static int16_t previousAngle;
	static uint8_t previousDistance;
	static uint8_t checkingRight;
	static uint8_t firstCall = 1;

	int16_t newAngle;

	if (firstCall) {
		firstCall = angleToPoint = previousAngleToPoint = previousAngle = previousDistance = 0;
		currentAction = ACTION_FINDING_ANGLE;

		if (routeFindingDepth > 1) {
			if (totalDeviation > 0) {
				checkingRight = 1;
			}
		}
	}


	uint16_t testingAngle = 90 ; // TODO fix this nu check hij zowel in lagere als hogere diepte de volledige 90 graden hoek.

	if ((previousDistance != 0 && sensorData.ultrasonic - previousDistance > 10) || (uint8_t angleLimit = (angleToPoint >= testingAngle))) { // indicates end of finding the angle (either found or none-existent) //TODO gauge 10
		if (checkingRight || routeFindingDepth > 0) { // done with both sides or it's only necessary to check one side
			if (angleLimit) {
				// TODO implement angle limit
				// REVERSE ROUTE FINDING ACTIONS AND LAST NORMAL ACTION
			} else {
				findRoute((angleToPoint < previousAngleToPoint) ? angleToPoint : previousAngleToPoint, previousDistance); // call find route with the smallest angle
			}

			firstCall = 1;
			return;
		} else {
			checkingRight = 1;
			previousAngleToPoint = angleToPoint;

			newAngle = -1 * previousAngleToPoint;
		}
	} else {
		previousDistance = sensorData.ultrasonic;

		newAngle = 5 * ((checkingRight) ? 1 : -1); // TODO gauge this shit // if checking right the angle should be positive, otherwise it should be negative
		angleToPoint += newAngle;
	}


	setTargetDegrees(sensorData.compassDegrees + newAngle);
}

uint8_t foundObstacle() {
	return (sensorData.ultrasonic < MIN_DISTANCE + 10);
}

int16_t convertToTime(int16_t ultrasonic) {
	// TODO implement and gauge

	return ultrasonic;
}
