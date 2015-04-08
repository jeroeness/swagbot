/*
 * i2c_lib.c
 *
 * Created: 3-3-2015 11:07:02
 *  Author: gerald
 *
 * v2.00
 */

#include "../globalincsanddefs.h"

/* I2C clock in Hz */
#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

extern union UID instructionData;
extern union USD sensorData;

//i2c core \/ .
enum i2c_rxtx_stats {IDLE, BUSY};
enum i2c_rxtx_stats volatile i2c_state;

uint8_t dest_SLA_RW, destaddress;
uint8_t *MTbuffer, *MRbuffer, i2c_rw_amount;
uint8_t *STbuffer, *SRbuffer, STbuffsize, SRbuffsize;
void (*i2c_MT_MR_Done) (void);
void (*i2c_ST_SR_Done) (void);
void (*i2c_error_call) (void);
//i2c core /\ .

uint8_t OverFlowToggle = 10; //for timer overflow

void i2c_init(void)
{
	i2c_init_M();//init as master only
	//i2c_callback_attach(0, 0, 0);

	// Timer1
	TCCR1A = (1 << WGM11) | (0 << WGM10);// timer mode 14(fast pwm)(pwm is not used)(IRC1 = TOP)
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12); //prescaler = div256 (16Mhz/256 = 62500hz)
	TCCR1C = 0;
	
	//ICR1 = 4167; 
	ICR1 = 4167; //set counter TOP    (16Mhz/256)/15hz = 4167
	TCNT1 = 0; //reset count
	TIFR1 = (1 << TOV1); //clear overflow flag
	TIMSK1 = (1 << TOIE1); //enable overflow interrupt

	DDRB |= 1<<PB7; //arduinomega2560 pin 13 led output
	PORTB &= ~(1<<PB7); //arduinomega pin 13 led off
}

void i2c_initCalibration(void){
	OverFlowToggle = 0;
	ICR1 = 0xFFFF;
}

ISR(TIMER1_OVF_vect)
{
	//15hz
	
	//PORTB ^= (1<<PB7); //arduinomega pin 13 led toggle
	
	switch(OverFlowToggle) {
		case 0:
		case 3:
		case 6:
		case 9:
			OverFlowToggle++;
			i2c_SendCompassCalibrateCmd();
			break;
			
		case 10:
			ICR1 = 4167;
			i2c_writeToRP6();
			OverFlowToggle = 11;
			break;
			
		case 11:
			i2c_readFromCompass();
			OverFlowToggle = 12;
			break;
			
		case 12:
			i2c_readFromRP6();
			OverFlowToggle = 10;
			break;
			
		
		default:
			OverFlowToggle++;
			break;
	}

	
}


void i2c_writeToRP6(void)
{
	i2c_write(0xAA, 0, (uint8_t *) &(instructionData.instructionstruct), sizeof(instructionData.instructionstruct));
	return;
}

void i2c_readFromRP6(void)
{
	i2c_read(0xAA, 0, (uint8_t *) &(sensorData.sensorStruct), sizeof(sensorData.sensorStruct) - 2);
	return;
}

//compass information: http://www.robot-electronics.co.uk/htm/cmps3tech.htm
void i2c_SendCompassCalibrateCmd(void)
{
	sensorData.sensorStruct.compassDegrees = 0xFF;
	i2c_write(0xC0, 0x0F, &(sensorData.sensorStruct.compassDegrees), sizeof(sensorData.sensorStruct.compassDegrees));
	i2c_waitforidle();
	return;
}

void i2c_readFromCompass(void)
{
	i2c_read(0xC0, 1, &(sensorData.sensorStruct.compassDegrees), sizeof(sensorData.sensorStruct.compassDegrees));
	return;
}


// i2c core \/ .
void i2c_change_slave_buffers(uint8_t *transmitarray, uint8_t transmitarraysize, uint8_t *receivearray, uint8_t receivearraysize)
{
	i2c_waitforidle();
	STbuffsize = transmitarraysize;
	SRbuffsize = receivearraysize;
	STbuffer = transmitarray;
	SRbuffer = receivearray;
}

void i2c_init_M_S(uint8_t own_SLA, uint8_t *transmitarray, uint8_t transmitarraysize, uint8_t *receivearray, uint8_t receivearraysize)
{
	uint8_t SREGorig = SREG; // Save SREG and disable interrupts
	cli();

	STbuffsize = transmitarraysize;
	SRbuffsize = receivearraysize;
	STbuffer = transmitarray;
	SRbuffer = receivearray;
	i2c_MT_MR_Done = 0;
	i2c_ST_SR_Done = 0;
	i2c_error_call = 0;

	TWSR = 0;	// prescaler is 0
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = (own_SLA & 0xFE) | 1; // i2c master address + general call enable
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	i2c_state = IDLE;

	SREG = SREGorig; // Restore SREG(and i bit)
}

void i2c_init_M(void)
{
	uint8_t SREGorig = SREG; // Save SREG and disable interrupts
	cli();

	STbuffsize = 0;
	SRbuffsize = 0;
	i2c_MT_MR_Done = 0;
	i2c_ST_SR_Done = 0;
	i2c_error_call = 0;

	TWSR = 0;	// prescaler is 0
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
	TWAR = 0; // i2c master address + general call off
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	i2c_state = IDLE;

	SREG = SREGorig; // Restore SREG(and i bit)
}

