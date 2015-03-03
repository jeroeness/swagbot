

// MOTOR functions:

/**	Make the RP6 motors rotate in dirL/dir/R at speedL/speedR
*
*	@param dirL the direction of the left motor (-1 for backwards, +1 for forward)
*	@param dirR the direction of the right motor (-1 for backwards, +1 for forward)
*	@param speedL the speed of the left motor (min: 0, max: 200)
*	@param speedR the speed of the right motor (min: 0, max: 200)
* 	@return 1 if successfull, 0 if wrong speed
*/
int moveMotors(int dirL,int dirR,int speedL,int speedR);

/**	Make the RP6 drive and turn
 * 
 *	@param speed	the speed at which the RP6 will drive 
 * 	@param bend	the amount the RP6 should bend off when driving (bend < 0: The RP6 will bend left, bend > 0: The RP6 will bend right, bend == 0: The RP6 won't turn) 
 */
void drive(int speed, int bend, int direction);
void motorTest();
void stop();
void turn(int speed);

void initMotor();
