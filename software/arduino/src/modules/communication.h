// communication.h

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "../globalincsanddefs.h"

struct TP {
	// Preamble
	uint8_t packetType:3;	// 3bits
	// Sensor data
    uint8_t ultrasonic;  // 8bits
    uint8_t bumpers:2;		// 2bits
    // System
    uint8_t mode:1;		// 1bit
    // Control
    int8_t leftMotor;	// 8bits
    int8_t rightMotor;	// 8bits
						// sum = 30
} ;

//extern struct TP TransmissionPacket;

typedef struct {
	int i;
} InstructionPacket;


//union test {
//	TP s;
//	uint8_t sendData[sizeof(TransmissionPacket)];
//};

//union test blabla;
//blabla.s = TransmissionPacket;
//blabla.sendData[i];


void initCommunication();
void updateCommunication ();

void insertInString(int8_t *, int8_t, int8_t, int8_t, int8_t);
//struct TransmissionPacket generateTransmissionPacket ();
//bool transmitData(struct TransmissionPacket packet);
InstructionPacket receiveData ();

bool openConnection();
void closeConnection();

void printVerbose();

void readInputs ();
int8_t keyIndex (char key);
char charIndex (int8_t key);


#endif
