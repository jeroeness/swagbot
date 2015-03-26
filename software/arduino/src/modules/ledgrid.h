#ifndef LEDGRIDHEADER
#define LEDGRIDHEADER

#include "../globalincsanddefs.h"

//#define OUTPUT_ENABLE (1<<PG1) //not used anymore
#define STROBE (1<<PB0) //pin53
#define CLOCK (1<<PG0) //pin41
#define DATA (1<<PB3) //pin 50

//#define PORT_OUTPUT_ENABLE PORTG //not used anymore
#define PORT_STROBE PORTB
#define PORT_CLOCK PORTG
#define PORT_DATA PORTB

#define DDR_STROBE DDRB
#define DDR_CLOCK DDRG
#define DDR_DATA DDRB


uint8_t updateLedGrid();
uint8_t pushArraysToGrid(uint8_t);
void setEmotion(uint8_t);
void initLedGrid();
void clearDisplayData();

#endif