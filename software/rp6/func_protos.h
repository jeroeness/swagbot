

// MOTOR functions:

/** Make the RP6 motors rotate in dirL/dir/R at speedL/speedR
*
*	@param dirL the direction of the left motor
*	@param dirR the direction of the right motor
*	@param speedL the speed of the left motor
*	@param speedR the speed of the right motor
*/
void moveMotors(int dirL,int dirR,int speedL,int speedR);

void drive(int speed, int bend, int direction);
void motorTest();
void stop();

void initMotor();
