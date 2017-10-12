#ifndef servoControl_h
#define servoControl_h
////////////////////////////////////////////////////////////////////////////
// operates a servo motor for a time if an external flag is set to true
// Justin Egbert
// July 2016
////////////////////////////////////////////////////////////////////////////
#include "Arduino.h"
#include "verifySequence.h"
#include <Servo.h>

#define SERVO_PIN 9
#define BUTTON_INPUT_PIN 2
#define BUTTON_RESET_TIMER 100

// Ticks the SM
void servoControl_tick();

// Decide if the servo should open or not
bool servoControl_shouldOpen();

// Decide if the servo should close or not
bool servoControl_buttonPressed();

#endif
