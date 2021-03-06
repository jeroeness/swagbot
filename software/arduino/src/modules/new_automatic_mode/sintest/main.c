#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>

#define PI 3.1415926535897932384626433832795

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define radians(deg) ((deg)*DEG_TO_RAD)

#define RAD_TO_DEG 57.295779513082320876798154814105
#define degrees(rad) ((rad)*RAD_TO_DEG)


#define OUTSIDE_MARGIN_RP6 10


void findRoute(int16_t angleToPoint, int16_t turnedAngle, uint16_t distance);
double sind(float a);
double cosd(float a);
double tand(float a);
double atand(float a);

volatile uint8_t previousDirection;
volatile float totalDeviation;
volatile float desiredProgression;

int main() {
	system("clear");
	printf("============= Program Start =============\n");
	findRoute(45, -45, 40);
	
	

	printf("============== Program end ==============\n");
	return 0;
}

void findRoute(int16_t angleToPoint, int16_t turnedAngle, uint16_t distance) {
	printf("\n------------- Finding route -------------\n");
	float a, a1, a2, s, s1, dv, dv1, p; //, a3
	uint8_t direction = (angleToPoint < 0) ? -1 : 1;

	if (previousDirection == 0) {
		previousDirection = direction;
	}

	a1 = (int16_t) abs(angleToPoint);
	
	angleToPoint = 0;
	s1 = distance;

	if (direction == previousDirection) {
		p = s1 * cosd(a1);				// progression
		dv1 = p * tand(a1);				// deviation part 1
	} else {
		p = s1 * sind(a1);
		dv1 = p / tand(a1);				// deviation part 1
	}
	printf("p=%f\n", p);
	printf("cos=%f\n", cosd(180));
	dv = dv1 + OUTSIDE_MARGIN_RP6; 	// deviation to match size RP6

	if (direction == previousDirection) {
		a = atand(dv / p);				// the total angle. // TODO convert atann to degrees
	} else {
		a = atand(p / dv);				// the total angle.
	}
	a2 = a - turnedAngle;					// the angle to turn for margin
	//a3 = a - turnedAngle;			// the angle that has to be turned to reach total angle // TODO controleer deze shit man fuck me.

	if ((totalDeviation < 0)*direction && (totalDeviation + dv > 0)*direction) { // TODO be weary of >
		dv = abs(totalDeviation);
	}
		
	if (direction == previousDirection) {
		s = dv / sind(a);				// the distance that has to be traveled to arrive at the point // TODO check deze sheis
	} else {
		s = dv / cosd(a);				// the distance that has to be traveled to arrive at the point
	}

	if (totalDeviation == -1 * dv) { 
		if (direction == previousDirection) {
			p = s * cosd(a);				// progression
		} else {
			p = s * sind(a);
		}
	}

	totalDeviation += dv * direction;			// increment the totalDeviation to be able to find a way back to the original path (dv is negative if the turn was to the left.)

	desiredProgression -= p;

	previousDirection = direction;

	printf("a = %f\n", a);
	printf("a1 = %f\n", a1);
	printf("a2 = %f\n", a2);
	printf("s = %f\n", s);
	printf("s1 = %f\n", s1);
	printf("dv = %f\n", dv);
	printf("dv1 = %f\n", dv1);
	printf("p = %f\n", p);
	printf("direction = %d\n", direction);
	printf("totalDeviation = %f\n", totalDeviation);
}


double sind(float a) {
	return sin(radians((double) a));
}

double cosd(float a) {
	return cos(radians((double) a));
}

double tand(float a) {
	return tan(radians((double) a));
}

double atand(float a) {
	return atan(((double) a)) * 180 / PI;
}



