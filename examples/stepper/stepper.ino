// For Arduino

#include <youkey_stepper.h>

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  youkey_turnStepperMotor(3,true,0);
  digitalWrite(2, youkey_getStepperBit(0) & 0b0001);
  digitalWrite(3, youkey_getStepperBit(0) & 0b0010);
  digitalWrite(4, youkey_getStepperBit(0) & 0b0100);
  digitalWrite(5, youkey_getStepperBit(0) & 0b1000);
  delay(500);
}
