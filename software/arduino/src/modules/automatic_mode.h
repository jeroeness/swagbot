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
void moveDistance(int16_t distance);
void moveToDistance(int16_t distance);



#endif // AUTOMATIC_MODE_H
