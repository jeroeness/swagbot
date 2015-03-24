// communication.c

#include "../globalincsanddefs.h"

#define KEYSTATESCOUNT 4

extern union UID instructionData;
extern union USD sensorData;

extern enum SteeringMode steeringMode;

int incomingByte = 0;
bool connectionIsOpen = false;
int16_t keyTimer = 0;
int16_t vebosityTimer = 0;


int8_t *keyState;


void initCommunication() {
	openConnection();
	sensorData.sensorStruct.batteryPercentage = 1;
	sensorData.sensorStruct.bumperRight = 1;
	sensorData.sensorStruct.bumperLeft = 1;
	instructionData.instructionstruct.motorLeft = 0;
	instructionData.instructionstruct.motorRight = 0;
	instructionData.instructionstruct.ledStatus = 1<<7;
	
	keyState = (int8_t*)calloc (KEYSTATESCOUNT, sizeof (int8_t));
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

	



	if (vebosityTimer-- == 0) {
		vebosityTimer = 0x8FFF;

		//char *str = (char*)malloc(3 * sizeof(char));
/*
		if(sensorData.sensorStruct.ultrasonic > 100){
			sensorData.sensorStruct.ultrasonic = 1;
		}else{
			sensorData.sensorStruct.ultrasonic++;
		}*/
		
		//sensorData.sensorStruct.ultrasonic = 1;
		
		//if(sensorData.sensorStruct.ultrasonic == 0 || sensorData.sensorStruct.ultrasonic == 255){
			
		//}
		
		/*
		if(sensorData.sensorStruct.batteryPercentage > 100){
			sensorData.sensorStruct.batteryPercentage = 1;
		}else{
			sensorData.sensorStruct.batteryPercentage++;
		}*/

		if(sensorData.sensorStruct.compassDegrees > 240){
			sensorData.sensorStruct.compassDegrees = 1;
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

		char str[11];
		
        uint8_t i = 0;
		str[i++] = instructionData.instructionstruct.motorLeft+128;
		str[i++] = instructionData.instructionstruct.motorRight+128;
		str[i++] = instructionData.instructionstruct.ledStatus;
		str[i++] = sensorData.sensorStruct.ultrasonic;
		str[i++] = sensorData.sensorStruct.bumperLeft;
		str[i++] = sensorData.sensorStruct.bumperRight;
		str[i++] = sensorData.sensorStruct.batteryPercentage;
		str[i++] = sensorData.sensorStruct.compassDegrees;
		if(steeringMode == manual){
			str[i++] = 1;
		}else{
			str[i++] = 2;
		}
		str[i++] = 255;
		str[i++] = 0;
		
		serialPrint(str);

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
        case 0: return 'w';
        case 1: return 'a';
        case 2: return 's';
        case 3: return 'd';
    }
	return ';';
}

void readInputs () {
	while(serialAvailable()){
		char input = serialRead();
		
		if(input == 0){
			sensorData.sensorStruct.ultrasonic = 1;
		}else if(input == 255){
			sensorData.sensorStruct.ultrasonic = 254;
		}else{
			sensorData.sensorStruct.ultrasonic = input;
		}
		
		switch (input) {
			case 'w':
			case 'a':
			case 's':
			case 'd':
			    keyState[keyIndex (input)] = 1;
                //inputKeyPress(input);
				break;
            case 'W':
			case 'A':
			case 'S':
			case 'D':
			    keyState[keyIndex (input)] = 0;
                inputKeyRelease(input + ('a'-'A'));
				break;
			case 'm':
				
				setSteeringMode(manual);
				break;
			case 'n':
				setSteeringMode(automatic);
				break;
		} 
    }
	
	/*
    for (int8_t i = 0; i < KEYSTATESCOUNT; i++) {
        if (keyState[i]) {
            inputKeyPress(charIndex(i));
        }
    }*/
	
	
}
