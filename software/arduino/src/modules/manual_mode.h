//manual_mode.h

#ifndef MANUAL_MODE_H
#define MANUAL_MODE_H

#include "../globalincsanddefs.h"

void inputRight();
void inputLeft();
void inputBackward();
void inputForward();

void stopForward();
void stopLeft();
void stopBackward();
void stopright();

void stopManualMode();
void beginManualMode();

void manualModecheckCollision();

void alterCourse ();

#endif // MANUAL_MODE_H
