#include "../globalincsanddefs.h"
#include "ledgrid.h"

//extern union UID instructionData;
//extern union USD sensorData;

uint8_t currentFace = 0;     //use this as extern to select an face. max value: 5
uint8_t currentSubFace = 0;  //use this as extern to select the subinterface of the face (for animation purposes). max value: 99

uint8_t previousFace = 255;
uint8_t previousSubFace = 255;
uint8_t CurrentPrintLine = 0;
uint8_t CurrentPrintColor = 0;

//much much better this way huh?
uint8_t rd[8] = {0,0,0,0,0,0,0,0};
uint8_t gd[8] = {0,0,0,0,0,0,0,0};
uint8_t bd[8] = {0,0,0,0,0,0,0,0};

/*
uint8_t letterbak[36][5] = {0,
							0,
							0,
							0,
							0}
*/



void printCharacter(uint8_t color[8], wchar_t character, uint8_t xOffset, uint8_t yOffset){
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t * letterbak;
	letterbak = (uint8_t[]) {0,0,0,0,0};

	switch(character){
		case 'A': letterbak = (uint8_t[]) {0x6,0x6,0x9,0xF,0x9}; break;
		case 'B': letterbak = (uint8_t[]) {0x7,0x9,0x7,0x9,0x7}; break;
		case 'C': letterbak = (uint8_t[]) {0x6,0x9,0x1,0x9,0x6}; break;
		case 'D': letterbak = (uint8_t[]) {0x7,0x9,0x9,0x9,0x7}; break;
		case 'E': letterbak = (uint8_t[]) {0x7,0x1,0x3,0x1,0x7}; break;
		case 'F': letterbak = (uint8_t[]) {0x7,0x1,0x3,0x1,0x1}; break;
		case 'G': letterbak = (uint8_t[]) {0xE,0x1,0xD,0x9,0xE}; break;
		case 'H': letterbak = (uint8_t[]) {0x9,0x9,0xF,0x9,0x9}; break;
		case 'I': letterbak = (uint8_t[]) {0x1,0x1,0x1,0x1,0x1}; break;
		case 'J': letterbak = (uint8_t[]) {0x4,0x4,0x4,0x5,0x3}; break;
		case 'K': letterbak = (uint8_t[]) {0x9,0x5,0x3,0x5,0x9}; break;
		case 'L': letterbak = (uint8_t[]) {0x1,0x1,0x1,0x1,0x7}; break;
		case 'M': letterbak = (uint8_t[]) {0x1,0xB,0x5,0x1,0x1}; break;
		case 'N': letterbak = (uint8_t[]) {0x9,0xB,0xD,0x9,0x9}; break;
		case 'O': letterbak = (uint8_t[]) {0x6,0x9,0x9,0x9,0x6}; break;
		case 'P': letterbak = (uint8_t[]) {0x7,0x9,0x7,0x1,0x1}; break;
		case 'Q': letterbak = (uint8_t[]) {0x6,0x9,0x9,0x5,0xA}; break;
		case 'R': letterbak = (uint8_t[]) {0x7,0x9,0x7,0x9,0x9}; break;
		case 'S': letterbak = (uint8_t[]) {0xE,0x1,0x6,0x8,0x7}; break;
		case 'T': letterbak = (uint8_t[]) {0x7,0x2,0x2,0x2,0x2}; break;
		case 'U': letterbak = (uint8_t[]) {0x9,0x9,0x9,0x9,0x6}; break;
		case 'V': letterbak = (uint8_t[]) {0x5,0x5,0x5,0x2,0x2}; break;
		case 'W': letterbak = (uint8_t[]) {0x1,0x5,0x5,0xA,0xA}; break;
		case 'X': letterbak = (uint8_t[]) {0x5,0x5,0x2,0x5,0x5}; break;
		case 'Y': letterbak = (uint8_t[]) {0x5,0x5,0x2,0x2,0x2}; break;
		case 'Z': letterbak = (uint8_t[]) {0x7,0x4,0x2,0x1,0x7}; break;
		case ' ': letterbak = (uint8_t[]) {0x0,0x0,0x0,0x0,0x0}; break;
		case '0': letterbak = (uint8_t[]) {0x2,0x5,0x5,0x5,0x2}; break;
		case '1': letterbak = (uint8_t[]) {0x2,0x3,0x2,0x2,0x2}; break;
		case '2': letterbak = (uint8_t[]) {0x3,0x4,0x2,0x1,0x7}; break;
		case '3': letterbak = (uint8_t[]) {0x3,0x4,0x2,0x4,0x3}; break;
		case '4': letterbak = (uint8_t[]) {0x4,0x6,0x5,0x7,0x4}; break;
		case '5': letterbak = (uint8_t[]) {0x7,0x1,0x7,0x4,0x3}; break;
		case '6': letterbak = (uint8_t[]) {0x2,0x1,0x3,0x5,0x2}; break;
		case '7': letterbak = (uint8_t[]) {0x7,0x4,0x2,0x2,0x2}; break;
		case '8': letterbak = (uint8_t[]) {0x2,0x5,0x2,0x5,0x2}; break;
		case '9': letterbak = (uint8_t[]) {0x2,0x5,0x7,0x4,0x2}; break;
		case '-': letterbak = (uint8_t[]) {0x0,0x0,0x3,0x0,0x0}; break;
		case '+': letterbak = (uint8_t[]) {0x0,0x2,0x7,0x2,0x0}; break;
		case '_': letterbak = (uint8_t[]) {0x0,0x0,0x0,0x0,0x0}; break;
		case '=': letterbak = (uint8_t[]) {0x0,0x0,0x0,0x3,0x0}; break;
		case '!': letterbak = (uint8_t[]) {0x1,0x1,0x1,0x0,0x1}; break;
		case '?': letterbak = (uint8_t[]) {0x1,0x2,0x1,0x0,0x1}; break;
		case '/': letterbak = (uint8_t[]) {0x2,0x2,0x3,0x1,0x1}; break;
		case '\\': letterbak = (uint8_t[]) {0x1,0x1,0x3,0x2,0x2}; break;
		case '|': letterbak = (uint8_t[]) {0x1,0x1,0x1,0x1,0x1}; break;
		case '<': letterbak = (uint8_t[]) {0x0,0x0,0x2,0x1,0x2}; break;
		case '>': letterbak = (uint8_t[]) {0x0,0x0,0x1,0x2,0x1}; break;
	
		default:
			letterbak = (uint8_t[]) {0xF,0xF,0xF,0xF,0xF}; break;
			break;
	}
	
	for(y = 0; y < 5; y++){
		for(x = 0; x < 5; x++){
			if(letterbak[y] & 1<<x){
				color[y+yOffset] |= 1<<(x+xOffset);
			}
		}
				
	}
			
	//free(letterbak);
}


