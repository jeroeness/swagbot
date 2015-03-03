#define F_CPU 8000000 //Base: 8.00MHz - DO NOT CHANGE! // CPU works @ 8.0Mhz;

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> // I/O Port definitions
#include <avr/interrupt.h> // Interrupt macros (e.g. cli(), sei())

#include "func_protos.h"

struct sD sensorData;

void loadSensors(){
	sensorData.bumperLeft = 1;
	sensorData.bumperRight = 0;
	sensorData.ultrasoonDistance = 1200;
}




