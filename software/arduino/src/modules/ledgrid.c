#include "../globalincsanddefs.h"
#include "ledgrid.h"

int16_t currentFace = -1;     //use this as extern to select an face. max value: 5. -1 for displayOff
int16_t currentSubFace = 0;  //use this as extern to select the subinterface of the face (for animation purposes). max value: 99 or the textlength

int16_t previousFace = 255;
int16_t previousSubFace = 255;
uint8_t CurrentPrintLine = 0;
uint8_t CurrentPrintColor = 0;

//much much better this way huh?
uint8_t rd[8] = {0,0,0,0,0,0,0,0};
uint8_t gd[8] = {0,0,0,0,0,0,0,0};
uint8_t bd[8] = {0,0,0,0,0,0,0,0};

//I want those 2 functions to be private
void pushArraysToGrid(uint8_t, uint8_t);
uint8_t printCharacter(uint8_t[], wchar_t, int8_t, int8_t);


char scrollText[100]; //current text to scroll
int16_t scrollLength; //text length (only calculate once)
uint8_t * scrollColor[100]; //the array with the color

void initLedGrid(void){
	DDR_STROBE |= STROBE; 
	DDR_DATA |= DATA;
	DDR_CLOCK |= CLOCK;
	DDR_POSITIVE |= POSITIVE;
	
	PORT_CLOCK &= ~CLOCK;
	PORT_STROBE &= ~STROBE;
	PORT_POSITIVE |= POSITIVE;
	
	//ledgrid drawing
	TCCR3B |= (1 << CS31) | (0<<CS30); //timer3: set prescaler of 8
	TCNT3 = 63000; //timer3: init counter
	TIMSK3 |= (1 << TOIE3); //timer3: enable overflow interrupt
	
	//scrolling text
	TCCR4B |= (1 << CS42) | (0<<CS40); //timer 4: prescaler of 256
	TCNT4 = 58000; //timer4: init counter differently than others to prevent simultaneously execution
	TIMSK4 |= (1 << TOIE4); //timer4: enable overflow interrupt
	
	setEmotion(0);
}

ISR(TIMER3_OVF_vect){
	updateLedGrid();
	TCNT3 = 65000;
}

ISR(TIMER4_OVF_vect){	
	updateScrollText();
	TCNT4 = 58000;
}


void clearDisplayData(void){
	uint8_t i = 0;
	for(i = 0; i < 8; i++){
		rd[i] = 0;
		gd[i] = 0;
		bd[i] = 0;
	}
}


void setEmotion(uint16_t em){
	currentFace = em;
	updateEmotion();
}

void setSubEmotion(uint16_t subem){
	currentSubFace = subem;
	updateEmotion();
}

void setScrollText(const char * text){
	uint8_t * currentColor = rd;
	uint8_t i = 0;
	uint8_t StringCounter = 0;
	uint8_t tmpStringLength = strlen(text);
	
	for(i = 0; i < tmpStringLength; i++){
		if(text[i] == '/'){
			i++;
			if(text[i] == 'r'){
				currentColor = rd;
			}else if(text[i] == 'g'){
				currentColor = gd;
			}else if(text[i] == 'b'){
				currentColor = bd;
			}
			continue;
		}else{
			scrollText[StringCounter] = text[i];
			scrollColor[StringCounter] = currentColor;
			StringCounter++;
		}
	}
	
	scrollText[StringCounter] = '\0';
	scrollLength = StringCounter;
	
	currentFace = 254; //scrolling text
	currentSubFace = 0; //what xOffset are we at?
	
	updateLedGrid();
}


void updateScrollText(void){
	if(currentFace == 254){
		currentSubFace++;
		updateEmotion();
	}
}

