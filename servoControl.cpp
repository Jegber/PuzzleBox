#include "servoControl.h"

#define OPEN_TIME  100 // in ms
#define TIMER_INIT 0
#define OPEN_DEGREES 95
#define CLOSED_DEGREES 11

int openTimer;

Servo myServo;

enum servoControl_smt_t{
  init_st,        // Initialize the SM
  closed_st,      // continuously checks if the servo should open or not
  open_st         // opens the servo until the closed button is pressed
} sc_currentState = init_st;


// Ticks the vs SM
void servoControl_tick(){
  // Perform state actions first
  switch(sc_currentState){
    case init_st:
      myServo.attach(SERVO_PIN); // Init servo
      myServo.write(CLOSED_DEGREES); // Init servo
      pinMode(BUTTON_INPUT_PIN, INPUT_PULLUP); // Init button pin
      openTimer = TIMER_INIT;
      break;
    case closed_st:
      break;
    case open_st:
      openTimer++;
      break;
    default:
      break;
  }

  // Perform state updates second
  switch(sc_currentState){
    case init_st:
      sc_currentState = closed_st;
      break;
    case closed_st:
      if (servoControl_shouldOpen()){
        sc_currentState = open_st;
        myServo.write(OPEN_DEGREES);
      }
      break;
    case open_st:
      if (servoControl_buttonPressed()){
        sc_currentState = closed_st;
        myServo.write(CLOSED_DEGREES);
        openTimer = TIMER_INIT;
      }
      break;
    default:
      break;
  }
}


// Decide if the servo should open
bool servoControl_shouldOpen(){
  if (servoControl_buttonPressed()) return true; // the box should open if the button is pressed (as a force open)
  return verifySequence_verified(); // returns if the correct combo has been entered by the user
}

// Decide if the button is pressed
bool servoControl_buttonPressed() {
  static int timer; // Uses a static variable to make it so you can't press the button multiple times in quick succession
  boolean pressed = !digitalRead(BUTTON_INPUT_PIN);
  if (pressed && timer < 0) {
    timer = BUTTON_RESET_TIMER;
    return true;
  }
  timer--;
  return false;
}

