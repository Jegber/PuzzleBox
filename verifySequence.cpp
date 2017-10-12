#include "verifySequence.h"

#define CORRECT   1
#define INCORRECT 0
#define START_OF_SEQUENCE 0


static int currentIndex = START_OF_SEQUENCE; // The current index in the sequence array
static bool correctSequence = INCORRECT;     // A flag indicating whether the correct sequence has been input by the user


int verifySequence_getInput(){ return cubeOrientation_getCurrentTop(); }

bool verifySequence_processInput(){ return cubeOrientation_topChanged(); }


enum verifySequence_smt_t{
	init_st,        // Initialize the SM
	check_input_st, // continuously checks the user's input, and advances through the array if correct inputs are given
	final_st        // Return that the user inputted the correct sequence
} vs_currentState = init_st;


// Ticks the vs SM
void verifySequence_tick(){
	// Perform state actions first
	switch(vs_currentState){
		case init_st:
			currentIndex = START_OF_SEQUENCE;
			correctSequence = INCORRECT;
			break;
		case check_input_st:
			break;
		case final_st:
			correctSequence = CORRECT;
      Serial.print("CORRECT!\n");
			break;
		default:
			break;
	}

	// Perform state updates second
	switch(vs_currentState){
		case init_st:
			vs_currentState = check_input_st;
			break;
		case check_input_st:
			// If it's time to process the input
			if (verifySequence_processInput()){
				// If the input is incorrect
				if (verifySequence_getInput() != verifySequence_sequenceArray[currentIndex]){
					currentIndex = START_OF_SEQUENCE; // Restart the iteration
					vs_currentState = check_input_st; // Stay in the check input state
				}
				// If the input is correct
				else if(verifySequence_getInput() == verifySequence_sequenceArray[currentIndex]){
					currentIndex++; // Increment the current Index
					vs_currentState = check_input_st; // Stay in the check input state
				}
			}
			else if (verifySequence_sequenceArray[currentIndex] == VERIFYSEQUENCE_SEQUENCE_END){
				vs_currentState = final_st;
			}
			break;
		case final_st:
			vs_currentState = init_st;
			break;
		default:
			break;
	}
}


// If correct sequence is inputted returns 1, else returns 0
bool verifySequence_verified(){
	return correctSequence;
}


