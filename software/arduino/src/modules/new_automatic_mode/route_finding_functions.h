#ifndef ROUTE_FINDING_FUNCTIONS
#define ROUTE_FINDING_FUNCTIONS
//DEFINES:

#define MIN_DISTANCE 		50
#define OUTSIDE_MARGIN_RP6	10


void checkObstacle();
void findRoute(int16_t angleToPoint, int16_t turnedAngle, uint16_t distance);
void findAngleToPoint();

void finishRouteFinding();
void endRouteFinding();

int16_t convertToTime(int16_t ultrasonic);

double sind(float a);
double cosd(float a);
double tand(float a);
double atand(float a);

extern volatile uint8_t routeFindingDepth;				
extern volatile uint8_t findingAngleToPoint;
extern volatile float totalDeviation;
extern volatile float desiredProgression;


#endif
