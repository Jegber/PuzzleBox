#ifndef cubeOrientation_h
#define cubeOrientation_h

/////////////////////////////////////////
// cubeOrientation is a state machine that determines for certain whether a user has turned a cube to a specific side.
// If the user turns the cube to a side, the state machine sets a global variable, and reports that the side has changed.
// Justin Egbert, June 2016
//////////////////////////////////////////
#include "orientation.h"

#define CUBEORIENTATION_SURETY 5  // The number of readings in a row needed to verify that the user has indeed changed the cube's face up
#define CUBEORIENTATION_BEEP_PIN 11
#define CUBEORIENTATION_BEEP_DURATION 100 // The number of ticks the duration should beep a piezoelectric buzzer
#define CUBEORIENTATION_LOWEST_FREQ 31
#define CUBEORIENTATION_MAX_FREQ 1500



void cubeOrientation_tick(); // Ticks the SM

bool cubeOrientation_topChanged(); // Returns true if the top side has changed, false if otherwise

int cubeOrientation_getCurrentTop(); // Returns the top side as determined by the state machine

void cubeOrientation_beep(); // Beeps a piezoelectric buzzer for a short time at a random frequency

#endif
