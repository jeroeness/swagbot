// sensor.h

#ifndef SENSORHEADER
#define SENSORHEADER
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*---------------- SENSOR functions ----------------*/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
//description comes later because of debugging state.

//SD stands for SensorData
struct SD {
	uint8_t bumperRight:1;
	uint8_t bumperLeft:1;
	uint16_t compassDegrees;
	int8_t motorLeft;
	int8_t motorRight;
	uint16_t ultrasonic;
};

struct ID {
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};

//struct SD sensorStruct;
//struct ID instructionstruct;

union USD {
	struct SD sensorStruct;
	uint8_t sensorArray[sizeof(struct SD)];
};

union UID {
	struct ID instructionstruct;
	uint8_t instructionArray[sizeof(struct ID)];
};

extern union UID instructionData;
extern union USD sensorData;

#endif
