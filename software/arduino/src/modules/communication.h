#ifndef COMMUNICATION_H
#define COMMUNICATION_H

typedef struct {
	// Preamble
	int8_t packetType;	// 3bits
	// Sensor data
    int8_t ultrasonic;  // 8bits
    int8_t bumpers;		// 2bits
    // System
    int8_t mode;		// 1bit
    // Control
    int8_t leftMotor;	// 8bits
    int8_t rightMotor;	// 8bits
						// sum = 30
} TransmissionPacket;

typedef struct {
	int i;
} InstructionPacket;

void initCommunication();
void updateCommunication ();

inline void insertInString(int8_t *, int8_t, int8_t, int8_t, int8_t);
TransmissionPacket generateTransmissionPacket ();
bool transmitData(TransmissionPacket packet);
InstructionPacket receiveData ();

bool openConnection();
void closeConnection();

void printVerbose();

void readInputs ();


#endif
