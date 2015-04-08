#include "../globalincsanddefs.h"
#include "ledgrid.h"

int16_t currentFace = -1;     //use this as extern to select an face. max value: 5. -1 for displayOff
int16_t currentSubFace = 0;  //use this as extern to select the subinterface of the face (for animation purposes). max value: 99 or the textlength

int16_t previousFace = 255;
int16_t previousSubFace = 255;
uint8_t currentPrintLine = 0;
uint8_t currentPrintColor = 0;

uint8_t refreshColors[3] = {0,0,0};
uint8_t refreshColorNum = 0;

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

void setNextSubEmotion(void){
	currentSubFace++;
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
			rd[1] = 0x24; rd[2] = 0x24; rd[5] = 0x3C;
			rd[6] = 0x42; rd[7] = 0x81;
			break;
			
		case 2: //compass
			clearDisplayData();
			
			if(currentSubFace > 23){ currentSubFace = 0;}
			clearDisplayData();
			
			gd[0] = 0x3E; gd[1] = 0x41; gd[2] = 0x41;
			gd[3] = 0x41; gd[4] = 0x41; gd[5] = 0x41;
			gd[6] = 0x3E;
			
			switch(currentSubFace){
				case 0: rd[1] |= 0x8; rd[2] |= 0x8; rd[3] |= 0x8;  break;
				case 1: rd[1] |= 0x10; rd[2] |= 0x8; rd[3] |= 0x8;  break;
				case 2: rd[1] |= 0x10; rd[2] |= 0x10; rd[3] |= 0x8; break;
				case 3: rd[1] |= 0x20; rd[2] |= 0x10; rd[3] |= 0x8;  break;
				case 4: rd[2] |= 0x30; rd[3] |= 0x8;  break;
				case 5: rd[2] |= 0x20; rd[3] |= 0x18;  break;
				case 6: rd[3] |= 0x38;  break;
				case 7: rd[3] |= 0x18; rd[4] |= 0x20;  break;
				case 8: rd[3] |= 0x8; rd[4] |= 0x30;  break;
				case 9: rd[3] |= 0x8; rd[4] |= 0x10; rd[5] |= 0x20;  break;
				case 10: rd[3] |= 0x8; rd[4] |= 0x10; rd[5] |= 0x10;  break;
				case 11: rd[3] |= 0x8; rd[4] |= 0x8; rd[5] |= 0x10;  break;
				case 12: rd[3] |= 0x8; rd[4] |= 0x8; rd[5] |= 0x8;  break;
				case 13: rd[3] |= 0x8; rd[4] |= 0x8; rd[5] |= 0x4;  break;
				case 14: rd[3] |= 0x8; rd[4] |= 0x4; rd[5] |= 0x4;  break;
				case 15: rd[3] |= 0x8; rd[4] |= 0x4; rd[5] |= 0x2;  break;
				case 16: rd[3] |= 0x8; rd[4] |= 0x6;  break;
				case 17: rd[3] |= 0xC; rd[4] |= 0x2;  break;
				case 18: rd[3] |= 0xE;  break;
				case 19: rd[2] |= 0x2; rd[3] |= 0xC;  break;
				case 20: rd[2] |= 0x6; rd[3] |= 0x8;  break;
				case 21: rd[1] |= 0x2; rd[2] |= 0x4; rd[3] |= 0x8;  break;
				case 22: rd[1] |= 0x4; rd[2] |= 0x4; rd[3] |= 0x8;  break;
				case 23: rd[1] |= 0x4; rd[2] |= 0x8; rd[3] |= 0x8;  break;
			}
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
			
		case 6: // IT'S A ME, MARIO!
			clearDisplayData();
			rd[0] = 0xFF; gd[0] = 0xC3; bd[0] = 0xC3; 
			rd[1] = 0xFF; gd[1] = 0xA3; bd[1] = 0xA3; 
			rd[2] = 0xD7; gd[2] = 0xD7; bd[2] = 0xEB; 
			rd[3] = 0xCF; gd[3] = 0xCF; bd[3] = 0xC3; 
			rd[4] = 0xDB; gd[4] = 0x81; bd[4] = 0x24; 
			rd[5] = 0xC3; gd[5] = 0xC3; bd[5] = 0xFF; 
			rd[6] = 0xC3; gd[6] = 0xC3; bd[6] = 0xFF; 
			rd[7] = 0xDB; gd[7] = 0xDB; bd[7] = 0xDB; 
			break;
		
		case 7: // Space invaders (animated) alien 1
			if(currentSubFace > 1){ currentSubFace = 0;}
			clearDisplayData();
			switch(currentSubFace){
				case 0:
					gd[0] = 0x18; gd[1] = 0x3C; gd[2] = 0x7E; 
					gd[3] = 0xDB; gd[4] = 0xFF; gd[5] = 0x5A; 
					gd[6] = 0x81; gd[7] = 0x42; 
					break;
					
				case 1:
					gd[0] = 0x18; gd[1] = 0x3C; gd[2] = 0x7E; 
					gd[3] = 0xDB; gd[4] = 0xFF; gd[5] = 0x24; 
					gd[6] = 0x5A; gd[7] = 0xA5; 
					break;
			}
					
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
	
	checkColorBrightness();
}

