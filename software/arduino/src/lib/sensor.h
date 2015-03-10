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
	uint16_t ultrasonic;
};

struct ID{
	int8_t motorLeft;
	int8_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};

extern struct SD sensorData;
extern struct ID instructionData;

union USD {
	struct SD s;
	uint8_t receiveData[sizeof(sensorData)];
};

union UID {
	struct ID i;
	uint8_t sendData[sizeof(instructionData)];
};


#endif
