#ifndef ROUTE_FINDING_FUNCTIONS
#define ROUTE_FINDING_FUNCTIONS
//DEFINES:

#define MIN_DISTANCE 		50
#define OUTSIDE_MARGIN_RP6	10


void checkObstacle();
void findRoute(int16_t angleToPoint, int16_t turnedAngle, uint16_t distance);
void findAngleToPoint();
void endRouteFinding();
int16_t convertToTime(int16_t ultrasonic);


volatile int16_t totalDeviation;
volatile int16_t desiredProgression;
volatile uint8_t routeFindingDepth;				
volatile uint8_t findingAngleToPoint;

#endif
