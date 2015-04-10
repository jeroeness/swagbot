#include "../globalincsanddefs.h"
#include "ledgrid.h"

uint8_t currentFace = 0;     //use this as extern to select an face. max value: 5. -1 for displayOff
uint8_t currentSubFace = 0;  //use this as extern to select the subinterface of the face (for animation purposes). max value: 99 or the textlength

uint8_t previousFace = 255;
uint8_t previousSubFace = 255;
uint8_t currentPrintLine = 0;
uint8_t currentPrintColor = 0;

uint8_t refreshColors[3] = {0,0,0};
uint8_t refreshColorNum = 0;

uint8_t scrolledAllTest = 0;

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

char dispText[5];
uint8_t *dispColor[5];

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


void setEmotion(uint8_t em){
	currentFace = em;
	updateEmotion();
}

void setSubEmotion(uint8_t subem){
	currentSubFace = subem;
	updateEmotion();
}

void setNextSubEmotion(void){
	currentSubFace++;
	updateEmotion();
}


void displayText(const char *text) {
	uint8_t * currentColor = rd;
	int8_t i, sc = 0;

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
		} else {
			if(sc == 4) break;
			dispText[sc] = text[i];
			dispColor[sc] = currentColor;
			sc++;
		}
	}

	tmpStringLength = sc;
	dispText[sc] = '\0';
	
	/*
	int8_t offset = 0;
	for(i = 0; i < tmpStringLength; i++){
		offset += printCharacter(dispColor[i], dispText[i] + '0', offset, 0);
	}*/

	currentFace = 253; //scrolling text
	currentSubFace = (currentSubFace == 0 ? 1 : 0); //what xOffset are we at?

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

	scrolledAllTest = 0;

	currentFace = 254; //scrolling text
	currentSubFace = 0; //what xOffset are we at?

	//updateLedGrid();
}

