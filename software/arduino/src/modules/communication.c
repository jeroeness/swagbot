// communication.c

#include "../globalincsanddefs.h"

#define KEYSTATESCOUNT 4

extern union UID instructionData;
extern union USD sensorData;

extern enum SteeringMode steeringMode;

int incomingByte = 0;
bool connectionIsOpen = false;
int16_t keyTimer = 0;
uint16_t vebosityTimer = 1;
int8_t connectionTimeOut = 0;

int8_t keyState[KEYSTATESCOUNT];


void initCommunication() {
	openConnection();
	sensorData.sensorStruct.batteryPercentage = 1;
	sensorData.sensorStruct.bumperRight = 0;
	sensorData.sensorStruct.bumperLeft = 0;
	instructionData.instructionstruct.motorLeft = 0;
	instructionData.instructionstruct.motorRight = 0;
	instructionData.instructionstruct.ledStatus = 1<<7;
	sensorData.sensorStruct.ultrasonic = 0;

	for (int8_t i = 0; i < KEYSTATESCOUNT; i++) {
        keyState[i] = 0;
    }

}

bool openConnection () {
	serialBegin();
	connectionIsOpen = true;
	return 1;
}

void closeConnection() {
	serialEnd();
	connectionIsOpen = false;
}

void updateCommunication () {
	readInputs();
	printVerbose();
}

char* comm_itoa(int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0) {
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as you go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

char* uitoa(unsigned int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as you go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}


void printVerbose() {





	if (vebosityTimer-- == 0) {
		vebosityTimer = 0x3FFF;


		if(sensorData.sensorStruct.compassDegrees > 240){
			sensorData.sensorStruct.compassDegrees = 0;
		}else{
			sensorData.sensorStruct.compassDegrees += 10;
		}


		while (!outputBufferWalked());
		clearBuffer();
		const uint8_t dl = 11; //datalength

		char str[dl];

        uint8_t i = 0;
		str[i++] = instructionData.instructionstruct.motorLeft+128;
		str[i++] = instructionData.instructionstruct.motorRight+128;
		str[i++] = instructionData.instructionstruct.ledStatus;
		str[i++] = sensorData.sensorStruct.ultrasonic;
		str[i++] = sensorData.sensorStruct.bumperLeft;
		str[i++] = sensorData.sensorStruct.bumperRight;
		str[i++] = sensorData.sensorStruct.batteryPercentage;
		str[i++] = sensorData.sensorStruct.compassDegrees;
		str[i++] = (steeringMode == manual ? 0 : 1);
		str[i++] = connectionTimeOut; //this one is the connection strength (for timeout posibilities)


		str[i++] = 255;

		for (i = 0; i < dl-1; i++) {
			if (str[i] == 255) {
				str[i]--;
			}
		}

		serialPrint(str, dl);


		connectionTimeOut++;
		if(connectionTimeOut > 4){ //about 2 seconds i hope then connection timeout?
			//do something with the timout? automatic mode?
		}



	}
}

int8_t keyIndex (char key) {
    switch (key) {
        case 'w': return 0;
        case 'a': return 1;
        case 's': return 2;
        case 'd': return 3;
    }
	return 0;
}


char charIndex (int8_t key) {
    switch (key) {
        case 0:
			return 'w';
			break;
        case 1:
			return 'a';
			break;
        case 2:
			return 's';
			break;
        case 3:
			return 'd';
			break;
    }
	return 'w';
}

void readInputs () {
	while(serialAvailable()){
		char input = serialRead();

		switch (input) {
			case 'w':
			case 'a':
			case 's':
			case 'd':
			    keyState[keyIndex(input)] = 1;
                inputKeyPress(input);
				break;
            case 'W':
			case 'A':
			case 'S':
			case 'D':
			    keyState[keyIndex(input + ('a'-'A'))] = 0;
                inputKeyRelease(input + ('a'-'A'));
			    break;
			case 'm':
				setSteeringMode(manual);
				break;
			case 'n':
				setSteeringMode(automatic);
				break;

			case 'f': //keepconnection alive
			case 'F': //keepconnection alive
				connectionTimeOut = 0;
				break;
		}
    }

	//the following loop is not needed because:
	//we set on the keypress: the motor speeds
	//those values will never change in the struct so no need for this loop
	//this loop hangs the transmitter because of the 12c_lib wires not to be connected to the arduino
	//this results in an timeout of the i2c_lib. I will send 2 chars after eachother in the GUI on keyUp to be sure
	//the motors will be off btw.

	//if i2c is connected this loop will drastically slowdown the arduino process. WHY?
	//because this function is triggered as fast as it can. This loop will be so much to handle in that way
	//that it will slow down the custom timers like 0x8FFF values.

    for (int8_t i = 0; i < KEYSTATESCOUNT; i++) {
        if (keyState[i] == 1) {
            inputKeyDown(charIndex(i));
        }
    }


}
