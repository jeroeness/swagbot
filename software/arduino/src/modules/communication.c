#include <Arduino.h>
#include "communication.h"

int incomingByte = 0;
bool connectionIsOpen = false;

void initCommunication() {

	openConnection();

}

bool openConnection () {
	// TODO omschrijven, arduino lib niet gebruiken
	Serial.begin(9600);
	connectionIsOpen = true;
	return 1;
}

void closeConnection() {
    Serial.end();
    connectionIsOpen = false;
}

void updateCommunication () {

	updateCommunication();
	// send data only when you receive data:
	if (Serial.available() > 0) {
			// read the incoming byteo
			incomingByte = Serial.read();

			// say what you got:
			Serial.print((char)(('A'-'a')+incomingByte));
	}
}
