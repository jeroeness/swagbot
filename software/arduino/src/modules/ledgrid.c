#include "../globalincsanddefs.h"
#include "ledgrid.h"

//extern union UID instructionData;
//extern union USD sensorData;

uint8_t currentFace = 0;

uint8_t previousFace = 10;
uint8_t CurrentPrintLine = 0;
uint8_t CurrentPrintColor = 0;

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
			clearDisplayData();
			gd[0][1] = 1; gd[0][2] = 1; gd[0][5] = 1; 
			gd[0][6] = 1; gd[1][0] = 1; gd[1][7] = 1; 
			gd[2][2] = 1; gd[2][5] = 1; gd[3][2] = 1; 
			gd[3][5] = 1; gd[5][0] = 1; gd[5][7] = 1; 
			gd[6][1] = 1; gd[6][6] = 1; gd[7][2] = 1; 
			gd[7][3] = 1; gd[7][4] = 1; gd[7][5] = 1; 
			break;
			
		case 1: //angry red face >:(
			clearDisplayData();
			rd[0][0] = 1; rd[0][1] = 1; rd[0][6] = 1; 
			rd[0][7] = 1; rd[1][2] = 1; rd[1][5] = 1; 
			rd[3][2] = 1; rd[3][5] = 1; rd[4][2] = 1; 
			rd[4][5] = 1; rd[6][1] = 1; rd[6][2] = 1; 
			rd[6][3] = 1; rd[6][4] = 1; rd[6][5] = 1; 
			rd[6][6] = 1; rd[7][0] = 1; rd[7][7] = 1; 
			break;
			
		case 2: //compass
			clearDisplayData();
			gd[0][2] = 1; bd[0][2] = 1; gd[0][3] = 1;
			bd[0][3] = 1; gd[0][4] = 1; bd[0][4] = 1;
			gd[0][5] = 1; bd[0][5] = 1; gd[1][1] = 1;
			bd[1][1] = 1; rd[1][5] = 1; gd[1][6] = 1;
			bd[1][6] = 1; gd[2][0] = 1; bd[2][0] = 1;
			rd[2][4] = 1; gd[2][7] = 1; bd[2][7] = 1;
			gd[3][0] = 1; bd[3][0] = 1; rd[3][4] = 1;
			gd[3][7] = 1; bd[3][7] = 1; gd[4][0] = 1;
			bd[4][0] = 1; rd[4][3] = 1; bd[4][3] = 1;
			gd[4][7] = 1; bd[4][7] = 1; gd[5][0] = 1;
			bd[5][0] = 1; rd[5][3] = 1; bd[5][3] = 1;
			gd[5][7] = 1; bd[5][7] = 1; gd[6][1] = 1;
			bd[6][1] = 1; rd[6][2] = 1; bd[6][2] = 1;
			gd[6][6] = 1; bd[6][6] = 1; gd[7][2] = 1;
			bd[7][2] = 1; gd[7][3] = 1; bd[7][3] = 1;
			gd[7][4] = 1; bd[7][4] = 1; gd[7][5] = 1;
			bd[7][5] = 1;
			break;
		
		case 3: //bumper (not pressed) Right
			clearDisplayData();
			rd[0][6] = 1; rd[0][7] = 1; rd[1][4] = 1;
			rd[1][5] = 1; rd[2][2] = 1; rd[2][3] = 1;
			rd[3][1] = 1; rd[4][0] = 1; rd[4][1] = 1;
			rd[4][2] = 1; rd[4][3] = 1; rd[4][4] = 1;
			rd[4][5] = 1; rd[4][6] = 1; rd[4][7] = 1;
			rd[5][0] = 1; rd[5][7] = 1; rd[6][0] = 1;
			rd[6][7] = 1; rd[7][0] = 1; rd[7][1] = 1;
			rd[7][2] = 1; rd[7][3] = 1; rd[7][4] = 1;
			rd[7][5] = 1; rd[7][6] = 1; rd[7][7] = 1;
			break;
		
		case 4: //bumper (pressed) Right
			clearDisplayData();
			gd[2][2] = 1; gd[2][3] = 1; gd[2][4] = 1;
			gd[2][5] = 1; gd[2][6] = 1; gd[2][7] = 1;
			gd[3][1] = 1; gd[4][0] = 1; gd[4][1] = 1;
			gd[4][2] = 1; gd[4][3] = 1; gd[4][4] = 1;
			gd[4][5] = 1; gd[4][6] = 1; gd[4][7] = 1;
			gd[5][0] = 1; gd[5][7] = 1; gd[6][0] = 1;
			gd[6][7] = 1; gd[7][0] = 1; gd[7][1] = 1;
			gd[7][2] = 1; gd[7][3] = 1; gd[7][4] = 1;
			gd[7][5] = 1; gd[7][6] = 1; gd[7][7] = 1;
			break;
		
		case 5:
			clearDisplayData();
			gd[0][0] = 1; gd[0][1] = 1; bd[0][2] = 1; 
			bd[0][3] = 1; bd[0][4] = 1; bd[0][5] = 1; 
			gd[0][6] = 1; gd[0][7] = 1; gd[1][0] = 1; 
			bd[1][1] = 1; bd[1][2] = 1; gd[1][3] = 1; 
			gd[1][4] = 1; bd[1][5] = 1; bd[1][6] = 1; 
			gd[1][7] = 1; bd[2][0] = 1; bd[2][1] = 1; 
			rd[2][2] = 1; gd[2][3] = 1; gd[2][4] = 1; 
			rd[2][5] = 1; bd[2][6] = 1; bd[2][7] = 1; 
			bd[3][0] = 1; gd[3][1] = 1; gd[3][2] = 1; 
			rd[3][3] = 1; rd[3][4] = 1; gd[3][5] = 1; 
			gd[3][6] = 1; bd[3][7] = 1; bd[4][0] = 1; 
			gd[4][1] = 1; gd[4][2] = 1; rd[4][3] = 1; 
			rd[4][4] = 1; gd[4][5] = 1; gd[4][6] = 1; 
			bd[4][7] = 1; bd[5][0] = 1; bd[5][1] = 1; 
			rd[5][2] = 1; gd[5][3] = 1; gd[5][4] = 1; 
			rd[5][5] = 1; bd[5][6] = 1; bd[5][7] = 1; 
			gd[6][0] = 1; bd[6][1] = 1; bd[6][2] = 1; 
			gd[6][3] = 1; gd[6][4] = 1; bd[6][5] = 1; 
			bd[6][6] = 1; gd[6][7] = 1; gd[7][0] = 1; 
			gd[7][1] = 1; bd[7][2] = 1; bd[7][3] = 1; 
			bd[7][4] = 1; bd[7][5] = 1; gd[7][6] = 1; 
			gd[7][7] = 1; 

 
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

uint8_t updateLedGrid(){
	setEmotion(currentFace);
	
	CurrentPrintColor++;
	if(CurrentPrintColor >= 3){
		CurrentPrintColor = 0;
		CurrentPrintLine++;
		if(CurrentPrintLine == 8) CurrentPrintLine = 0;
	}
	
	return pushArraysToGrid(CurrentPrintLine,CurrentPrintColor);
}

uint8_t pushArraysToGrid(uint8_t i, uint8_t c){
	//int8_t i = 0;
	int8_t j = 0;
	PORT_STROBE &= ~STROBE;
	uint8_t ledsOn = 0;
	
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
			if(gd[i][7-j] == 1 && c == 1){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
			if(gd[i][7-j] == 1 && c == 1){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
			if(bd[i][7-j] == 1 && c == 2){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
			if(bd[i][7-j] == 1 && c == 2){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
			if(rd[i][7-j] == 1 && c == 0){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
			if(rd[i][7-j] == 1 && c == 0){
				PORT_DATA &= ~DATA;
				//ledsOn++;
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
		//_delay_us(5);
		return ledsOn;
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