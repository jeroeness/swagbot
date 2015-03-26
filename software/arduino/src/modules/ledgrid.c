#include "../globalincsanddefs.h"
#include "ledgrid.h"

//extern union UID instructionData;
//extern union USD sensorData;

uint8_t currentFace = 0;

uint8_t previousFace = 10;
uint8_t CurrentPrintLine = 0;

uint8_t rd[8][8] = {{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}};

uint8_t gd[8][8] = {{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}};

uint8_t bd[8][8] = {{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}};
						
void initLedGrid(){
	DDR_STROBE |= STROBE; //pin53 (Strobe)
	DDR_DATA |= DATA; //DATA_RED | DATA_GREEN | DATA_BLUE; //pin52,51,50 (Data)
	
	//DDR_OUTPUT_ENABLE |= OUTPUT_ENABLE; //pin30 (OutputEnable)
	DDR_CLOCK |= CLOCK; //pin31 (Clock)
	
	PORT_CLOCK &= ~CLOCK;
	
}

void setEmotion(uint8_t num){
	if(num == previousFace) return;
	previousFace = num;
	
	switch(num){ //here some other faces or sensor stats!
		case 0: //green SMILEY!!! <:)
			gd[0][1] = 1; gd[0][2] = 1; gd[0][5] = 1; 
			gd[0][6] = 1; gd[1][0] = 1; gd[1][7] = 1; 
			gd[2][2] = 1; gd[2][5] = 1; gd[3][2] = 1; 
			gd[3][5] = 1; gd[5][0] = 1; gd[5][7] = 1; 
			gd[6][1] = 1; gd[6][6] = 1; gd[7][2] = 1; 
			gd[7][3] = 1; gd[7][4] = 1; gd[7][5] = 1; 
			break;
			
		case 1: //angry red face >:(
			rd[0][0] = 1; rd[0][1] = 1; rd[0][6] = 1; 
			rd[0][7] = 1; rd[1][2] = 1; rd[1][5] = 1; 
			rd[3][2] = 1; rd[3][5] = 1; rd[4][2] = 1; 
			rd[4][5] = 1; rd[6][1] = 1; rd[6][2] = 1; 
			rd[6][3] = 1; rd[6][4] = 1; rd[6][5] = 1; 
			rd[6][6] = 1; rd[7][0] = 1; rd[7][7] = 1; 
			break;
			
		default: //unknown face? Question Mark ??????
			clearDisplayData();
			bd[1][2] = 1; rd[0][4] = 1; rd[2][6] = 1;
			gd[2][2] = 1; gd[0][5] = 1; gd[3][5] = 1;
			bd[0][3] = 1; bd[1][6] = 1; bd[4][4] = 1;
			rd[5][4] = 1; gd[7][4] = 1;
			break;
	}
}

void updateLedGrid(){
	setEmotion(currentFace);
	
	pushArraysToGrid(CurrentPrintLine++);
	if(CurrentPrintLine == 8) CurrentPrintLine = 0;
}

void pushArraysToGrid(uint8_t i){
	//int8_t i = 0;
	int8_t j = 0;
	
	//for(i = 0; i < 8; i++){
		for(j = 4; j < 8; j++){ //turn row on first part
			if(j == i){
				PORT_DATA |= DATA;
			}else{
				PORT_DATA &= ~DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
		for(j = 4; j < 8; j++){ //green first part
			if(gd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
		for(j = 0; j < 4; j++){ //turn row on second part
			if(j == i){
				PORT_DATA |= DATA;
			}else{
				PORT_DATA &= ~DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
			
		for(j = 0; j < 4; j++){ //green second part
			if(gd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
		for(j = 4; j < 8; j++){ //blue
			if(bd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
				
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
		for(j = 0; j < 4; j++){ //blue
			if(bd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
			
		for(j = 4; j < 8; j++){ //red
			if(rd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}
			
		for(j = 0; j < 4; j++){ //red
			if(rd[i][7-j] == 1){
				PORT_DATA &= ~DATA;
			}else{
				PORT_DATA |= DATA;
			}
			//_delay_us(10);
			PORT_CLOCK |= CLOCK;
			//_delay_us(10);
			PORT_CLOCK &= ~CLOCK;
			//_delay_us(10);
		}

		PORT_STROBE |= STROBE;
		_delay_us(10);
		PORT_STROBE &= ~STROBE;
	//}
}

void clearDisplayData(){
	uint8_t i = 0;
	uint8_t j = 0;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			rd[i][j] = 0;
			gd[i][j] = 0;
			bd[i][j] = 0;
		}
	}
}