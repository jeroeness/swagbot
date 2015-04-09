// ultrasonic_sensor.c
// v1.0

#include "../globalincsanddefs.h"

//extern union UID instructionData;
extern union USD sensorData;

void initUltrasonicSensor(void)
{
	DDRL &= ~(1 << PL1);
	PORTL &= ~(1 << PL1);
	sensorData.sensorStruct.ultrasonic = 0;
}

void UltrasonicSensorRead(void)
{
	DDRL |= (1 << PL1);
	PORTL &= ~(1 << PL1);//create a clean pulse
	_delay_us(2);
	PORTL |= (1 << PL1);
	_delay_us(5);
	PORTL &= ~(1 << PL1);
	DDRL &= ~(1 << PL1);

	//Timer5
	TCCR5A = (1 << WGM51) | (1 << WGM50);//wgm=15 fpwm ocr1a=top
	TCCR5B = (1 << ICNC5) | (0 << ICES5) | (1 << WGM53) | (1 << WGM52) | (0 << CS50);//falling edge, cs1 = div1	//todo: prescalervalue must be tested
	OCR5A = 0x4FFF;// timer TOP value
	TCNT5 = 0;
	
	
	
	uint16_t register timeoutcounter = 10000;//todo: calculate a good value
	
	while (!(PINL & (1 << PL1)))// wait for the pulse that needs to be measured  //can also be done with icr edge interrupt (see if this works first)
	{
		if (!timeoutcounter--)
		{
			//(can give error)
			
			sensorData.sensorStruct.ultrasonic = 255;
			return;
		}
		asm("nop");//a delay
	}
	
	TIFR5 = (1 << ICF5) | (1 << OCF5A);//clear flags
	TIMSK5 = (1 << ICIE5) | (1 << OCIE5A);//inputcapture interrupt and OCR5A(overflow) interrupt  on
	TCCR5B |= (1 << CS51);//start timer (cs = div8)
	return;
}

ISR(TIMER5_CAPT_vect)
{
	//the pulselength has been stored in ICR5
	
	sensorData.sensorStruct.ultrasonic = (uint8_t) (ICR5>>7) & 0xFF;//to 8bit value
	
	//timer offs
	TIMSK5 &= ~((1 << ICIE5) | (1 << OCIE5A));//inputcapture interrupt and OCR5A(overflow) interrupt  off
	TCCR5B &= ~((1 << CS51) | (1 << CS50));//start timer (cs = off)
}

ISR(TIMER5_COMPA_vect)
{
	//(sort of) the overflow, no pulse falingedge detected
	//(can give error)
	
	sensorData.sensorStruct.ultrasonic = 0;
	
	//timer off
	TIMSK5 &= ~((1 << ICIE5) | (1 << OCIE5A));//inputcapture interrupt and OCR5A(overflow) interrupt  off
	TCCR5B &= ~((1 << CS51) | (1 << CS50));//start timer (cs = off)
}
