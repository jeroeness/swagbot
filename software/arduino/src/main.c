#ifndef F_CPU
#ifdef __AVR_ATmega2560__
#define F_CPU 8000000UL
#endif // __AVR_ATmega2560__
#ifdef __AVR_ATmega328P__
#define F_CPU 16000000UL
#endif // __AVR_ATmega328P__
#endif // F_CPU

#include <Arduino.h>
#include "lib/swagbotlib.h"
#include "modules/communication.h"
#include "modules/mode_manager.h"

void setup() {

	// Invoke initialize for all modules
	initCommunication();
	initModeManager();

}

void loop() {

	// Invoke update for all modules
	updateCommunication();

}