uint8_t checkTextScrolled(void){
	return scrolledAllTest;
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
		case 0://just clear the display
			clearDisplayData();
			break;

		case 1: //green SMILEY!!! <:)
			clearDisplayData();
			gd[0] = 0x66; gd[1] = 0x81; gd[2] = 0x24;
			gd[3] = 0x24; gd[5] = 0x81; gd[6] = 0x42;
			gd[7] = 0x3C;
			break;

		case 2: //angry red face >:(
			clearDisplayData();
			rd[1] = 0x24; rd[2] = 0x24; rd[5] = 0x3C;
			rd[6] = 0x42; rd[7] = 0x81;
			break;

		case 3: //compass
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

		case 4: //bumper (not pressed) Right
			clearDisplayData();
			rd[0] = 0xC0; rd[1] = 0x30; rd[2] = 0xC;
			rd[3] = 0x2; rd[4] = 0xFF; rd[5] = 0x81;
			rd[6] = 0x81; rd[7] = 0xFF;
			break;

		case 5: //bumper (pressed) Right
			clearDisplayData();
			gd[2] = 0xFC; gd[3] = 0x2; gd[4] = 0xFF;
			gd[5] = 0x81; gd[6] = 0x81; gd[7] = 0xFF;
			break;

		case 6: //display numbers
			clearDisplayData();
			num1 = currentSubFace / 10;
			num2 = currentSubFace % 10;
			printCharacter(rd, num1 + '0', 0, 2);
			printCharacter(gd, num2 + '0', 4, 2);
			break;
			
		case 7: // IT'S A ME, MARIO!
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

		case 8: // Space invaders (animated) alien 1
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
			break;
			
		case 253: //scrollable text
			clearDisplayData();
			
			for(i = 0; i < 4; i++){
				num1 = i / 2;
				num2 = i % 2;
				printCharacter(dispColor[i], dispText[i], num2 * 4, num1 * 4);
			}

			break;
			
		case 254: //scrollable text
			clearDisplayData();
			for(i = 0; i < scrollLength; i++){
				offsetCount += printCharacter(scrollColor[i], scrollText[i], offsetCount - currentSubFace + 8, 0);
			}
			if(currentSubFace >= offsetCount+8){
				scrolledAllTest++;
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
	uint8_t lb[8] = {0,0,0,0,0,0,0,0};
	int8_t cw = 0; //CharWidth

	switch(character){
		case 'M': lb[0] = 0x63; lb[1] = 0x63; lb[2] = 0x55; lb[3] = 0x55; lb[4] = 0x49; lb[5] = 0x49; lb[6] = 0x41;  cw = 8; break;
		case 'W': lb[0] = 0x81; lb[1] = 0x81; lb[2] = 0x81; lb[3] = 0x42; lb[4] = 0x5A; lb[5] = 0x5A; lb[6] = 0x24;  cw = 9; break;
		case 'm': lb[4] = 0x3F; lb[5] = 0x49; lb[6] = 0x49; lb[7] = 0x49;  cw = 8; break;
		case 'w': lb[4] = 0x11; lb[5] = 0x15; lb[6] = 0x15; lb[7] = 0xE;  cw = 7; break;

		case 'A': lb[0] = 0xC; lb[1] = 0xC; lb[2] = 0x12; lb[3] = 0x12; lb[4] = 0x12; lb[5] = 0x3F; lb[6] = 0x21; lb[7] = 0x21;  cw = 7; break;
		case 'B': lb[0] = 0x1F; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x1F; lb[4] = 0x21; lb[5] = 0x21; lb[6] = 0x21; lb[7] = 0x1F;  cw = 7; break;
		case 'C': lb[0] = 0x1E; lb[1] = 0x21; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x21; lb[7] = 0x1E;  cw = 7; break;
		case 'D': lb[0] = 0x1F; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x21; lb[4] = 0x21; lb[5] = 0x21; lb[6] = 0x21; lb[7] = 0x1F;  cw = 7; break;
		case 'E': lb[0] = 0x1F; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0xF; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1F;  cw = 6; break;
		case 'F': lb[0] = 0x1F; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0xF; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 6; break;
		case 'G': lb[0] = 0x3E; lb[1] = 0x41; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x71; lb[5] = 0x41; lb[6] = 0x41; lb[7] = 0x3E;  cw = 8; break;
		case 'H': lb[0] = 0x21; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x3F; lb[4] = 0x21; lb[5] = 0x21; lb[6] = 0x21; lb[7] = 0x21;  cw = 7; break;
		case 'I': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 2; break;
		case 'J': lb[0] = 0x8; lb[1] = 0x8; lb[2] = 0x8; lb[3] = 0x8; lb[4] = 0x8; lb[5] = 0x9; lb[6] = 0x9; lb[7] = 0x6;  cw = 5; break;
		case 'K': lb[0] = 0x21; lb[1] = 0x11; lb[2] = 0x9; lb[3] = 0x7; lb[4] = 0x7; lb[5] = 0x9; lb[6] = 0x11; lb[7] = 0x21;  cw = 7; break;
		case 'L': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1F;  cw = 6; break;
		case 'N': lb[0] = 0x23; lb[1] = 0x23; lb[2] = 0x25; lb[3] = 0x25; lb[4] = 0x29; lb[5] = 0x29; lb[6] = 0x31; lb[7] = 0x31;  cw = 7; break;
		case 'O': lb[0] = 0x3E; lb[1] = 0x41; lb[2] = 0x41; lb[3] = 0x41; lb[4] = 0x41; lb[5] = 0x41; lb[6] = 0x41; lb[7] = 0x3E;  cw = 8; break;
		case 'P': lb[0] = 0x1F; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x21; lb[4] = 0x1F; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 7; break;
		case 'Q': lb[0] = 0x3E; lb[1] = 0x41; lb[2] = 0x41; lb[3] = 0x41; lb[4] = 0x41; lb[5] = 0x51; lb[6] = 0x61; lb[7] = 0x3E;  cw = 8; break;
		case 'R': lb[0] = 0x1F; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x21; lb[4] = 0x1F; lb[5] = 0x21; lb[6] = 0x21; lb[7] = 0x21;  cw = 7; break;
		case 'S': lb[0] = 0x1E; lb[1] = 0x21; lb[2] = 0x1; lb[3] = 0x1E; lb[4] = 0x20; lb[5] = 0x20; lb[6] = 0x21; lb[7] = 0x1E;  cw = 7; break;
		case 'T': lb[0] = 0x1F; lb[1] = 0x4; lb[2] = 0x4; lb[3] = 0x4; lb[4] = 0x4; lb[5] = 0x4; lb[6] = 0x4; lb[7] = 0x4;  cw = 6; break;
		case 'U': lb[0] = 0x21; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x21; lb[4] = 0x21; lb[5] = 0x21; lb[6] = 0x21; lb[7] = 0x1E;  cw = 7; break;
		case 'V': lb[0] = 0x21; lb[1] = 0x21; lb[2] = 0x21; lb[3] = 0x12; lb[4] = 0x12; lb[5] = 0x12; lb[6] = 0xC; lb[7] = 0xC;  cw = 7; break;
		case 'X': lb[0] = 0x21; lb[1] = 0x21; lb[2] = 0x12; lb[3] = 0xC; lb[4] = 0xC; lb[5] = 0x12; lb[6] = 0x21; lb[7] = 0x21;  cw = 7; break;
		case 'Y': lb[0] = 0x20; lb[1] = 0x20; lb[2] = 0x11; lb[3] = 0xA; lb[4] = 0x4; lb[5] = 0x4; lb[6] = 0x4; lb[7] = 0x4;  cw = 7; break;
		case 'Z': lb[0] = 0x1F; lb[1] = 0x10; lb[2] = 0x8; lb[3] = 0x4; lb[4] = 0x2; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1F;  cw = 6; break;
		case 'a': lb[3] = 0xE; lb[4] = 0x10; lb[5] = 0x1E; lb[6] = 0x11; lb[7] = 0x1E;  cw = 6; break;
		case 'b': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0xF; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xF;  cw = 6; break;
		case 'c': lb[3] = 0xE; lb[4] = 0x11; lb[5] = 0x1; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case 'd': lb[0] = 0x10; lb[1] = 0x10; lb[2] = 0x10; lb[3] = 0x1E; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0x1E;  cw = 6; break;
		case 'e': lb[3] = 0xE; lb[4] = 0x11; lb[5] = 0x1F; lb[6] = 0x1; lb[7] = 0xE;  cw = 6; break;
		case 'f': lb[0] = 0x2; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x3; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case 'g': lb[3] = 0x1E; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0x1E;  cw = 6; break;
		case 'h': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0xD; lb[4] = 0x13; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0x11;  cw = 6; break;
		case 'i': lb[1] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 2; break;
		case 'j': lb[1] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 2; break;
		case 'k': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x9; lb[4] = 0x5; lb[5] = 0x3; lb[6] = 0x5; lb[7] = 0x9;  cw = 5; break;
		case 'l': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 2; break;
		case 'n': lb[3] = 0xF; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0x11;  cw = 6; break;
		case 'o': lb[3] = 0xE; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case 'p': lb[3] = 0xF; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xF;  cw = 6; break;
		case 'q': lb[3] = 0x1E; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0x1E;  cw = 6; break;
		case 'r': lb[3] = 0x3; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case 's': lb[3] = 0xE; lb[4] = 0x1; lb[5] = 0x6; lb[6] = 0x8; lb[7] = 0x7;  cw = 5; break;
		case 't': lb[2] = 0x1; lb[3] = 0x3; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x2;  cw = 3; break;
		case 'u': lb[3] = 0x11; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x19; lb[7] = 0x16;  cw = 6; break;
		case 'v': lb[3] = 0x9; lb[4] = 0x9; lb[5] = 0x9; lb[6] = 0x6; lb[7] = 0x6;  cw = 5; break;
		case 'x': lb[3] = 0x9; lb[4] = 0x9; lb[5] = 0x6; lb[6] = 0x9; lb[7] = 0x9;  cw = 5; break;
		case 'y': lb[3] = 0x9; lb[4] = 0x9; lb[5] = 0x9; lb[6] = 0xA; lb[7] = 0x4;  cw = 5; break;
		case 'z': lb[3] = 0xF; lb[4] = 0x4; lb[5] = 0x2; lb[6] = 0x1; lb[7] = 0xF;  cw = 5; break;
		case ' ':  cw = 2; break;
		
		/*
		case '0': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x11; lb[3] = 0x11; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case '1': lb[0] = 0x4; lb[1] = 0x7; lb[2] = 0x4; lb[3] = 0x4; lb[4] = 0x4; lb[5] = 0x4; lb[6] = 0x4; lb[7] = 0x4;  cw = 4; break;
		case '2': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x10; lb[3] = 0x8; lb[4] = 0x4; lb[5] = 0x2; lb[6] = 0x1; lb[7] = 0x1F;  cw = 6; break;
		case '3': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x10; lb[3] = 0xC; lb[4] = 0x10; lb[5] = 0x10; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case '4': lb[0] = 0x8; lb[1] = 0xC; lb[2] = 0xA; lb[3] = 0x9; lb[4] = 0x9; lb[5] = 0x1F; lb[6] = 0x8; lb[7] = 0x8;  cw = 6; break;
		case '5': lb[0] = 0x1F; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0xF; lb[4] = 0x10; lb[5] = 0x10; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case '6': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x1; lb[3] = 0xF; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case '7': lb[0] = 0x1F; lb[1] = 0x10; lb[2] = 0x8; lb[3] = 0x8; lb[4] = 0x4; lb[5] = 0x4; lb[6] = 0x4; lb[7] = 0x4;  cw = 6; break;
		case '8': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x11; lb[3] = 0xE; lb[4] = 0x11; lb[5] = 0x11; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		case '9': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x11; lb[3] = 0x1E; lb[4] = 0x10; lb[5] = 0x10; lb[6] = 0x11; lb[7] = 0xE;  cw = 6; break;
		*/
		
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

		case '-': lb[4] = 0xF;  cw = 5; break;
		case '+': lb[2] = 0x4; lb[3] = 0x4; lb[4] = 0x1F; lb[5] = 0x4; lb[6] = 0x4;  cw = 6; break;
		case '_':  cw = 6; break;
		case '=': lb[3] = 0xF; lb[5] = 0xF;  cw = 6; break;
		case '!': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[6] = 0x1;  cw = 3; break;
		case '?': lb[0] = 0xE; lb[1] = 0x11; lb[2] = 0x10; lb[3] = 0x8; lb[4] = 0x4; lb[5] = 0x4; lb[7] = 0x4;  cw = 6; break;
		case '/': lb[0] = 0x2; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case '\\': lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x3; lb[5] = 0x2; lb[6] = 0x2; lb[7] = 0x2;  cw = 3; break;
		case '|': lb[0] = 0x1; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case '<': lb[1] = 0x8; lb[2] = 0x4; lb[3] = 0x2; lb[4] = 0x1; lb[5] = 0x2; lb[6] = 0x4; lb[7] = 0x8;  cw = 6; break;
		case '>': lb[1] = 0x1; lb[2] = 0x2; lb[3] = 0x4; lb[4] = 0x8; lb[5] = 0x4; lb[6] = 0x2; lb[7] = 0x1;  cw = 6; break;
		case '[': lb[0] = 0x3; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case ']': lb[0] = 0x3; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2; lb[5] = 0x2; lb[6] = 0x2; lb[7] = 0x2;  cw = 3; break;
		case '(': lb[0] = 0x2; lb[1] = 0x1; lb[2] = 0x1; lb[3] = 0x1; lb[4] = 0x1; lb[5] = 0x1; lb[6] = 0x1; lb[7] = 0x1;  cw = 3; break;
		case ')': lb[0] = 0x1; lb[1] = 0x2; lb[2] = 0x2; lb[3] = 0x2; lb[4] = 0x2; lb[5] = 0x2; lb[6] = 0x2; lb[7] = 0x2;  cw = 3; break;

		default:
			lb[0] = 0xF; lb[1] = 0xF; lb[2] = 0xF; lb[3] = 0xF; lb[4] = 0xF; lb[5] = 0xF; lb[6] = 0xF; cw = 4; break;
			break;
	}

	if(xOffset < -3 && xOffset > 9) return cw;

	for(y = 0; y < 8; y++){
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

