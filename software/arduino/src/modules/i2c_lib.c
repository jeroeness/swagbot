#define F_CPU 8000000

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "automatic_mode.h"
#include "motor.h"
#include "sensor.h"
#include "mode_manager.h"
#include "i2c_lib.h"

/*
 * i2c_lib.c
 *
 * Created: 3-3-2015 11:07:02
 *  Author: gerald
 *
 * v1.01
 */ 
//todo
// startindex+rwamount fixen

/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

extern struct ID instructionData;
extern struct SD sensorData;

union UID instructionDataLocal;
union USD sensorDataLocal;

uint8_t volatile destaddress, startindex, rwamount;
uint8_t volatile i2cbusy;

void i2c_init(uint8_t masteraddress) {
	TWSR = 0;	// prescaler always 0 (AVR315)
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = (masteraddress & 0xFE) | 1; // i2c master address (atmega 2560) + general call enable
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	i2cbusy = 0;
}

void i2c_waitforidle(void) {
	uint8_t register timeoutcounter = 100;
	while (i2cbusy)	// wait if async process is still busy
	{
		if (!timeoutcounter--)
			break;
		_delay_ms(1);
	}
	return;
}



void i2c_write_cmd_wrap(void) {
	
	instructionDataLocal.i.motorLeft = instructionData.motorLeft;
	instructionDataLocal.i.motorRight = instructionData.motorRight;
	instructionDataLocal.i.ledStatus = instructionData.ledStatus;


	i2c_write_cmd(sizeof(instructionData));
	return;
}






void i2c_write_cmd(uint8_t amount) {
	i2c_waitforidle();
	destaddress = (0xAA & 0xFE) | 0;// write
	startindex = 0;
	rwamount = amount;
	i2cbusy = 1;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

void i2c_read_sensors(uint8_t amount) {
	i2c_waitforidle();
	destaddress = (0xAA & 0xFE) | 1;// read
	startindex = 0;
	rwamount = amount;
	i2cbusy = 1;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

void i2c_continue(void)
{
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	return;
}

void i2c_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE);
	i2cbusy = 0;
	return;
}

//cant see if its a stop or a repeated START
void i2c_SR_done(void)
{
	//parseInstruction();//sensor.c
	return;
}

ISR(TWI_vect)
{
	uint8_t static volatile rwaddress = 0; // index of read/write operation by a master
	uint8_t static volatile firstwrite = 0; // first write to slave is address (write to index)

	switch (TWSR & 0xF8)
	{
		case 0x60:	// SLA+W received, Ack was send back				SR (Master/Slave Transmitter/Receiver)
		case 0x70:	// gencall received, Ack was send back				SR
		case 0x68:	// arbitration lost (SLA+W/R). own SLA+W received, Ack was send	MT->SR
		case 0x78:	// arbitration lost (SLA+W/R). gencall received, Ack was send	MT->SR
			i2cbusy = 1;
			i2c_continue();
			firstwrite = 1;
			break;
		case 0x80:	// Data was received, Ack was send back				SR
		case 0x90:	// gencall Data was received, Ack was send back			SR
			if (firstwrite)
			{
				// write to address
				rwaddress = TWDR;
				firstwrite = 0;
			}
			else
				instructionDataLocal.instructionArray[rwaddress++] = TWDR;
			i2c_continue();
			break;

		case 0xA0:	// STOP or repeated START received				SR
			i2cbusy = 0;
			i2c_continue();
			i2c_SR_done();
			break;
		case 0xA8:	// SLA+R received, Ack was send back				SR
		case 0xB0:	// arbitration lost (SLA+W/R). own SLA+R received, Ack was send	MT->ST
		case 0xB8:	// TWDR was send, Ack received					ST
			i2cbusy = 1;
			TWDR = sensorDataLocal.sensorArray[rwaddress++];
			i2c_continue();
			break;
		case 0xC0:	// TWDR was send, nAck received					ST
		case 0xC8:	// last TWDR was send, Ack received				ST
			i2c_continue();
			break;

//-----------------------------------------------------------------------------------------/\ slave /\  |  \/ master \/

		case 0x08:	// START condition was send					MR
			i2cbusy = 1;
			rwaddress = 0;
			TWDR = destaddress & 0xFE;//write first
			i2c_continue();
			break;
		case 0x10:	// repeated START condition was send				MR
			TWDR = destaddress;// SLA+R
			i2c_continue();
			rwaddress = 0;
			break;
		case 0x18:	// SLA+W sent, Ack was received					MT
			TWDR = startindex;
			i2c_continue();
			break;
		case 0x28:	// TWDR was send, Ack received					MT
			if (destaddress & 0x01)
			{
				TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);// send repeated START
				break;
			}
			if (rwaddress >= rwamount)
			{
				i2c_stop();
			}
			else
			{
				TWDR = instructionDataLocal.instructionArray[rwaddress++];
				i2c_continue();
			}
			break;
		case 0x38:	// arbitration lost (SLA+W/R or data)				MT/MR
		case 0x40:	// SLA+R sent, Ack was received					MR
			i2c_continue();
			break;
		case 0x50:	// TWDR received, Ack was send back				MR
			sensorDataLocal.sensorArray[rwaddress++] = TWDR;
			if (rwaddress >= rwamount)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
			}
			else
				i2c_continue();
			break;
		case 0x58:	// TWDR received, nAck was send back				MR
			sensorDataLocal.sensorArray[rwaddress++] = TWDR;
			i2c_stop();
			break;


		case 0x20:	// SLA+W sent, nAck was received				MT
		case 0x30:	// TWDR was send, nAck received					MT
		case 0x48:	// SLA+R sent, nAck was received				MR
		default:	// error (buserror)
			i2c_stop();
			break;
	}
}