//0 = idle, 1 = busy
uint8_t i2c_checkstatus(void)
{
	return i2c_state;
}

void i2c_waitforidle(void)
{
	uint8_t register timeoutcounter = 250;
	while (i2c_state == BUSY)	// wait while async process is still busy
	{
		if (!--timeoutcounter)
		{
			break;
		}
		_delay_us(500);
	}
	return;
}

void i2c_callback_attach(void (*i2c_master_Done) (void), void (*i2c_slave_Done) (void), void (*i2c_error) (void))
{
	i2c_waitforidle();
	i2c_MT_MR_Done = i2c_master_Done;
	i2c_ST_SR_Done = i2c_slave_Done;
	i2c_error_call = i2c_error;
}

void i2c_write(uint8_t destSLA, uint8_t destregaddress, uint8_t *dataptr, uint8_t amount)
{
	i2c_waitforidle();
	i2c_state = BUSY;

	PORTB |= 1<<PB7; //arduinomega pin 13 led on

	dest_SLA_RW = (destSLA & 0xFE) | 0;// write
	destaddress = destregaddress;
	MTbuffer = dataptr;
	i2c_rw_amount = amount;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);// send START condition (starts interrupt process)
	return;
}

void i2c_read(uint8_t destSLA, uint8_t destregaddress, uint8_t *dataptr, uint8_t amount)
{
	i2c_waitforidle();
	i2c_state = BUSY;

	PORTB |= 1<<PB7; //arduinomega pin 13 led on

	dest_SLA_RW = (destSLA & 0xFE) | 1;// read
	destaddress = destregaddress;
	MRbuffer = dataptr;
	i2c_rw_amount = amount;
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
	
	PORTB &= ~(1<<PB7); //arduinomega pin 13 led off

	i2c_state = IDLE;
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
				i2c_continue();
			}
			else
			{
				SRbuffer[rwaddress++] = TWDR;
				i2c_continue();
				if (rwaddress >= SRbuffsize)//wraps around if buffer is to small
				{
					rwaddress -= SRbuffsize;
				}
			}
			break;
		case 0xA0:	// STOP or repeated START received				SR
			i2c_state = IDLE;
			i2c_continue();
			if (i2c_ST_SR_Done)//see if user attached a callback
			{
				i2c_ST_SR_Done();
			}
			break;
		case 0xA8:	// SLA+R received, Ack was send back				SR
		case 0xB0:	// arbitration lost (SLA+W/R). own SLA+R received, Ack was send	MT->ST
		case 0xB8:	// TWDR was send, Ack received					ST
			i2c_state = BUSY;
			TWDR = STbuffer[rwaddress++];
			i2c_continue();
			if (rwaddress >= STbuffsize)//wraps around if buffer is to small
			{
				rwaddress -= STbuffsize;
			}
			break;
		case 0xC0:	// TWDR was send, nAck received					ST
		case 0xC8:	// last TWDR was send, Ack received				ST
			i2c_continue();
			break;

		//-----------------------------------------------------------------------------------------/\ slave /\  |  \/ master \/

		case 0x08:	// START condition was send					MR
			i2c_state = BUSY;
			rwaddress = 0;
			TWDR = dest_SLA_RW & 0xFE;//write first
			i2c_continue();
			break;
		case 0x10:	// repeated START condition was send				MR
			TWDR = dest_SLA_RW;// SLA+R
			i2c_continue();
			rwaddress = 0;
			i2c_rw_amount--;// MR must end sooner than MT because MT can end whenever and MR must nACK first
			break;
		case 0x18:	// SLA+W sent, Ack was received					MT
			TWDR = destaddress;
			i2c_continue();
			break;
		case 0x28:	// TWDR was send, Ack received					MT
			if (dest_SLA_RW & 0x01)
			{
				TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);// send repeated START
				break;
			}
			if (rwaddress >= i2c_rw_amount)
			{
				i2c_stop();
				if (i2c_MT_MR_Done)//see if user attached a callback
				{
					i2c_MT_MR_Done();
				}
			}
			else
			{
				TWDR = MTbuffer[rwaddress++];
				i2c_continue();
			}
			break;
		case 0x40:	// SLA+R sent, Ack was received					MR
			if (rwaddress >= i2c_rw_amount)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
			}
			else
			{
				i2c_continue();
			}
			break;
		case 0x50:	// TWDR received, Ack was send back				MR
			MRbuffer[rwaddress++] = TWDR;
			if (rwaddress >= i2c_rw_amount)
			{
				TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);// next receive will not Ack'ed
			}
			else
			{
				i2c_continue();
			}
			break;
		case 0x58:	// TWDR received, nAck was send back				MR
			MRbuffer[rwaddress++] = TWDR;
			i2c_stop();
			if (i2c_MT_MR_Done)//see if user attached a callback
			{
				i2c_MT_MR_Done();
			}
			break;

		case 0x38:	// arbitration lost (SLA+W/R or data)				MT/MR
			i2c_continue();
			PORTB &= ~(1<<PB7); //arduinomega pin 13 led off
			i2c_state = IDLE;
			break;

		case 0x20:	// SLA+W sent, nAck was received				MT
		case 0x30:	// TWDR was send, nAck received					MT
		case 0x48:	// SLA+R sent, nAck was received				MR
		default:	// error (buserror)
			i2c_stop();
			if (i2c_error_call)//see if user attached a callback
			{
				i2c_error_call();
			}
			break;
	}
}
// i2c core /\ .
