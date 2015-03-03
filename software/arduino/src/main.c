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
