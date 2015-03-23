// communication.c

#include "../globalincsanddefs.h"

extern union UID instructionData;
extern union USD sensorData;

int incomingByte = 0;
bool connectionIsOpen = false;
uint8_t activeKey = 0;
int16_t keyTimer = 0;
int16_t vebosityTimer = 0;

void initCommunication() {
	openConnection();
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
	readInputs ();
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

	sensorData.sensorStruct.bumperRight = 1;
	sensorData.sensorStruct.bumperLeft = 1;
	instructionData.instructionstruct.motorLeft = 255;
	instructionData.instructionstruct.motorRight = 255;
	instructionData.instructionstruct.ledStatus = 1;



	if (vebosityTimer-- == 0) {
		vebosityTimer = 0xFFFF;

		//char *str = (char*)malloc(3 * sizeof(char));

		if(sensorData.sensorStruct.ultrasonic > 100){
			sensorData.sensorStruct.ultrasonic = 0;
		}else{
			sensorData.sensorStruct.ultrasonic++;
		}

		if(sensorData.sensorStruct.batteryPercentage > 100){
			sensorData.sensorStruct.batteryPercentage = 0;
		}else{
			sensorData.sensorStruct.batteryPercentage++;
		}

		if(sensorData.sensorStruct.compassDegrees > 244){
			sensorData.sensorStruct.compassDegrees = 0;
		}else{
			sensorData.sensorStruct.compassDegrees += 10;
		}


		while (!outputBufferWalked());
		clearBuffer();
		/*serialPrint("");
		serialPrint(comm_itoa(instructionData.instructionstruct.motorLeft, str));
		serialPrint(":");
		serialPrint(comm_itoa(instructionData.instructionstruct.motorRight, str));
		serialPrint(":");
		serialPrint(comm_itoa(instructionData.instructionstruct.ledStatus, str));
		serialPrint(":");
		serialPrint(comm_itoa(sensorData.sensorStruct.ultrasonic, str));
		serialPrint(":");
		serialPrint(comm_itoa(sensorData.sensorStruct.bumperLeft, str));
		serialPrint(":");
		serialPrint(comm_itoa(sensorData.sensorStruct.bumperRight, str));
		serialPrint(":");
		serialPrint(comm_itoa(sensorData.sensorStruct.batteryPercentage, str));
		serialPrint(":");
		serialPrint(comm_itoa(sensorData.sensorStruct.compassDegrees, str));
		serialPrint(";");*/

		char *str = (char*)malloc(8 * sizeof(char));

        uint8_t i = 0;
		str[i++] = instructionData.instructionstruct.motorLeft;
		str[i++] = instructionData.instructionstruct.motorRight;
		str[i++] = instructionData.instructionstruct.ledStatus;
		str[i++] = sensorData.sensorStruct.ultrasonic;
		str[i++] = sensorData.sensorStruct.bumperLeft;
		str[i++] = sensorData.sensorStruct.bumperRight;
		str[i++] = sensorData.sensorStruct.batteryPercentage;
		str[i++] = sensorData.sensorStruct.compassDegrees;
		serialPrint(str);
		free(str);

	}
}

void readInputs () {
	if (serialAvailable()) {
		char input = serialRead();
		switch (input) {
			case 'w':
			case 'a':
			case 's':
			case 'd':
				if (input != activeKey) {
					if (activeKey) {
						inputKeyRelease(activeKey);
					}
					inputKeyPress(input);
				}
				activeKey = input;
				keyTimer = 0x3000;
				break;
			case 'p':
				activeKey = 0;
				break;
			case 'm':
				setSteeringMode(manual);
				break;
			case 'n':
				setSteeringMode(automatic);
				break;
		}
    }

	if (activeKey > 0) {
		if (keyTimer-- == 1) {
			inputKeyRelease(activeKey);
			activeKey = 0;
		}
		inputKeyDown (activeKey);

		//serialPrintCharacterSynchronous(activeKey);
	}
}
