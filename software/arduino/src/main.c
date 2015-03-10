#ifndef F_CPU
#ifdef __AVR_ATmega2560__
#define F_CPU 8000000UL
#endif // __AVR_ATmega2560__
#ifdef __AVR_ATmega328P__
#define F_CPU 16000000UL
#endif // __AVR_ATmega328P__
#endif // F_CPU

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <stdlib.h>

#include "lib/swagbotlib.h"
#include "lib/serial.h"
#include "modules/communication.h"
#include "modules/mode_manager.h"
#include "modules/motor.h"
#include "modules/automatic_mode.h"
#include "modules/i2c_lib.h"
#include "lib/sensor.h"

struct ID instructionData;
struct SD sensorData;

int main(void){
	cli();

	initAutomaticMode();
	initCommunication();
	i2c_init(1);

	sei();

	setSteeringMode(automatic);
	resetAutomaticMode();

	i2c_write_cmd_wrap();

	while(1){
		updateAutomaticMode();
		updateCommunication();
	}

	return 1998;
}
