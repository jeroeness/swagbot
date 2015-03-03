#include "mode_manager.h"
#include "manual_mode.h"

SteeringMode steeringMode;

void initModeManager() {
	steeringMode = manual;
}

void setSteeringMode(SteeringMode s) {
	steeringMode = s;
}

void inputKey(int8_t key) {
	if (steeringMode == automatic) {
        handleInputAutomaticMode(key);
	} else {
		handleInputManualMode(key);
	}
}

void handleInputAutomaticMode (int8_t key) {
	//TODO this method is not yet implemented
}

void handleInputManualMode (int8_t key) {
	//TODO handle keypresses
	switch (key) {
		case 'w':
			inputForward();
			break;
		case 'a':
			inputBackward();
			break;
		case 's':
			inputLeft();
			break;
		case 'd':
			inputRight();
			break;
	}
}
