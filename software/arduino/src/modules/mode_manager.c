#include "mode_manager.h"
#include "manual_mode.h"
#include "automatic_mode.h"

SteeringMode steeringMode;

void initModeManager() {
	steeringMode = manual;
}

void setSteeringMode(SteeringMode s) {
	if (steeringMode != s) {
		if (steeringMode == manual) {
			stopManualMode();
			beginAutomaticMode();
		} else {
			stopAutomaticMode();
			beginManualMode();
		}
	}
	steeringMode = s;
}

void inputKeyDown (uint8_t key) {
	//TODO
	if (steeringMode == automatic) {
        //handleKeyDownAutomaticMode(key);
	} else {
		//handleKeyDownManualMode(key);
	}
}

void inputKeyPress(uint8_t key) {
	if (steeringMode == automatic) {
        	setSteeringMode(manual);
        	handleKeyPressManualMode(key);
	} else {
		handleKeyPressManualMode(key);
	}
}

void inputKeyRelease(uint8_t key) {
	if (steeringMode == automatic) {
        handleKeyReleaseAutomaticMode(key);
	} else {
		handleKeyReleaseManualMode(key);
	}
}

void handleKeyReleaseAutomaticMode (uint8_t key) {
	//TODO this method is not yet implemented
}


void handleKeyPressManualMode (uint8_t key) {
	switch (key) {
		case 'w':
			inputForward();
			break;
		case 'a':
			inputLeft();
			break;
		case 's':
			inputBackward();
			break;
		case 'd':
			inputRight();
			break;
	}
}

void handleKeyReleaseManualMode (uint8_t key) {
	switch (key) {
		case 'w':
		case 'a':
		case 's':
		case 'd':
			stopManualMode();
			break;
	}
}