void initLedGrid(){
	DDR_STROBE |= STROBE; 
	DDR_DATA |= DATA;
	DDR_CLOCK |= CLOCK;
	DDR_POSITIVE |= POSITIVE;
	
	PORT_CLOCK &= ~CLOCK;
	PORT_STROBE &= ~STROBE;
	PORT_POSITIVE |= POSITIVE;
}

void setEmotion(){
	uint8_t num1 = 0;
	uint8_t num2 = 0;
	
	if(currentFace == previousFace && currentSubFace == previousSubFace) return;
	previousFace = currentFace;
	previousSubFace = currentSubFace;
			
	switch(currentFace){ //here some other faces or sensor stats!
		case 0: //green SMILEY!!! <:)
			clearDisplayData();
			gd[0] = 0x66; gd[1] = 0x81; gd[2] = 0x24; 
			gd[3] = 0x24; gd[5] = 0x81; gd[6] = 0x42; 
			gd[7] = 0x3C; 
			break;
			
		case 1: //angry red face >:(
			clearDisplayData();
			rd[0] = 0x81; rd[1] = 0x66; rd[3] = 0x24; 
			rd[4] = 0x24; rd[6] = 0x7E; rd[7] = 0x81; 
			break;
			
		case 2: //compass
			clearDisplayData();
			gd[0] = 0x3C; gd[1] = 0x42; rd[2] = 0x60; 
			gd[2] = 0x81; rd[3] = 0x18; gd[3] = 0x81; 
			gd[4] = 0x81; bd[4] = 0x18; gd[5] = 0x81; 
			bd[5] = 0x6; gd[6] = 0x42; gd[7] = 0x3C; 
			break;
		
		case 3: //bumper (not pressed) Right
			clearDisplayData();
			rd[0] = 0xC0; rd[1] = 0x30; rd[2] = 0xC; 
			rd[3] = 0x2; rd[4] = 0xFF; rd[5] = 0x81; 
			rd[6] = 0x81; rd[7] = 0xFF; 
			break;
		
		case 4: //bumper (pressed) Right
			clearDisplayData();
			gd[2] = 0xFC; gd[3] = 0x2; gd[4] = 0xFF; 
			gd[5] = 0x81; gd[6] = 0x81; gd[7] = 0xFF; 
			break;
		
		case 5: //display numbers 
			clearDisplayData();
			num1 = currentSubFace / 10;
			num2 = currentSubFace % 10;
			printCharacter(rd, num1 + '0', 0, 2);
			printCharacter(gd, num2 + '0', 4, 2);
			break;
			
		default: //unknown face? Question Mark ??????
			clearDisplayData();
			gd[0] = 0x38; bd[0] = 0xC7; gd[1] = 0x44; 
			bd[1] = 0xBB; gd[2] = 0x40; bd[2] = 0xBF; 
			gd[3] = 0x20; bd[3] = 0xDF; gd[4] = 0x10; 
			bd[4] = 0xEF; gd[5] = 0x10; bd[5] = 0xEF; 
			bd[6] = 0xFF; gd[7] = 0x10; bd[7] = 0xEF; 

			break;
	}
}

