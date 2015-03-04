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
	int16_t ultrasonic;
	int16_t motorLeft;
	int16_t motorRight;
	uint8_t ledStatus; //8 all leds in one variable
};

extern struct SD sensorData;

union USD {
	struct SD s;
	uint8_t sendData[sizeof(sensorData)];
};


#endif
