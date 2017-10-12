#include <Servo.h>
#include "orientation.h"
#include "cubeOrientation.h"
#include "verifySequence.h"
#include "servoControl.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("I'm starting");
}

void loop() {
  delay(10);
  cubeOrientation_tick();
  verifySequence_tick();
  servoControl_tick();
}