void updateEmotion(void){
	uint8_t num1 = 0;
	uint8_t num2 = 0;
	int8_t i = 0;
	int16_t offsetCount = 0;
	
	if(currentFace == previousFace && currentSubFace == previousSubFace) return;
	previousFace = currentFace;
	previousSubFace = currentSubFace;
			
	switch(currentFace){ //here some other faces or sensor stats!
		case -1://just clear the display
			clearDisplayData();
			break;
			
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
		
		case 254: //scrollable text
			clearDisplayData();
			for(i = 0; i < scrollLength; i++){
				offsetCount += printCharacter(scrollColor[i], scrollText[i], offsetCount - currentSubFace + 8, 1);
			}
			if(currentSubFace >= offsetCount+8){
				currentSubFace = 0;
			}
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

void updateLedGrid(void){
	CurrentPrintColor++;
	if(CurrentPrintColor >= 3){
		CurrentPrintColor = 0;
		CurrentPrintLine++;
		if(CurrentPrintLine == 8) CurrentPrintLine = 0;
	}
	
	pushArraysToGrid(CurrentPrintLine,CurrentPrintColor);
}


uint8_t printCharacter(uint8_t color[8], wchar_t character, int8_t xOffset, int8_t yOffset){
	int8_t x = 0;
	int8_t y = 0;
	uint8_t * letterbak;
	int8_t cw = 0; //CharWidth
	letterbak = (uint8_t[]) {0,0,0,0,0,0};
	
	switch(character){
		case 'A': letterbak = (uint8_t[]) {0x6, 0x6, 0x9, 0xF, 0x9, 0x0, 0x0}; cw = 5; break;
		case 'B': letterbak = (uint8_t[]) {0x7, 0x9, 0x7, 0x9, 0x7, 0x0, 0x0}; cw = 5; break;
		case 'C': letterbak = (uint8_t[]) {0x6, 0x9, 0x1, 0x9, 0x6, 0x0, 0x0}; cw = 5; break;
		case 'D': letterbak = (uint8_t[]) {0x7, 0x9, 0x9, 0x9, 0x7, 0x0, 0x0}; cw = 5; break;
		case 'E': letterbak = (uint8_t[]) {0x7, 0x1, 0x3, 0x1, 0x7, 0x0, 0x0}; cw = 4; break;
		case 'F': letterbak = (uint8_t[]) {0x7, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0}; cw = 4; break;
		case 'G': letterbak = (uint8_t[]) {0xE, 0x1, 0xD, 0x9, 0xE, 0x0, 0x0}; cw = 5; break;
		case 'H': letterbak = (uint8_t[]) {0x9, 0x9, 0xF, 0x9, 0x9, 0x0, 0x0}; cw = 5; break;
		case 'I': letterbak = (uint8_t[]) {0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0}; cw = 2; break;
		case 'J': letterbak = (uint8_t[]) {0x4, 0x4, 0x4, 0x5, 0x3, 0x0, 0x0}; cw = 4; break;
		case 'K': letterbak = (uint8_t[]) {0x9, 0x5, 0x3, 0x5, 0x9, 0x0, 0x0}; cw = 5; break;
		case 'L': letterbak = (uint8_t[]) {0x1, 0x1, 0x1, 0x1, 0x7, 0x0, 0x0}; cw = 4; break;
		case 'M': letterbak = (uint8_t[]) {0x11, 0x1B, 0x15, 0x11, 0x11, 0x0, 0x0}; cw = 6; break;
		case 'N': letterbak = (uint8_t[]) {0x9, 0xB, 0xD, 0x9, 0x9, 0x0, 0x0}; cw = 5; break;
		case 'O': letterbak = (uint8_t[]) {0x6, 0x9, 0x9, 0x9, 0x6, 0x0, 0x0}; cw = 5; break;
		case 'P': letterbak = (uint8_t[]) {0x7, 0x9, 0x7, 0x1, 0x1, 0x0, 0x0}; cw = 5; break;
		case 'Q': letterbak = (uint8_t[]) {0x6, 0x9, 0x9, 0x5, 0xA, 0x0, 0x0}; cw = 5; break;
		case 'R': letterbak = (uint8_t[]) {0x7, 0x9, 0x7, 0x9, 0x9, 0x0, 0x0}; cw = 5; break;
		case 'S': letterbak = (uint8_t[]) {0xE, 0x1, 0x6, 0x8, 0x7, 0x0, 0x0}; cw = 5; break;
		case 'T': letterbak = (uint8_t[]) {0x7, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0}; cw = 4; break;
		case 'U': letterbak = (uint8_t[]) {0x9, 0x9, 0x9, 0x9, 0x6, 0x0, 0x0}; cw = 5; break;
		case 'V': letterbak = (uint8_t[]) {0x5, 0x5, 0x5, 0x2, 0x2, 0x0, 0x0}; cw = 4; break;
		case 'W': letterbak = (uint8_t[]) {0x11, 0x15, 0x15, 0xA, 0xA, 0x0, 0x0}; cw = 6; break;
		case 'X': letterbak = (uint8_t[]) {0x5, 0x5, 0x2, 0x5, 0x5, 0x0, 0x0}; cw = 4; break;
		case 'Y': letterbak = (uint8_t[]) {0x5, 0x5, 0x2, 0x2, 0x2, 0x0, 0x0}; cw = 4; break;
		case 'Z': letterbak = (uint8_t[]) {0x7, 0x4, 0x2, 0x1, 0x7, 0x0, 0x0}; cw = 4; break;
		case 'a': letterbak = (uint8_t[]) {0x0, 0x0, 0x6, 0x5, 0x6, 0x0, 0x0}; cw = 4; break;
		case 'b': letterbak = (uint8_t[]) {0x1, 0x1, 0x3, 0x5, 0x3, 0x0, 0x0}; cw = 4; break;
		case 'c': letterbak = (uint8_t[]) {0x0, 0x0, 0x6, 0x1, 0x6, 0x0, 0x0}; cw = 4; break;
		case 'd': letterbak = (uint8_t[]) {0x4, 0x4, 0x6, 0x5, 0x6, 0x0, 0x0}; cw = 4; break;
		case 'e': letterbak = (uint8_t[]) {0x0, 0x0, 0x2, 0x5, 0x3, 0x0, 0x0}; cw = 4; break;
		case 'f': letterbak = (uint8_t[]) {0x2, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0}; cw = 3; break;
		case 'g': letterbak = (uint8_t[]) {0x0, 0x0, 0x6, 0x5, 0x6, 0x4, 0x0}; cw = 4; break;
		case 'h': letterbak = (uint8_t[]) {0x1, 0x1, 0x3, 0x5, 0x5, 0x0, 0x0}; cw = 4; break;
		case 'i': letterbak = (uint8_t[]) {0x1, 0x0, 0x1, 0x1, 0x1, 0x0, 0x0}; cw = 2; break;
		case 'j': letterbak = (uint8_t[]) {0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x0}; cw = 2; break;
		case 'k': letterbak = (uint8_t[]) {0x1, 0x1, 0x5, 0x3, 0x5, 0x0, 0x0}; cw = 4; break;
		case 'l': letterbak = (uint8_t[]) {0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0}; cw = 2; break;
		case 'm': letterbak = (uint8_t[]) {0x0, 0x0, 0xF, 0x15, 0x15, 0x0, 0x0}; cw = 6; break;
		case 'n': letterbak = (uint8_t[]) {0x0, 0x0, 0x3, 0x5, 0x5, 0x0, 0x0}; cw = 4; break;
		case 'o': letterbak = (uint8_t[]) {0x0, 0x0, 0x7, 0x5, 0x7, 0x0, 0x0}; cw = 4; break;
		case 'p': letterbak = (uint8_t[]) {0x0, 0x0, 0x3, 0x5, 0x3, 0x1, 0x0}; cw = 4; break;
		case 'q': letterbak = (uint8_t[]) {0x0, 0x0, 0x6, 0x5, 0x6, 0x4, 0x0}; cw = 4; break;
		case 'r': letterbak = (uint8_t[]) {0x0, 0x0, 0x3, 0x1, 0x1, 0x0, 0x0}; cw = 3; break;
		case 's': letterbak = (uint8_t[]) {0x0, 0x0, 0x3, 0x1, 0x1, 0x0, 0x0}; cw = 3; break;
		case 't': letterbak = (uint8_t[]) {0x0, 0x1, 0x3, 0x1, 0x2, 0x0, 0x0}; cw = 3; break;
		case 'u': letterbak = (uint8_t[]) {0x0, 0x0, 0x5, 0x5, 0x6, 0x0, 0x0}; cw = 4; break;
		case 'v': letterbak = (uint8_t[]) {0x0, 0x0, 0x5, 0x5, 0x2, 0x0, 0x0}; cw = 4; break;
		case 'w': letterbak = (uint8_t[]) {0x0, 0x0, 0x9, 0x9, 0xF, 0x0, 0x0}; cw = 5; break;
		case 'x': letterbak = (uint8_t[]) {0x0, 0x0, 0x5, 0x2, 0x5, 0x0, 0x0}; cw = 4; break;
		case 'y': letterbak = (uint8_t[]) {0x0, 0x0, 0x5, 0x2, 0x2, 0x1, 0x0}; cw = 4; break;
		case 'z': letterbak = (uint8_t[]) {0x0, 0x0, 0x7, 0x2, 0x7, 0x0, 0x0}; cw = 4; break;
		case ' ': letterbak = (uint8_t[]) {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}; cw = 1; break;
		case '0': letterbak = (uint8_t[]) {0x2, 0x5, 0x5, 0x5, 0x2, 0x0, 0x0}; cw = 4; break;
		case '1': letterbak = (uint8_t[]) {0x2, 0x3, 0x2, 0x2, 0x2, 0x0, 0x0}; cw = 3; break;
		case '2': letterbak = (uint8_t[]) {0x3, 0x4, 0x2, 0x1, 0x7, 0x0, 0x0}; cw = 4; break;
		case '3': letterbak = (uint8_t[]) {0x3, 0x4, 0x2, 0x4, 0x3, 0x0, 0x0}; cw = 4; break;
		case '4': letterbak = (uint8_t[]) {0x4, 0x6, 0x5, 0x7, 0x4, 0x0, 0x0}; cw = 4; break;
		case '5': letterbak = (uint8_t[]) {0x7, 0x1, 0x7, 0x4, 0x3, 0x0, 0x0}; cw = 4; break;
		case '6': letterbak = (uint8_t[]) {0x2, 0x1, 0x3, 0x5, 0x2, 0x0, 0x0}; cw = 4; break;
		case '7': letterbak = (uint8_t[]) {0x7, 0x4, 0x2, 0x2, 0x2, 0x0, 0x0}; cw = 4; break;
		case '8': letterbak = (uint8_t[]) {0x2, 0x5, 0x2, 0x5, 0x2, 0x0, 0x0}; cw = 4; break;
		case '9': letterbak = (uint8_t[]) {0x2, 0x5, 0x7, 0x4, 0x2, 0x0, 0x0}; cw = 4; break;
		case '-': letterbak = (uint8_t[]) {0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0}; cw = 3; break;
		case '+': letterbak = (uint8_t[]) {0x0, 0x2, 0x7, 0x2, 0x0, 0x0, 0x0}; cw = 4; break;
		case '_': letterbak = (uint8_t[]) {0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0}; cw = 4; break;
		case '=': letterbak = (uint8_t[]) {0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0}; cw = 3; break;
		case '!': letterbak = (uint8_t[]) {0x1, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0}; cw = 2; break;
		case '?': letterbak = (uint8_t[]) {0x1, 0x2, 0x1, 0x0, 0x1, 0x0, 0x0}; cw = 3; break;
		case '/': letterbak = (uint8_t[]) {0x2, 0x2, 0x3, 0x1, 0x1, 0x0, 0x0}; cw = 3; break;
		case '\\': letterbak = (uint8_t[]) {0x1, 0x1, 0x3, 0x2, 0x2, 0x0, 0x0}; cw = 3; break;
		case '|': letterbak = (uint8_t[]) {0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0}; cw = 2; break;
		case '<': letterbak = (uint8_t[]) {0x0, 0x0, 0x2, 0x1, 0x2, 0x0, 0x0}; cw = 3; break;
		case '>': letterbak = (uint8_t[]) {0x0, 0x0, 0x1, 0x2, 0x1, 0x0, 0x0}; cw = 3; break;
		case '[': letterbak = (uint8_t[]) {0x3, 0x1, 0x1, 0x1, 0x1, 0x3, 0x0}; cw = 3; break;
		case ']': letterbak = (uint8_t[]) {0x3, 0x2, 0x2, 0x2, 0x2, 0x3, 0x0}; cw = 3; break;
		case '(': letterbak = (uint8_t[]) {0x2, 0x1, 0x1, 0x1, 0x1, 0x2, 0x0}; cw = 3; break;
		case ')': letterbak = (uint8_t[]) {0x1, 0x2, 0x2, 0x2, 0x2, 0x1, 0x0}; cw = 3; break;

		default:
			letterbak = (uint8_t[]) {0xF,0xF,0xF,0xF,0xF,0xF}; cw = 4; break;
			break;
	}
	
	if(xOffset < -3 && xOffset > 9) return cw;
	
	for(y = 0; y < 6; y++){
		for(x = 0; x < cw; x++){
			if(letterbak[y] & (1<<x)){
				if((y+yOffset) > -1 && (y+yOffset) < 8 && (x+xOffset) > -1 && (x+xOffset) < 8){
					color[y+yOffset] |= 1<<(x+xOffset);
				}
			}
		}

	}
	
	return cw;
}

void pushArraysToGrid(uint8_t i, uint8_t c){
	int8_t j = 0;
	
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
			
	for(j = 4; j < 8; j++){ //green second part
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
			
	for(j = 0; j < 4; j++){ //green fisrt part
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
}

