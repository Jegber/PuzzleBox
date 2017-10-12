#include "orientation.h"

//determines whether a number is within a degree range on a circle
bool withinRange(double minVal, double givenVal, double maxVal){
  double correction = minVal;
  minVal = 0;
  givenVal = givenVal - correction;
  if (givenVal < 0) givenVal = 360 + givenVal;
  maxVal = maxVal - correction;
  if (maxVal < 0) maxVal = 360 + maxVal;
  if ((givenVal < maxVal) && (givenVal > minVal)) return true;
  else return false;
}

int cubeTopSide(double x, double y, double z){
  
  if( withinRange(TOPX - WIGGLE, x, TOPX + WIGGLE) &&              
      withinRange(TOPY - WIGGLE, y, TOPY + WIGGLE) &&
      withinRange(TOPZ - WIGGLE, z, TOPZ + WIGGLE)   ) return CUBE_TOP;
  
  else if( withinRange(BOTX - WIGGLE, x, BOTX + WIGGLE) &&              
           withinRange(BOTY - WIGGLE, y, BOTY + WIGGLE) &&
           withinRange(BOTZ - WIGGLE, z, BOTZ + WIGGLE)   ) return CUBE_BOTTOM;
      
  else if( withinRange(FROX - WIGGLE, x, FROX + WIGGLE) &&              
           withinRange(FROY - WIGGLE, y, FROY + WIGGLE) &&
           withinRange(FROZ - WIGGLE, z, FROZ + WIGGLE)   ) return CUBE_FRONT;

  else if( withinRange(BACX - WIGGLE, x, BACX + WIGGLE) &&              
           withinRange(BACY - WIGGLE, y, BACY + WIGGLE) &&
           withinRange(BACZ - WIGGLE, z, BACZ + WIGGLE)   ) return CUBE_BACK; 

  else if( withinRange(LEFX - WIGGLE, x, LEFX + WIGGLE) &&
           withinRange(LEFY - WIGGLE, y, LEFY + WIGGLE) &&
           withinRange(LEFZ - WIGGLE, z, LEFZ + WIGGLE)   ) return CUBE_LEFT; 
      
  else if( withinRange(RIGX - WIGGLE, x, RIGX + WIGGLE) &&              
           withinRange(RIGY - WIGGLE, y, RIGY + WIGGLE) &&
           withinRange(RIGZ - WIGGLE, z, RIGZ + WIGGLE)   ) return CUBE_RIGHT;
      
  return CUBE_EDGE;
}

int orientation_getCubeTop(){
  //read the analog values from the accelerometer
  int xRead = analogRead(X_PIN);
  int yRead = analogRead(Y_PIN);
  int zRead = analogRead(Z_PIN);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, MINVAL, MAXVAL, -90, 90);
  int yAng = map(yRead, MINVAL, MAXVAL, -90, 90);
  int zAng = map(zRead, MINVAL, MAXVAL, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  double x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  double y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  double z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  return cubeTopSide(x, y, z);
}
