#include "ToggleSwitch.h"

ToggleSwitch::ToggleSwitch():DigitalInput() {
}

ToggleSwitch::ToggleSwitch(int pin):DigitalInput(pin) {
  this->antibounceTime = 10000;
  this->prevTime = micros();
  this->onTime = 0;
  this->offTime = 0;
  if(digitalRead(this->pin) == HIGH) {
    this->onTriggered = true;
    this->isOn = true;
  } else {
    this->offTriggered = true;
    this->isOn = false;
  }
}

ToggleSwitch::~ToggleSwitch() {
}

void ToggleSwitch::monitor() {
  if(digitalRead(this->pin) == HIGH) {
    this->onTime += micros() - this->prevTime;
    this->prevTime = micros();
    this->offTime = 0;
    if(this->onTime > this->antibounceTime) {
      this->isOn = true;
      if(!this->onTriggered) {
        if(this->onOnStateFunction != NULL) this->onOnStateFunction();
        if(this->onToggleFunction != NULL) this->onToggleFunction(this->isOn);
      }    
      this->onTriggered = true;
      this->offTriggered = false;
    }
  } else {
    this->offTime += micros() - this->prevTime;
    this->prevTime = micros();
    this->onTime = 0;
    if(this->offTime > this->antibounceTime) {
      this->isOn = false;
      if(!this->offTriggered) 
      {
        if(this->onOffStateFunction != NULL) this->onOffStateFunction();
        if(this->onToggleFunction != NULL) this->onToggleFunction(this->isOn); 
      }
      this->onTriggered = false;
      this->offTriggered = true;
    }
  }
}

void ToggleSwitch::setAntibounceTime(long time) {
  this->antibounceTime = time;
}

long ToggleSwitch::getAntibounceTime() {
  return this->antibounceTime;
}
