

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

/**	Makes the RP6 motors rotate at speedL/speedR
 *
 *	@param speedL 		the speed of the left motor (min: -100, max: 100)  negative for backwards, positive for forwards.
 *	@param speedR 		the speed of the right motor (min: -100, max: 100)  negative for backwards, positive for forwards.
 * 	@return 			1 if successfull, 0 if wrong speed
 */
int moveMotors(int8_t speedL, int8_t speedR);

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
struct SD{
	uint8_t bumperRight:1;
	uint8_t bumperLeft:1;
	uint16_t compassDegrees;
	int16_t ultrasonic;
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};


extern struct SD sensorData;

union USD {
	struct SD s;
	uint8_t sendData[sizeof(sensorData)];
};


void initSensors();

void setLed(uint8_t uLed, uint8_t uOn);

void readBumperL();
void readBumperR();
void readSensors();


#endif
