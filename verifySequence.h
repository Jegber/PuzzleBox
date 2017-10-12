#ifndef verifySequence_h
#define verifySequence_h

////////////////////////////////////////////////////////////////
// verifySequence checks a stream of inputs against a pre-defined combination.
// Justin Egbert, June 2016
////////////////////////////////////////////////////////////////
#include "cubeOrientation.h"
#include "orientation.h"

#define VERIFYSEQUENCE_SEQUENCESIZE 10 // The size of the desired sequence
#define VERIFYSEQUENCE_SEQUENCE_END -1 // The character used to terminate a sequence


// The sequence to be solved. It is terminated with a termination integer
int const verifySequence_sequenceArray[VERIFYSEQUENCE_SEQUENCESIZE] = { 
																CUBE_T,
										 						CUBE_H,
										 						CUBE_I,
										 						CUBE_N,
										 						CUBE_K,
										 						VERIFYSEQUENCE_SEQUENCE_END
																};


// Ticks the vs SM
void verifySequence_tick();

// If the correct sequence has been inputted returns true, else returns false 
bool verifySequence_verified();

// This function is what retrieves the stream of input data for the SM
int verifySequence_getInput(); // In this case, returns whichever side is on currently top

// This function tells the SM that it's time to process the given input
bool verifySequence_processInput(); // In this case, the user has turned the cube so a new side is on top

#endif
