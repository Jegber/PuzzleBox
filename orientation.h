#ifndef orientation_h
#define orientation_h

////////////////////////////////////////////////////////////////////////////
// orientation uses an accelerometer to determine an object's orientation
// Justin Egbert, accelerometer read code adapted from Bildr
// June 2016
////////////////////////////////////////////////////////////////////////////
#include "Arduino.h"


// Analog read pins
#define X_PIN 0
#define Y_PIN 1
#define Z_PIN 2

// The minimum and maximum values that came from
// the accelerometer while standing still
// You very well may need to change these
#define MINVAL 275
#define MAXVAL 315

// How many degrees of wiggle room for determining sideup?
#define WIGGLE 20

// What are the coords for each side of a cube?
#define TOPX  14  // Top side's coordinates (when the top is facing up)
#define TOPY  19
#define TOPZ  36
#define BOTX  127 // Bottom side's coordinates (when the bottom is facing up)
#define BOTY  126
#define BOTZ  45
#define FROX  40  // Front side's coordinates (when the front is facing up)
#define FROY  70
#define FROZ  20
#define BACX  40  // Back side's coordinates (when the back is facing up)
#define BACY  322
#define BACZ  129
#define LEFX  320 // Left side's coordinates (when the left side is facing up)
#define LEFY  38
#define LEFZ  315
#define RIGX  68  // Right side's coordinates (when the right side is facing up)
#define RIGY  42
#define RIGZ  70

// The sides of a cube
#define CUBE_TOP    0
#define CUBE_BOTTOM 1 
#define CUBE_LEFT   2
#define CUBE_RIGHT  3
#define CUBE_FRONT  4
#define CUBE_BACK   5
#define CUBE_EDGE   6

// The letters on the sides of the cube
#define CUBE_T CUBE_RIGHT
#define CUBE_H CUBE_TOP
#define CUBE_I CUBE_BACK
#define CUBE_N CUBE_BOTTOM
#define CUBE_K CUBE_FRONT
#define CUBE_E CUBE_LEFT


// Returns the value for whichever side of a cube is facing up, 
// should the accelerometer be mounted in a cube
int orientation_getCubeTop();

#endif
