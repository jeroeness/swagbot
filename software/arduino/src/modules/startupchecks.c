//startupchecks

#include "../globalincsanddefs.h"

extern union USD sensorData;

void checkSensors(){
  bool checksdone = 0;
  while(!checksdone){
    i2c_read_sensors(sizeof(sensorData.instructionstruct));
    //check bumper L
    if(sensorData.sensorStruct.bumperLeft){
      
    }
    
    //check bumper R
    if(sensorData.sensorStruct.bumperLeft){
      
    }
    
    //check sonar
    //if(sensorData.sensorStruct.ultrasonic >= something){
    
    //}
    
    //check compas????
    
    
  }
  //_delay_ms()
  
}
