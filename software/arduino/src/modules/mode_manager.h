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
void inputKey(int8_t key);

void handleInputManualMode (int8_t key);
void handleInputAutomaticMode (int8_t key);

#endif // MODE_MANAGER_H
