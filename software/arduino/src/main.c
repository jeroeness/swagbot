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
#include <util/delay.h>
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

	PORTD = 3;

	DDRB = 1 << 7;

	i2c_init(0xA8);
	initAutomaticMode();
	initCommunication();

	sei();

	setSteeringMode(automatic);
	resetAutomaticMode();

	serialPrintSynchronous("begin!");
	moveMotors(50,50);
	i2c_write_cmd_wrap();
	serialPrintSynchronous("end!");

	while(1){
		PORTB &= ~(1 << 7);
		//i2c_write_cmd_wrap();
 		//updateAutomaticMode();
		moveMotors(50,50);
		updateCommunication();
	}

	return 1998;
}