uint8_t updateLedGrid(){
	setEmotion();
	
	CurrentPrintColor++;
	if(CurrentPrintColor >= 3){
		CurrentPrintColor = 0;
		CurrentPrintLine++;
		if(CurrentPrintLine == 8) CurrentPrintLine = 0;
	}
	
	return pushArraysToGrid(CurrentPrintLine,CurrentPrintColor);
}

uint8_t pushArraysToGrid(uint8_t i, uint8_t c){
	int8_t j = 0;
	uint8_t ledsOn = 0;
	
	PORT_STROBE &= ~STROBE; //prevent bits from flowing into output
	
	for(j = 4; j < 8; j++){ //turn row on first part
		if(j == i){
			PORT_DATA |= DATA;
		}else{
			PORT_DATA &= ~DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}
			
	for(j = 4; j < 8; j++){ //green first part
		if((gd[i] & (1 << (7-j))) && c == 1){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}
			
	for(j = 0; j < 4; j++){ //turn row on second part
		if(j == i){
			PORT_DATA |= DATA;
		}else{
			PORT_DATA &= ~DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}	
			
	for(j = 0; j < 4; j++){ //green second part
		if((gd[i] & (1 << (7-j))) && c == 1){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}
			
	for(j = 4; j < 8; j++){ //blue second part
		if((bd[i] & (1 << (7-j))) && c == 2){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}
			
	for(j = 0; j < 4; j++){ //blue first part
		if((bd[i] & (1 << (7-j))) && c == 2){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}	
			
	for(j = 4; j < 8; j++){ //red second part
		if((rd[i] & (1 << (7-j))) && c == 0){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}
			
	for(j = 0; j < 4; j++){ //red first part
		if((rd[i] & (1 << (7-j))) && c == 0){
			PORT_DATA &= ~DATA;
		}else{
			PORT_DATA |= DATA;
		}
		PORT_CLOCK |= CLOCK;
		PORT_CLOCK &= ~CLOCK;
	}

	PORT_STROBE |= STROBE;
	return ledsOn;
}

void clearDisplayData(){
	uint8_t i = 0;
	for(i = 0; i < 8; i++){
		rd[i] = 0;
		gd[i] = 0;
		bd[i] = 0;
	}
}