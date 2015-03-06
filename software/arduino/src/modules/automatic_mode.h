#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*----------- Automatic Mode functions ------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void initAutomaticMode();
void updateAutomaticMode();
void checkCrash();
void executeNextAction();
void checkTurn();
void checkMove();
int checkFuzzy(int16_t value1, int16_t value2, int16_t fuzzyness);
void turnByDegrees(int16_t degrees);
void turnToDegrees(int16_t degrees);
void turnFor(int16_t milliseconds);
void moveDistance(int16_t distance);
void moveToDistance(int16_t distance);
inline void resetClock();
void moveFor(int16_t milliseconds, int8_t direction);
void initTimer();

inline void setSpeed(int8_t s);
inline void setDirection(int8_t d);

void beginAutomaticMode();
void stopAutomaticMode();

#endif // AUTOMATIC_MODE_H
