/*
 * i2c_lib.c
 *
 * Created: 3-3-2015 11:07:02
 *  Author: gerald
 *
 * v0.991 //at2560->at32 werkt
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

uint8_t volatile sensordata[256];//maybe change size?(sometime not now)
uint8_t volatile cmddata[256];
uint8_t volatile i2cbusy, rwamount;

void i2c_init(uint8_t slaveaddress) {
	TWSR = 0;	// prescaler always 0 (AVR315)
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = (slaveaddress<<1) | 1; // i2c slave address (atmega32) + general call enable
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	i2cbusy = 0;
}

void i2c_waitforidle(void) {
	uint8_t register timeoutcounter = 100;// (1/100khz) * (((~10)*berichtlengte) + (~11)) = ongeveer 0.001688 sec voor 20 byte write
	while (i2cbusy)	// wait if async process is still busy
	{
		if (!timeoutcounter--)
		{
			break;
		}
		_delay_ms(1);
	}
	return;
}

//cmd[0] = SLA+R/W
//cmd[1] = startaddress
//cmd[2...255] = data
void i2c_write_cmd(uint8_t amount) {
	i2c_waitforidle();
	cmddata[1] = 0;//start adress
	cmddata[0] = (0x55 << 1) | 0;// write
	rwamount = amount;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

void i2c_read_sensors(uint8_t amount) {
	i2c_waitforidle();
	cmddata[1] = 0;//start adress
	cmddata[0] = (0x55 << 1) | 1;// read
	rwamount = amount;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

int main(void)
{
	i2c_init(0x55);//SLA
	sei();
	while(1)
	{
		//cmd example
		cmddata[2] = 12;//data
		i2c_write_cmd(5);//the 5 is the amount of data with arrayindex 0 and 1 included in counting
		
		//sensor update example
		i2c_read_sensors(5);//updates sensorarray from 0 to 0+(amount+1)
		
		//slave example
		sensordata[0] = (PIND & 0x08) >> 3;
		if (cmddata[0])
		{
			cmddata[0] = 0;
			//do stuff with cmddata[1...253]
		} 
	}
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

ISR(TWI_vect)
{
	uint8_t static volatile rwaddress = 0; // index of read/write operation by a master
	uint8_t static volatile firstwrite = 0; // first write to slave is address (write to index)

	switch (TWSR & 0xF8)
	{
		case 0x60:	// SLA+W received, Ack was send back			SR (Master/Slave Transmitter/Receiver)
		case 0x70:	// gencall received, Ack was send back			SR
		case 0x68:	// arbitration lost (SLA+W/R). own SLA+W received, Ack was send		MT->SR
		case 0x78:	// arbitration lost (SLA+W/R). gencall received, Ack was send		MT->SR
			i2cbusy = 1;
			i2c_continue();
			firstwrite = 1;
			break;
		case 0x80:	// Data was received, Ack was send back			SR
		case 0x90:	// gencall Data was received, Ack was send back	SR
			if (firstwrite)
			{
				// write to address
				rwaddress = TWDR;
				firstwrite = 0;
			}
			else
				cmddata[rwaddress++] = TWDR;
			i2c_continue();
			break;

		case 0xA0:	// STOP or repeated START received			SR
			i2cbusy = 0;
			i2c_continue();
			break;
		case 0xA8:	// SLA+R received, Ack was send back			SR
		case 0xB0:	// arbitration lost (SLA+W/R). own SLA+R received, Ack was send		MT->ST
		case 0xB8:	// TWDR was send, Ack received				ST
			i2cbusy = 1;
			TWDR = sensordata[rwaddress++];
			i2c_continue();
			break;
		case 0xC0:	// TWDR was send, nAck received				ST
		case 0xC8:	// last TWDR was send, Ack received			ST
			i2c_continue();
			break;

//-----------------------------------------------------------------------------------------/\ slave /\  |  \/ master \/

		case 0x08:	// START condition was send				MR
			i2cbusy = 1;
			rwaddress = 1;
			TWDR = cmddata[0] & 0xFE;//write first
			i2c_continue();
			break;
		case 0x10:	// repeated START condition was send			MR
			TWDR = cmddata[0];// SLA+R
			i2c_continue();
			rwaddress = 0;
			break;
		case 0x18:	// SLA+W sent, Ack was received				MT
			TWDR = cmddata[rwaddress++];
			i2c_continue();
			break;
		case 0x28:	// TWDR was send, Ack received				MT
			if (cmddata[0] & 0x01)
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
				TWDR = cmddata[rwaddress++];
				i2c_continue();
			}
			break;
		case 0x40:	// SLA+R sent, Ack was received				MR
			i2c_continue();
			break;
		case 0x50:	// TWDR received, Ack was send back			MR
			sensordata[rwaddress++] = TWDR;
			if (rwaddress >= rwamount)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
				//i2c_stop();//this was my problem
			}
			else
				i2c_continue();
			break;
		case 0x58:	// TWDR received, nAck was send back			MR
			sensordata[rwaddress++] = TWDR;
			i2c_stop();
			break;

		case 0x38:	// arbitration lost (SLA+W/R or data)			MT/MR
			i2c_continue();//cancel MT/MR operations
			break;


		case 0x20:	// SLA+W sent, nAck was received			MT
		case 0x30:	// TWDR was send, nAck received				MT
		case 0x48:	// SLA+R sent, nAck was received			MR
		default:	// error (buserror)
			i2c_stop();
			break;
	}
}
