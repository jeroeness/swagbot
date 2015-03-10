#include "communication.h"
#include "../lib/serial.h"
#include "mode_manager.h"
#include "../lib/sensor.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

extern struct ID instructionData;
extern struct SD sensorData;

int incomingByte = 0;
bool connectionIsOpen = false;
uint8_t activeKey = 0;
int16_t keyTimer = 0;

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
    //printVerbose();
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
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
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


void printVerbose() {

	sensorData.bumperRight = 1;
	sensorData.bumperLeft = 1;
	instructionData.motorLeft = 255;
	instructionData.motorRight = 255;
	instructionData.ledStatus = 1;
	sensorData.ultrasonic = 12;


	char *str = (char*)malloc(3 * sizeof(char));

    while (!outputBufferWalked());
    clearBuffer();
    serialPrint("Motor Left:");
    serialPrintLine(itoa(instructionData.motorLeft, str));
    serialPrint("Motor Right:");
    serialPrintLine(itoa(instructionData.motorRight, str));

    serialPrint("LED:");
    serialPrintLine(itoa(instructionData.ledStatus, str));
    serialPrint("Ultrasonic:");
    serialPrintLine(itoa(sensorData.ultrasonic, str));

    serialPrint("The Right bumper:");
    serialPrintLine(itoa(sensorData.bumperRight, str));
    serialPrint("The left bumper:");
    serialPrintLine(itoa(sensorData.bumperLeft, str));

    free(str);
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

		serialPrintCharacterSynchronous(activeKey);
    }
}
