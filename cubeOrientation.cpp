#include "cubeOrientation.h"

#define NO_CHANGE   0
#define IS_CHANGE   1
#define NO_READINGS 0


static int num_readings; // The number of readings currently acquired before reaching SURETY
static bool changeOfTop; // Whether or not the side has changed
static int currentTop;   // The cube's current side, determined after reaching SURETY
static int tempTop;      // The side that's currently being counted on, pre-SURETY


enum cubeOrientation_st_t {
	init_st,           // The initial state of the state machine
	count_readings_st, // Count readings until you get a SURETY number of them in a row
	final_st           // The final state of the state machine
} co_currentState = init_st;


// Ticks the SM
void cubeOrientation_tick(){
	// Perform state actions first
	switch(co_currentState){
		case init_st:
			num_readings = NO_READINGS;
			changeOfTop = NO_CHANGE;
			tempTop = orientation_getCubeTop();
			break;
		case count_readings_st:
			num_readings++;
			break;
		case final_st:
			changeOfTop = IS_CHANGE;
			currentTop = tempTop;
      cubeOrientation_beep();
      Serial.print(currentTop);
			break;
		default:
			break;
	}

	// Perform state transitions second
	switch(co_currentState){
		case init_st:
			co_currentState = count_readings_st;
			break;
		case count_readings_st:
			if (orientation_getCubeTop() != tempTop){ // If the orientation has changed
				num_readings = NO_READINGS; // reset the counter
				tempTop = orientation_getCubeTop(); // reset the temptop
        co_currentState = count_readings_st;
			}
			else if ( (orientation_getCubeTop() == tempTop) && // if the orientation hasn't changed but there's still counting to do
				        (num_readings < CUBEORIENTATION_SURETY) ){
				tempTop = orientation_getCubeTop(); // reset the temp top and stay in the same state
        co_currentState = count_readings_st;
      }
      else if (  (num_readings >= CUBEORIENTATION_SURETY) && // if the orientation hasn't changed and you've reached SURETY,
            		 (orientation_getCubeTop() == tempTop)   &&
            		 (tempTop == currentTop) ){   //     but the user is still on the same side as last time, start counting again
        num_readings = NO_READINGS;
        tempTop = orientation_getCubeTop();          
        co_currentState = count_readings_st;
      }
      else if (  (num_readings >= CUBEORIENTATION_SURETY) && // if the orientation hasn't changed and you've reached SURETY, and tempTop is different from last time
                 (orientation_getCubeTop() == tempTop)    &&
                 (tempTop != currentTop) &&
                 (tempTop != CUBE_EDGE)){
        currentTop = tempTop;
        co_currentState = final_st; // Proceed to final state
      }
			break;
		case final_st:
			co_currentState = init_st;
			break;
		default:
			break;
	}
}

// Returns true if the side has changed, false if otherwise
bool cubeOrientation_topChanged(){
	return changeOfTop;
}


// Returns the side as determined by the state machine
int cubeOrientation_getCurrentTop(){
	return currentTop;
}

void cubeOrientation_beep() {
  int randomTone = random(CUBEORIENTATION_LOWEST_FREQ, CUBEORIENTATION_MAX_FREQ);
  tone(CUBEORIENTATION_BEEP_PIN, randomTone, CUBEORIENTATION_BEEP_DURATION);
}

