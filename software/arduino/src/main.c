#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h>



#include "lib/swagbotlib.h"
#include "modules/communication.h"
#include "modules/mode_manager.h"
#include "modules/motor.h"

#ifndef F_CPU
#ifdef __AVR_ATmega2560__
#define F_CPU 8000000UL
#endif // __AVR_ATmega2560__
#ifdef __AVR_ATmega328P__
#define F_CPU 16000000UL
#endif // __AVR_ATmega328P__
#endif // F_CPU

#ifdef __cplusplus
extern "C"{
#endif

void setup() {

	sei();

	// Invoke initialize for all modules
	initCommunication();
	//initModeManager();
	//initMotor();
}

void loop() {

	// Invoke update for all modules
	updateCommunication();

}

#ifdef __cplusplus
}
#endif
