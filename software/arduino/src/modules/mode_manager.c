// mode_manager.c

#include "../globalincsanddefs.h"

enum SteeringMode steeringMode;

void initModeManager() {
	steeringMode = manual;
}

void setSteeringMode(enum SteeringMode s) {
	if (steeringMode != s) {
		if (steeringMode == manual) {
			stopManualMode();
			beginAutomaticMode();
		} else {
			stopAutomaticMode();
			beginManualMode();
		}
	}

	/*
	if(steeringMode == manual){
		sensorData.sensorStruct.steeringMode = 1;
	}else if(steeringMode == automatic){
		sensorData.sensorStruct.steeringMode = 2;
	}*/

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
        //TODO key press automatic
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

void updateModeManager () {
    if (steeringMode == manual) {
        //TODO update manual mode
    } else {
        updateAutomaticMode();
    }
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
    alterCourse();
}

void handleKeyReleaseManualMode (uint8_t key) {
	switch (key) {
		case 'w':
			stopForward();
			break;
		case 'a':
			stopLeft();
			break;
		case 's':
			stopBackward();
			break;
		case 'd':
			stopright();
			break;
	}
    alterCourse();
}
