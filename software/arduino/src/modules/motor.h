// motor.h

#ifndef MOTOR_H
#define MOTOR_H

#include "../globalincsanddefs.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*---------------- MOTOR functions ----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/**	Makes the RP6 drive and deflect from it's current path if necessary.
 * 
 *	@param speed		the speed at which the RP6 will drive 
 * 	@param deflection	the amount the RP6 should deflect when driving (deflect < 0: The RP6 will deflect to the left, deflect > 0: The RP6 will deflect to the right, deflect == 0: The RP6 won't deflect) 
 */
void drive(int8_t speed, int8_t bend);

/**	Makes the RP6 turn around it's own axis.
 * 
 *	@param speed		the speed at which the RP6 will turn 
 */
void turn(int8_t speed);

/**	Makes both of the RP6 motors stop with everything they're doing.
 */
void stop();

/**	Set the motor variables to be sent to the RP6 by I2C
 *
 *	@param speedL 		the speed of the left motor (min: -100, max: 100)  negative for backwards, positive for forwards.
 *	@param speedR 		the speed of the right motor (min: -100, max: 100)  negative for backwards, positive for forwards.
 * 	@return 			1 if successfull, 0 if wrong speed
 */
int moveMotors(int8_t speedL, int8_t speedR);

#endif // MOTOR_H
