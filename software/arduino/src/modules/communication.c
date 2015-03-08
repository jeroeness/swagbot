#include "communication.h"
#include "serial.h"
#include "mode_manager.h"
#include "sensor.h"

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
    printVerbose();
}

void printVerbose() {
    //serialPrintLine("hello");
    //TODO print suff


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

		char *str = " ";
		str[0] = activeKey;
		serialPrint(str);
    }
}
