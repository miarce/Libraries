#include "PresenceDetector.h"

PresenceDetector::PresenceDetector() : DigitalInput(){
}

PresenceDetector::PresenceDetector(int analogPin): DigitalInput(analogPin) {
  this->objectMinReference = 0;
  this->objectMaxReference = 512;
  this->currentTime = micros();
}

PresenceDetector::PresenceDetector(int analogPin,int objectMinReference,int objectMaxReference): DigitalInput(analogPin) {
  this->objectMaxReference = objectMaxReference;
  this->objectMinReference = objectMinReference;
  this->currentTime = micros();
}

PresenceDetector::~PresenceDetector() {
  
}

void PresenceDetector::onObjectDetected(void (*f)()){
  this->monitor();
  this->onOnStateFunction = (*f);
}

void PresenceDetector::onObjectLost(void (*f)()){
  this->monitor();
  this->onOffStateFunction = (*f);
}

void PresenceDetector::monitor() {
  if(micros() - this->currentTime > 50000) {
    int value = analogRead(this->pin);
    if(value >= objectMinReference &&  value < objectMaxReference) {         
      this->isOn = true;
      if(!this->onTriggered) {
        if(this->onOnStateFunction != NULL) this->onOnStateFunction();
        if(this->onToggleFunction != NULL) this->onToggleFunction(this->isOn);
        //Serial.print(this->pin);Serial.print(" on  ");Serial.print(value);Serial.print(">=");Serial.print(objectMinReference);Serial.print("-");Serial.print(value);Serial.print("<");Serial.println(objectMaxReference);
      }    
      this->onTriggered = true;
      this->offTriggered = false;
    } else {
      this->isOn = false;
      if(!this->offTriggered) 
      {
        if(this->onOffStateFunction != NULL) this->onOffStateFunction();
        if(this->onToggleFunction != NULL) this->onToggleFunction(this->isOn); 
        //Serial.print(this->pin);Serial.print(" off ");Serial.print(value);Serial.print(">=");Serial.print(objectMinReference);Serial.print("-");Serial.print(value);Serial.print("<");Serial.println(objectMaxReference);
      }
      this->onTriggered = false;
      this->offTriggered = true;    
    }
    this->currentTime = micros();
  }
}

boolean PresenceDetector::getIsPresent() {
  return this->isOn;
}
