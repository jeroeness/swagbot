#ifndef LEDGRIDHEADER
#define LEDGRIDHEADER

#include "../globalincsanddefs.h"

//#define OUTPUT_ENABLE (1<<PG1) //not used anymore
#define STROBE (1<<PL0) //pin49
#define CLOCK (1<<PB2) //pin51
#define DATA (1<<PB0) //pin53
#define POSITIVE (1<<PL2) //pin53

//#define PORT_OUTPUT_ENABLE PORTG //not used anymore
#define PORT_STROBE PORTL
#define PORT_CLOCK PORTB
#define PORT_DATA PORTB
#define PORT_POSITIVE PORTL

#define DDR_STROBE DDRL
#define DDR_CLOCK DDRB
#define DDR_DATA DDRB
#define DDR_POSITIVE DDRL

uint8_t updateLedGrid();
uint8_t pushArraysToGrid(uint8_t, uint8_t);
void setEmotion(uint8_t);
void initLedGrid();
void clearDisplayData();

#endif