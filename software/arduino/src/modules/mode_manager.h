#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include <avr/io.h>
#include <stdio.h>

enum SteeringMode {
	manual,
	automatic
};

void setSteeringMode(SteeringMode);
void initModeManager();
void inputKeyPress(uint8_t key);
void inputKeyRelease(uint8_t key);
void inputKeyDown(uint8_t key);

void handleKeyPressManualMode (uint8_t key);
void handleKeyReleaseManualMode (uint8_t key);
void handleKeyPressAutomaticMode (uint8_t key);
void handleKeyReleaseAutomaticMode (uint8_t key);

#endif // MODE_MANAGER_H
