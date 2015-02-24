#include <Arduino.h>

int incomingByte = 0;

void initCommunication() {
	Serial.begin(9600);

}

void updateCommunication () {

	updateCommunication();
	// send data only when you receive data:
	if (Serial.available() > 0) {
			// read the incoming byte:
			incomingByte = Serial.read();

			// say what you got:
			Serial.print((char)(('A'-'a')+incomingByte));
	}
}