void checkColorBrightness(void){
	uint8_t i = 0;
	uint16_t colorR = 0;
	uint16_t colorG = 0;
	uint16_t colorB = 0;
	
	for(i = 0; i < 8; i++){
		colorR += rd[i];
		colorG += gd[i];
		colorB += bd[i];
	}
	
	refreshColorNum = 0;
	
	if(colorR > 0){
		refreshColors[refreshColorNum] = 0;
		refreshColorNum++;
	}
	if(colorG > 0){
		refreshColors[refreshColorNum] = 1;
		refreshColorNum++;
	}
	if(colorB > 0){
		refreshColors[refreshColorNum] = 2;
		refreshColorNum++;
	}
}

void updateLedGrid(void){
	currentPrintColor++;
	if(currentPrintColor >= refreshColorNum){
		currentPrintColor = 0;
		currentPrintLine++;
		if(currentPrintLine == 8) currentPrintLine = 0;
	}
	
	pushArraysToGrid(currentPrintLine,refreshColors[currentPrintColor]);
}


uint8_t printCharacter(uint8_t color[8], wchar_t character, int8_t xOffset, int8_t yOffset){
	int8_t x = 0;
	int8_t y = 0;
	uint8_t lb[6] = {0,0,0,0,0,0};
	int8_t cw = 0; //CharWidth
	
	switch(character){
		case 'A': lb[0] = 0x6; lb[1] = 0x6; lb[2] = 0x9; lb[3] = 0xF; lb[4] = 0x9;  cw = 5; break;
		case 'B': lb[0] = 0x7; lb[1] = 0x9; lb[2] = 0x7; lb[3] = 0x9; lb[4] = 0x7;  cw = 5; break;
		case 'C': lb[0] = 0x6; lb[1] = 0x9; lb[2] = 0x1; lb[3] = 0x9; lb[4] = 0x6;  cw = 5; break;
		case 'D': lb[0] = 0x7; lb[1] = 0x9; lb[2] = 0x9; lb[3] = 0x9; lb[4] = 0x7;  cw = 5; break;
		case 'E': lb[0] = 0x7; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x7;  cw = 4; break;
		case 'F': lb[0] = 0x7; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x1;  cw = 4; break;
		case 'G': lb[0] = 0xE; lb[1] = 0x1; lb[2] = 0xD; lb[3] = 0x9; lb[4] = 0xE;  cw = 5; break;
		case 'H': lb[0] = 0x9; lb[1] = 0x9; lb[2] = 0xF; lb[3] = 0x9; lb[4] = 0x9;  cw = 5; break;
		case 'I': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1;  cw = 2; break;
		case 'J': lb[0] = 0x4; lb[1] = 0x4; lb[2] = 0x4; lb[3] = 0x5; lb[4] = 0x3;  cw = 4; break;
		case 'K': lb[0] = 0x9; lb[1] = 0x5; lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x9;  cw = 5; break;
		case 'L': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x7;  cw = 4; break;
		case 'M': lb[0] = 0x11; lb[1] = 0x1B; lb[2] = 0x15; lb[3] = 0x11; lb[4] = 0x11;  cw = 6; break;
		case 'N': lb[0] = 0x9; lb[1] = 0xB; lb[2] = 0xD; lb[3] = 0x9; lb[4] = 0x9;  cw = 5; break;
		case 'O': lb[0] = 0x6; lb[1] = 0x9; lb[2] = 0x9; lb[3] = 0x9; lb[4] = 0x6;  cw = 5; break;
		case 'P': lb[0] = 0x7; lb[1] = 0x9; lb[2] = 0x7; lb[3] = 0x1; lb[4] = 0x1;  cw = 5; break;
		case 'Q': lb[0] = 0x6; lb[1] = 0x9; lb[2] = 0x9; lb[3] = 0x5; lb[4] = 0xA;  cw = 5; break;
		case 'R': lb[0] = 0x7; lb[1] = 0x9; lb[2] = 0x7; lb[3] = 0x9; lb[4] = 0x9;  cw = 5; break;
		case 'S': lb[0] = 0xE; lb[1] = 0x1; lb[2] = 0x6; lb[3] = 0x8; lb[4] = 0x7;  cw = 5; break;
		case 'T': lb[0] = 0x7; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2;  cw = 4; break;
		case 'U': lb[0] = 0x9; lb[1] = 0x9; lb[2] = 0x9; lb[3] = 0x9; lb[4] = 0x6;  cw = 5; break;
		case 'V': lb[0] = 0x5; lb[1] = 0x5; lb[2] = 0x5; lb[3] = 0x2; lb[4] = 0x2;  cw = 4; break;
		case 'W': lb[0] = 0x11; lb[1] = 0x15; lb[2] = 0x15; lb[3] = 0xA; lb[4] = 0xA;  cw = 6; break;
		case 'X': lb[0] = 0x5; lb[1] = 0x5; lb[2] = 0x2; lb[3] = 0x5; lb[4] = 0x5;  cw = 4; break;
		case 'Y': lb[0] = 0x5; lb[1] = 0x5; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2;  cw = 4; break;
		case 'Z': lb[0] = 0x7; lb[1] = 0x4; lb[2] = 0x2; lb[3] = 0x1; lb[4] = 0x7;  cw = 4; break;
		case 'a': lb[2] = 0x6; lb[3] = 0x5; lb[4] = 0x6;  cw = 4; break;
		case 'b': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x3;  cw = 4; break;
		case 'c': lb[2] = 0x6; lb[3] = 0x1; lb[4] = 0x6;  cw = 4; break;
		case 'd': lb[0] = 0x4; lb[1] = 0x4; lb[2] = 0x6; lb[3] = 0x5; lb[4] = 0x6;  cw = 4; break;
		case 'e': lb[2] = 0x2; lb[3] = 0x5; lb[4] = 0x3;  cw = 4; break;
		case 'f': lb[0] = 0x2; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x1;  cw = 3; break;
		case 'g': lb[2] = 0x6; lb[3] = 0x5; lb[4] = 0x6; lb[5] = 0x4;  cw = 4; break;
		case 'h': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x5;  cw = 4; break;
		case 'i': lb[0] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1;  cw = 2; break;
		case 'j': lb[0] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1;  cw = 2; break;
		case 'k': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x5; lb[3] = 0x3; lb[4] = 0x5;  cw = 4; break;
		case 'l': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1;  cw = 2; break;
		case 'm': lb[2] = 0xF; lb[3] = 0x15; lb[4] = 0x15;  cw = 6; break;
		case 'n': lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x5;  cw = 4; break;
		case 'o': lb[2] = 0x7; lb[3] = 0x5; lb[4] = 0x7;  cw = 4; break;
		case 'p': lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x3; lb[5] = 0x1;  cw = 4; break;
		case 'q': lb[2] = 0x6; lb[3] = 0x5; lb[4] = 0x6; lb[5] = 0x4;  cw = 4; break;
		case 'r': lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x1;  cw = 3; break;
		case 's': lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x1;  cw = 3; break;
		case 't': lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x2;  cw = 3; break;
		case 'u': lb[2] = 0x5; lb[3] = 0x5; lb[4] = 0x6;  cw = 4; break;
		case 'v': lb[2] = 0x5; lb[3] = 0x5; lb[4] = 0x2;  cw = 4; break;
		case 'w': lb[2] = 0x9; lb[3] = 0x9; lb[4] = 0xF;  cw = 5; break;
		case 'x': lb[2] = 0x5; lb[3] = 0x2; lb[4] = 0x5;  cw = 4; break;
		case 'y': lb[2] = 0x5; lb[3] = 0x2; lb[4] = 0x2; lb[5] = 0x1;  cw = 4; break;
		case 'z': lb[2] = 0x7; lb[3] = 0x2; lb[4] = 0x7;  cw = 4; break;
		case ' ':  cw = 2; break;
		case '0': lb[0] = 0x2; lb[1] = 0x5; lb[2] = 0x5; lb[3] = 0x5; lb[4] = 0x2;  cw = 4; break;
		case '1': lb[0] = 0x2; lb[1] = 0x3; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2;  cw = 3; break;
		case '2': lb[0] = 0x3; lb[1] = 0x4; lb[2] = 0x2; lb[3] = 0x1; lb[4] = 0x7;  cw = 4; break;
		case '3': lb[0] = 0x3; lb[1] = 0x4; lb[2] = 0x2; lb[3] = 0x4; lb[4] = 0x3;  cw = 4; break;
		case '4': lb[0] = 0x4; lb[1] = 0x6; lb[2] = 0x5; lb[3] = 0x7; lb[4] = 0x4;  cw = 4; break;
		case '5': lb[0] = 0x7; lb[1] = 0x1; lb[2] = 0x7; lb[3] = 0x4; lb[4] = 0x3;  cw = 4; break;
		case '6': lb[0] = 0x2; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x5; lb[4] = 0x2;  cw = 4; break;
		case '7': lb[0] = 0x7; lb[1] = 0x4; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2;  cw = 4; break;
		case '8': lb[0] = 0x2; lb[1] = 0x5; lb[2] = 0x2; lb[3] = 0x5; lb[4] = 0x2;  cw = 4; break;
		case '9': lb[0] = 0x2; lb[1] = 0x5; lb[2] = 0x7; lb[3] = 0x4; lb[4] = 0x2;  cw = 4; break;
		case '-': lb[2] = 0x3;  cw = 3; break;
		case '+': lb[1] = 0x2; lb[2] = 0x7; lb[3] = 0x2;  cw = 4; break;
		case '_': lb[5] = 0x7;  cw = 4; break;
		case '=': lb[3] = 0x3;  cw = 3; break;
		case '!': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[4] = 0x1;  cw = 2; break;
		case '?': lb[0] = 0x1; lb[1] = 0x2; lb[2] = 0x1; lb[4] = 0x1;  cw = 3; break;
		case '/': lb[0] = 0x2; lb[1] = 0x2; lb[2] = 0x3; lb[3] = 0x1; lb[4] = 0x1;  cw = 3; break;
		case '\\': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x3; lb[3] = 0x2; lb[4] = 0x2;  cw = 3; break;
		case '|': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1;  cw = 2; break;
		case '<': lb[2] = 0x2; lb[3] = 0x1; lb[4] = 0x2;  cw = 3; break;
		case '>': lb[2] = 0x1; lb[3] = 0x2; lb[4] = 0x1;  cw = 3; break;
		case '[': lb[0] = 0x3; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x3;  cw = 3; break;
		case ']': lb[0] = 0x3; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2; lb[5] = 0x3;  cw = 3; break;
		case '(': lb[0] = 0x2; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x2;  cw = 3; break;
		case ')': lb[0] = 0x1; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2; lb[5] = 0x1;  cw = 3; break;


		default:
			lb[0] = 0xF; lb[1] = 0xF; lb[2] = 0xF; lb[3] = 0xF; lb[4] = 0xF; lb[5] = 0xF; cw = 4; break;
			break;
	}
	
	if(xOffset < -3 && xOffset > 9) return cw;
	
	for(y = 0; y < 6; y++){
		for(x = 0; x < cw; x++){
			if(lb[y] & (1<<x)){
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

