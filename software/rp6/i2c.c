/*
 * i2c.c
 *
 * Created: 3-3-2015 11:07:02
 *  Author: gerald
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include <avr/sleep.h>

/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

uint8_t volatile sensordata[256];
uint8_t volatile cmddata[256];
uint8_t volatile i2cbusy, rwamount;

void i2c_init(uint8_t slaveaddress) {
	TWSR = 0;	// prescaler always 0 (AVR315)
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = (slaveaddress<<1) | 1; // i2c slave address (atmega32) + general call enable
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
}

void i2c_write_cmd(uint8_t amount) {
	while (i2cbusy);	// wait if async process is still busy
	cmddata[0] = (0x55 << 1) | 0;// write
	//i2cbusy = 1;
	TWCR |= (1<<TWSTA);// send START condition (starts interrupt process)
	return;
}

void i2c_read_sensors(uint8_t amount) {
	while (i2cbusy);	// wait if async process is still busy
	cmddata[0] = (0x55 << 1) | 1;// read
	//i2cbusy = 1;
	TWCR |= (1<<TWSTA);// send START condition (starts interrupt process)
	return;
}

int main(void)
{
	//DDRC = 0x05;
	//PORTC |= 0x01;
	i2c_init(0x55);
	//set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
	while(1)
	{
	}
}

ISR(TWI_vect)
{
	uint8_t static volatile rwaddress = 0; // index of read/write operation by a master
	uint8_t static volatile firstwrite = 0; // first write to slave is address (write to index)

	TWCR |= (1<<TWINT);

	switch (TWSR & 0xF8)
	{
		case 0x60: // SLA+W received, Ack was send back				SR (Master/Slave Transmitter/Receiver)
		case 0x70: // gencall received, Ack was send back			SR
			i2cbusy = 1;
			firstwrite = 1;
			break;
		case 0x80: // Data was received, Ack was send back			SR
		case 0x90: // gencall Data was received, Ack was send back	SR
			if (firstwrite)
			{
				// write to address
				rwaddress = TWDR;
				firstwrite = 0;
			}
			else
				cmddata[rwaddress++] = TWDR;
			break;
		case 0xA0:
			// STOP or repeated START received			SR
			i2cbusy = 0;
			break;
		case 0xA8:
			// SLA+R received, Ack was send back		SR
			i2cbusy = 1;
			break;
		case 0xB8:
			// TWDR was send, Ack received				ST
			TWDR = sensordata[rwaddress++];
			break;
		case 0xC0:
			// TWDR was send, nAck received				ST
			break;
		case 0xC8:
			// last TWDR was send, Ack received			ST
			break;

//  /\ slave /\  |  \/ master \/

		case 0x18: // SLA+W sent, Ack was received		MT
			TWDR = cmddata[rwaddress++];
			break;
		case 0x20: // SLA+W sent, nAck was received		MT
			TWCR |= (1 << TWSTO);// send stop
			i2cbusy = 0;
			break;
		case 0x28:
			// TWDR was send, Ack received				MT
			if (cmddata[0] & 0x01)
			{
				TWCR |= (1<<TWSTA);// send repeated START
				break;
			}
			TWDR = cmddata[rwaddress++];
			if (rwaddress >= rwamount)
			{
				TWCR |= (1 << TWSTO);// send stop
				i2cbusy = 0;
			}
			break;
		case 0x30:
			// TWDR was send, nAck received				MT
			TWCR |= (1 << TWSTO);// send stop
			i2cbusy = 0;
			break;
		case 0x38:
			// arbitration lost (SLA+W/R or data)		MT/MR
			TWCR &= ~(1 << TWSTA);
			TWCR |= (1 << TWSTO);// release bus
			i2cbusy = 0;
			break;
		case 0x08:
			// START condition was send					MR
			i2cbusy = 1;
			rwaddress = 2;
			TWCR &= ~(1 << TWSTA);
			TWCR |= (1 << TWEA);
			TWDR = cmddata[0] & 0xFE;//write first
			break;
		case 0x10:
			// repeated START condition was send		MR
			TWDR = sensordata[0];// SLA+R
			rwaddress = 0;
			break;
		case 0x40: // SLA+R sent, Ack was received		MR
			break;
		case 0x48: // SLA+R sent, nAck was received		MR
			TWCR |= (1 << TWSTO);// send stop
			i2cbusy = 0;
			break;
		case 0x50:
			// TWDR received, Ack was send back			MR
			sensordata[rwaddress++] = TWDR;
			if (rwaddress >= rwamount)
			{
				TWCR |= (1 << TWSTO);// send stop
				i2cbusy = 0;
			}
			break;
		case 0x58:
			// TWDR received, nAck was send back		MR

			TWCR |= (1 << TWSTO);// send stop
			i2cbusy = 0;
			break;


		default:
			// error (master+arbitration+(gencall or SLA+R/W) or buserror)
			TWCR &= ~(1 << TWSTA);
			TWCR |= (1 << TWSTO);// assert stop to recover
			TWCR |= (1 << TWEA);
			i2cbusy = 0;
			break;
	}
}
