
#include <stdio.h>
//#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "sensor.h"

struct SD sensorData;


// negative deflection = left; positive deflection = right
void drive(int8_t speed, int8_t deflection) {
	uint8_t direction;
	if (speed < 0)
		direction = -1;
	else
		direction = 1;

	int speedL = direction * speed;
	int speedR = direction * speed;
	
	
  
	if (deflection > 0) {
	   speedR -= deflection; 
	} else {
	   speedL += deflection; 
	}
	moveMotors(direction * speedL, direction * speedR);
}

void turn(int8_t speed) {
	moveMotors(speed, -speed);
}

void stop() {
	moveMotors(0, 0);
}

//dirL, dirR direction of left and right motor. 1=forward, -1=backward
//speedL, speedR movement speed of left and right motor. 0 <= speed <= 200
int moveMotors(int8_t speedL, int8_t speedR){
	if(speedR < -100 || speedR > 100)
	    return 0;
	if(speedL < -100 || speedL > 100)
	    return 0;

	sensorData.motorLeft = speedL;
	sensorData.motorRight = speedR;
	
	return 1;
}
