/*
 * i2c_lib.c
 *
 * Created: 3-3-2015 11:07:02
 *  Author: gerald
 *
 * v1.15
 */

#include "../globalincsanddefs.h"


/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 400000UL
#endif

extern union UID instructionData;
extern union USD sensorData;

uint8_t volatile destaddress, destoffset, startindex, stopindex;

enum i2c_rxtx_stats {IDLE, BUSY};
enum i2c_rxtx_stats volatile i2c_state;

uint8_t volatile OverFlowToggle = 0; //for timer overflow

void i2c_init(uint8_t masteraddress) {
	TWSR = 0;	// prescaler always 0 (AVR315)
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = (masteraddress & 0xFE) | 1; // i2c master address + general call enable
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	i2c_state = IDLE;
	
	
	TCCR1B |= (1 << CS12) | (0<<CS10); //timer1: prescaler of 256
	TCNT1 = 30000; //timer1: init counter
	TIMSK1 |= (1 << TOIE1); //timer0: enable overflow interrupt
	
	DDRB |= 1<<PB7; //led on the arduino mega 2560 on pin 13
	
}

ISR(TIMER1_OVF_vect){
	
	
	switch(OverFlowToggle){
		case 0:
			i2c_write_cmd_wrap();
			OverFlowToggle = 1;
			break;
			
		case 1:
			i2c_readFromCompass();
			OverFlowToggle = 2;
			break;
			
		case 2:
			i2c_readFromRP6();
			OverFlowToggle = 0;
			break;
	}
	
	TCNT1 = 59000;
}


void i2c_write_cmd_wrap(void) {
	i2c_writeToRP6();
}

void i2c_read_sensors_wrap(void) {
	i2c_readFromCompass();
	i2c_readFromRP6();
}


void i2c_writeToRP6(void) {
	i2c_write(0xAA, 0, 0, sizeof(instructionData.instructionstruct));
	return;
}

void i2c_readFromRP6(void) {
	i2c_read(0xAA, 0, 0, sizeof(sensorData.sensorStruct) - 2);
	return;
}

void i2c_readFromCompass(void) {
	//compass information: http://www.robot-electronics.co.uk/htm/cmps3tech.htm
	
	i2c_read(0xC0, 1, sizeof(sensorData.sensorStruct) - 1, sizeof(sensorData.sensorStruct.compassDegrees));
	return;
}


void i2c_waitforidle(void) {
	uint8_t register timeoutcounter = 200;
	while (i2c_state == BUSY)	// wait while async process is still busy
	{
		if (!--timeoutcounter)
		{
			//i2c_state = ERROR;
			break;
		}
		_delay_us(500);
	}
	return;
}

void i2c_write(uint8_t destaddr, uint8_t destoffs, uint8_t offset, uint8_t amount) {
	i2c_waitforidle();
	i2c_state = BUSY;
	PORTB |= 1<<PB7; //pin 13 led on
	
	destaddress = (destaddr & 0xFE) | 0;// write
	destoffset = destoffs;
	startindex = offset;
	uint16_t temp16bitnumber = amount;
	temp16bitnumber += offset;
	if (temp16bitnumber <= 0xFF)
	{
		stopindex = (uint8_t)temp16bitnumber;
	}
	else
	{
		stopindex = 0xFF;
	}
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

void i2c_read(uint8_t destaddr, uint8_t destoffs, uint8_t offset, uint8_t amount) {
	i2c_waitforidle();
	i2c_state = BUSY;
	PORTB |= 1<<PB7; //pin 13 led on
	
	destaddress = (destaddr & 0xFE) | 1;// read
	destoffset = destoffs;
	startindex = offset;
	uint16_t temp16bitnumber = amount;
	temp16bitnumber += offset;
	if (temp16bitnumber <= 0xFF)
	{
		stopindex = (uint8_t)temp16bitnumber;
	}
	else
	{
		stopindex = 0xFF;
	}
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
	while(TWCR & (1 << TWSTO));
	
	PORTB &= ~(1<<PB7); //pin 13 led off
	
	i2c_state = IDLE;
	return;
}

//cant see if its a stop or a repeated START
void i2c_SR_done(void)
{
	return;
}

void i2c_MR_done(void)
{
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
			i2c_state = BUSY;
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
			instructionData.instructionArray[rwaddress++] = TWDR;
			i2c_continue();
			break;

		case 0xA0:	// STOP or repeated START received				SR
			i2c_state = IDLE;
			i2c_continue();
			i2c_SR_done();
			break;
		case 0xA8:	// SLA+R received, Ack was send back				SR
		case 0xB0:	// arbitration lost (SLA+W/R). own SLA+R received, Ack was send	MT->ST
		case 0xB8:	// TWDR was send, Ack received					ST
			i2c_state = BUSY;
			TWDR = sensorData.sensorArray[rwaddress++];
			i2c_continue();
			break;
		case 0xC0:	// TWDR was send, nAck received					ST
		case 0xC8:	// last TWDR was send, Ack received				ST
			i2c_continue();
			break;

		//-----------------------------------------------------------------------------------------/\ slave /\  |  \/ master \/

		case 0x08:	// START condition was send					MR
			//i2c_state = BUSY;
			rwaddress = startindex;
			TWDR = destaddress & 0xFE;//write first
			i2c_continue();
			break;
		case 0x10:	// repeated START condition was send				MR
			TWDR = destaddress;// SLA+R
			i2c_continue();
			rwaddress = startindex;
			stopindex--;// MR must end sooner than MT because MT can end whenever and MR must nACK first
			break;
		case 0x18:	// SLA+W sent, Ack was received					MT
			TWDR = destoffset;
			i2c_continue();
			break;
		case 0x28:	// TWDR was send, Ack received					MT
			if (destaddress & 0x01)
			{
				TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);// send repeated START
				break;
			}
			if (rwaddress >= stopindex)
			{
				i2c_stop();
			}
			else
			{
				TWDR = instructionData.instructionArray[rwaddress++];
				i2c_continue();
			}
			break;
		case 0x40:	// SLA+R sent, Ack was received					MR
			if (rwaddress >= stopindex)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
			}
			else
			{
				i2c_continue();
			}
			break;
		case 0x50:	// TWDR received, Ack was send back				MR
			sensorData.sensorArray[rwaddress++] = TWDR;
			if (rwaddress >= stopindex)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
			}
			else
			{
				i2c_continue();
			}
			break;
		case 0x58:	// TWDR received, nAck was send back				MR
			sensorData.sensorArray[rwaddress++] = TWDR;
			i2c_stop();
			i2c_MR_done();
			break;


		case 0x38:	// arbitration lost (SLA+W/R or data)				MT/MR
			i2c_continue();
			i2c_state = IDLE;
			PORTB &= ~(1<<PB7); //pin 13 led off
			break;

		case 0x20:	// SLA+W sent, nAck was received				MT
		case 0x30:	// TWDR was send, nAck received					MT
		case 0x48:	// SLA+R sent, nAck was received				MR
		default:	// error (buserror)
			i2c_stop();
			break;
	}
}
