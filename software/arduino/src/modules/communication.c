// communication.c

#include "../globalincsanddefs.h"

#define KEYSTATESCOUNT 4

#define dl 11 //datalength

extern union UID instructionData;
extern union USD sensorData;

extern enum SteeringMode steeringMode;

extern uint8_t currentFace;

int incomingByte = 0;
bool connectionIsOpen = false;
int16_t keyTimer = 0;
uint16_t vebosityTimer = 1;
int8_t connectionTimeOut = 0;

int8_t keyState[KEYSTATESCOUNT];

int8_t uploadActionBits = -1;
uint8_t uploadActionBuffer[] = {0,0,0,0};

void initCommunication() {
	openConnection();
	sensorData.sensorStruct.batteryPercentage = 1;
	sensorData.sensorStruct.bumperRight = 0;
	sensorData.sensorStruct.bumperLeft = 0;
	instructionData.instructionstruct.motorLeft = 0;
	instructionData.instructionstruct.motorRight = 0;
	instructionData.instructionstruct.ledStatus = 1<<7;
	sensorData.sensorStruct.ultrasonic = 0;
	sensorData.sensorStruct.compassDegrees = 0;

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

void printVerbose() {

	if (vebosityTimer-- == 0) {

		vebosityTimer = 0x1FFF;

/*
		if(sensorData.sensorStruct.compassDegrees > 240){
			sensorData.sensorStruct.compassDegrees = 0;
		}else{
			sensorData.sensorStruct.compassDegrees += 10;
		}*/


		while (!outputBufferWalked());
		clearBuffer();

		uint8_t str[dl];

        uint8_t i = 0;
		str[i++] = instructionData.instructionstruct.motorLeft+128;
		str[i++] = instructionData.instructionstruct.motorRight+128;
		str[i++] = instructionData.instructionstruct.ledStatus;
		str[i++] = sensorData.sensorStruct.ultrasonic;
		str[i++] = (sensorData.sensorStruct.bumperLeft<<1) | (sensorData.sensorStruct.bumperRight<<0) | (i2c_checkstatus()<<2);
		str[i++] = sensorData.sensorStruct.batteryPercentage;
		str[i++] = sensorData.sensorStruct.compassDegrees;
		str[i++] = (steeringMode == manual ? 0 : 1);
		str[i++] = connectionTimeOut; //this one is the connection strength (for timeout posibilities)
		str[i++] = currentFace;

		str[i++] = 255;

		for (i = 0; i < (dl-1); i++) {
			if (str[i] == 255) str[i]--;
		}

		serialPrintUnsigned(str, dl); //sorry jeroen, needed this because the loop above was detecting negative numbers OH MY GOD!?!?!?!
		//So needed to force the arduino to be unsigned int. This idea fucks my brain up but it works now (its just a copy of your function with only uint8_t c[] in the parameter


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
        case 0:	return 'w';
        case 1:	return 'a';
        case 2:	return 's';
        case 3: return 'd';
    }
	return 'w';
}

void readInputs () {
	while(serialAvailable()){
		wchar_t input = serialRead();
		
		if(uploadActionBits != -1){
			
			uploadActionBuffer[uploadActionBits] = input;
			
			connectionTimeOut = 0; //prevent timeout
			uploadActionBits++;
			if(uploadActionBits == 3){ //add the action to the list
				addToActionList(uploadActionBuffer[0], uploadActionBuffer[1], uploadActionBuffer[2]);
				displayText("/r8/g9/b1");
				uploadActionBits = -1;
			}
			return;
		}
		
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
			
			case 'u': //uploading actionlist
				uploadActionBits = 0;
				connectionTimeOut = 0;
				break;
				
			case 'k':
				i2c_initCalibration();
				break;
				
			case 'z': //we have send the last char in our serialdata from gui so we may send again :)
				vebosityTimer = 10;
				break;
				
		}
    }

    for (int8_t i = 0; i < KEYSTATESCOUNT; i++) {
        if (keyState[i] == 1) {
            inputKeyDown(charIndex(i));
        }
    }
}
