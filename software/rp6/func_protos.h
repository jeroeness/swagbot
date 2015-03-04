

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*---------------- MOTOR functions ----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/**	Makes the RP6 drive and deflect from it's current path if necessary.
 * 
 *	@param speed		the speed at which the RP6 will drive 
 * 	@param deflection	the amount the RP6 should deflect when driving (deflect < 0: The RP6 will deflect to the left, deflect > 0: The RP6 will deflect to the right, deflect == 0: The RP6 won't deflect) 
 */
void drive(int speed, int bend, int direction);

/**	Makes the RP6 turn around it's own axis.
 * 
 *	@param speed		the speed at which the RP6 will turn 
 */
void turn(int speed);

/**	Makes both of the RP6 motors stop with everything they're doing.
 */
void stop();

/**	This function initializes everything that is necessary for the motor functions to work.
 * 
 *	@param speed		the speed at which the RP6 will turn 
 */
void initMotor();

/**	Makes the RP6 motors rotate in dirL/dir/R at speedL/speedR
 *
 *	@param dirL 		the direction of the left motor (-1 for backwards, +1 for forward)
 *	@param dirR 		the direction of the right motor (-1 for backwards, +1 for forward)
 *	@param speedL 		the speed of the left motor (min: 0, max: 200)
 *	@param speedR 		the speed of the right motor (min: 0, max: 200)
 * 	@return 			1 if successfull, 0 if wrong speed
 */
int moveMotors(int dirL,int dirR,int speedL,int speedR);

/**	A simple function to test the motor functions.
 */
void motorTest();



#ifndef SENSORHEADER
#define SENSORHEADER
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*---------------- SENSOR functions ----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
//description comes later because of debugging state.

//SD stands for SensorData
struct sD{
	uint8_t bumperRight:1;
	uint8_t bumperLeft:1;
	int16_t ultrasoonDistance;
};

extern struct sD sensorData;

union uSD {
	struct sD s;
	uint8_t sendData[sizeof(sensorData)];
};


void initSensors();

void setLed(uint8_t uLed, uint8_t uOn);

void readBumperL();
void readBumperR();
void readSensors();


#endif
