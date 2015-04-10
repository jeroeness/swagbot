// mode_manager.h

#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include "../globalincsanddefs.h"

enum SteeringMode {
	manual,
	automatic
};

void setSteeringMode(enum SteeringMode);
void initModeManager();
void inputKeyPress(uint8_t key);
void inputKeyRelease(uint8_t key);
void inputKeyDown(uint8_t key);

void handleKeyPressManualMode (uint8_t key);
void handleKeyReleaseManualMode (uint8_t key);
void handleKeyPressAutomaticMode (uint8_t key);
void handleKeyReleaseAutomaticMode (uint8_t key);

void updateManualMode();

void handleKeyDownManualMode (uint8_t key);


void updateModeManager();

#endif // MODE_MANAGER_H
