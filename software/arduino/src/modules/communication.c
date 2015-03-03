#include <Arduino.h>
#include "communication.h"
#include "lib/serial.h"
#include "mode_manager.h"

int incomingByte = 0;
bool connectionIsOpen = false;
int8_t activeKey = 0;
int16_t keyTimer = 0;

void initCommunication() {

	openConnection();

}

bool openConnection () {
	// TODO omschrijven, arduino lib niet gebruiken
	Serial.begin(9600);
	Serial.print("hello");
	connectionIsOpen = true;
	return 1;
}

void closeConnection() {
    Serial.end();
    connectionIsOpen = false;
}

void updateCommunication () {

    /*
    TransmissionPacket t = generateTransmissionPacket();

	if (!transmitData(t)) {

		//TODO flashPanicLight();

	}*/

	// send data only when you receive data:
	if (Serial.available() > 0) {
			// read the incoming byteo
			//incomingByte = Serial.read();

			// say what you got:
	}

	readInputs ();

}

void readInputs () {
    if (Serial.available() > 0) {
        int8_t input = Serial.read();

        switch (input) {
            case 'w':
            case 'a':
            case 's':
            case 'd':
            activeKey = input;
            keyTimer = 0x3000;
			Serial.print(activeKey);
            break;
            case 'm':
                setSteeringMode(manual);
			break;
			case 'n':
				setSteeringMode(automatic);
			break;
        }


    }
    if (keyTimer-- == 1) {
        activeKey = 0;
    }

    if (activeKey > 0) {
		inputKey (activeKey);
    } else {
        PORTB = PORTD = 0;
    }
}

TransmissionPacket generateTransmissionPacket () {
	TransmissionPacket tp;

	// TODO temporary generating dummy packet
	tp.bumpers = 3;
	tp.leftMotor = 255;
	tp.rightMotor = 127;
    tp.mode = 0;
    tp.packetType = 1;
    tp.ultrasonic = 152;

    tp.bumpers = 0;
	tp.leftMotor = 0;
	tp.rightMotor = 0;
    tp.mode = 0;
    tp.packetType = 1;
    tp.ultrasonic = 0;

    return tp;
}

bool transmitData(TransmissionPacket packet) {

	// See transmission packet for sizes
    int packetSize = 3 + 8 + 2 + 1 + 8 + 8;
    int mallocSize = (int)ceil(packetSize / 8) + 1;

    int8_t * data = (int8_t*)calloc(mallocSize, sizeof(int8_t));

	// data visualisation:
	// [........][........][........][........][......]
	//  AAABBBBB  BBBCCDEE  EEEEEEFF  FFFFFF    \0
	//data |= packet.packetType;
	//data |= packet.ultrasonic >> 3;

	insertInString(data, packet.rightMotor, 8, 3, 2);
	insertInString(data, packet.leftMotor, 8, 2, 2);
	insertInString(data, packet.mode, 1, 1, 2);
	insertInString(data, packet.bumpers, 2, 1, 3);
	insertInString(data, packet.ultrasonic, 8, 1, 5);
	insertInString(data, packet.packetType, 3, 0, 5);

	for (int i = 0; i < mallocSize; i++) {
		Serial.print((int8_t)data[i], BIN);
		Serial.print(' ');
	}
	Serial.println();

    free(data);

	return 1;
}

inline int8_t power(int8_t base, int8_t exp) {
	if (exp == 0) {
		return base != 0;
	}
	for (int8_t i = 0; i < exp; i++) {
		base *= base;
	}
}

inline void insertInString(int8_t *string, int8_t data, int8_t dataLength, int8_t byteOffset, int8_t bitOffset) {
	//string[byteOffset] |= (data & ((1<<7-bitOffset)-1)) << bitOffset;

	//if (bitOffset+dataLength > 8) {
	//	string[byteOffset - 1] |= (data & ~((1<<7-bitOffset)-1)) >> 8 - bitOffset;
	//}

	int8_t i = 0;
	for (i = 0; i < min(8-bitOffset, dataLength); i++) {
		if (data & (1 << i)) {
			string[byteOffset] += power(2, i + bitOffset);
		}
	}


}
