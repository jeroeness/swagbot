#ifndef MOTORHEADER
#define MOTORHEADER

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*---------------- MOTOR functions ----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

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

#endif

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
	int8_t motorLeft;
	int8_t motorRight;
	int16_t ultrasonic;
};

struct ID{
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};

extern struct ID instructionData;
extern struct SD sensorData;

union USD {
	struct SD s;
	uint8_t sendData[sizeof(sensorData)];
};

union UID {
	struct ID i;
	uint8_t receiveData[sizeof(instructionData)];
};


void initSensors();

void setLed(uint8_t uLed, uint8_t uOn);

void readBumperL();
void readBumperR();
void readCompass();
void readSensors();


#endif
