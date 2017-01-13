#include "TwoStateOutput.h"

TwoStateOutput::TwoStateOutput():DigitalOutput() {
}

TwoStateOutput::TwoStateOutput(int pin):DigitalOutput(pin) {
}

TwoStateOutput::TwoStateOutput(int pin,long timeOn,long timeOff):DigitalOutput(pin) {
  this->timeOn = timeOn;
  this->timeOff = timeOff;  
  this->prevStateTime = millis();
  this->maxTimes = -1;
  this->currentTimes = 0;
}

TwoStateOutput::~TwoStateOutput() {}
