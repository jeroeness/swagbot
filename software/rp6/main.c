#include "func_protos.h"

//extern union UID instructionData;
//extern union USD sensorData;

volatile uint8_t timer0OverflowCount = 0; //for timer overflow
volatile uint8_t timer0Overflow = 0; //for timer overflow

void initTimerMain(){
	//timer0: set prescaler of 1024
	TCCR0 |= (1 << CS00) | (1<<CS02);
	
	//timer0: init counter
	TCNT0 = 0;
	
	//timer0: enable overflow interrupt
	TIMSK |= (1 << TOIE0);
	
	//Set overflow variable to 0 (just to be sure)
	timer0Overflow = 0;
}


int main(void) {
	cli();
	
	initMotor();
	initSensors();
	i2c_init(0xAA);
	initTimerMain();
	
	sei();
	
	while(1) {
		if(timer0Overflow == 1){ //timed script sequence of 50ms
			timer0Overflow = 0;
			
			readSensors();
		}
	}
	
	return 0;
}




ISR(TIMER0_OVF_vect)
{
	timer0OverflowCount++;
	if(timer0OverflowCount == 1){
		TCNT0 = 122; //count from 122 to 256(overflow) to create pulse of 50ms
		}else{
		timer0Overflow = 1;
		timer0OverflowCount = 0;
	}
	
	//formula to check the number of milliseconds:
	//delay_in_seconds / (1/F_CPU*prescaler) - 1 = (0.050 / (1/8000000*1024) = 389.625
	//390.625 - 256 = 134,625 //need to overflow 1 and almost another half time
	// 256 - 133,625 = start value of timer on second interrupt = 122.375
	
	//complete formula: 256-(((0.050/(1/8000000*1024))-1)-256)
}
