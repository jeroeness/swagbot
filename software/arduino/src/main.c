#include <Arduino.h>
#include "lib/swagbotlib.h"
#include "modules/communication.h"

void setup() {

	// Invoke initialize for all modules
	initCommunication();

}

void loop() {

	// Invoke update for all modules
	updateCommunication();

}
