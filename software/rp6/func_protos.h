//func_protos.h
#define F_CPU 8000000 //Base: 8.00MHz - DO NOT CHANGE! // CPU works @ 8.0Mhz;

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> // I/O Port definitions
#include <avr/interrupt.h> // Interrupt macros (e.g. cli(), sei())


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
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t batteryPercentage;
	uint8_t ultrasonic;
	uint8_t compassDegrees;
};

struct ID{
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};

struct SD sensorStruct;
struct ID instructionstruct;

union USD {
	struct SD sensorStruct;
	uint8_t sensorArray[sizeof(sensorStruct)];
};

union UID {
	struct ID instructionstruct;
	uint8_t instructionArray[sizeof(instructionstruct)];
};

union UID instructionData;
union USD sensorData;

void initSensors();

void parseInstruction(void);

void setLed(uint8_t uLed, uint8_t uOn);

void readBumperL();
void readBumperR();
void readCompass();
void readSensors();


#endif

#ifndef I2CLIBHEADER
#define I2CLIBHEADER
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*----------------- I2C functions -----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

void i2c_init(uint8_t slaveaddress);
void i2c_write_cmd(uint8_t);
void i2c_read_sensors(uint8_t);

#endif
