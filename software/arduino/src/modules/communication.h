#ifndef COMMUNICATION_H
#define COMMUNICATION_H

typedef struct {
	int i;
} TransmissionPacket;

typedef struct {
	int i;
} InstructionPacket;

void initCommunication();
void updateCommunication ();

void transmitData(TransmissionPacket *packet);
InstructionPacket receiveData ();

bool openConnection();
void closeConnection();


#endif
