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

int16_t sinn(int16_t a);
int16_t coss(int16_t a);
int16_t tann(int16_t a);
int16_t atann(int16_t a);

extern volatile uint8_t routeFindingDepth;				
extern volatile uint8_t findingAngleToPoint;
extern volatile int16_t totalDeviation;
extern volatile int16_t desiredProgression;


#endif
