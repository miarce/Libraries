#include "Cylinder.h"

Cylinder::Cylinder(int pinNumber):DigitalOutput(pinNumber) {
  this->travelOnTime = 0;
  this->travelOffTime = 0;
  this->paused = false;
  this->onTravelOnStartedFunction = NULL;
  this->onTravelOffStartedFunction = NULL;
}

Cylinder::Cylinder(int pinNumber,long timeOn,long timeOff):DigitalOutput(pinNumber,timeOn,timeOff) {
  this->travelOnTime = 0;
  this->travelOffTime = 0;
  this->paused = false;
  this->onTravelOnStartedFunction = NULL;
  this->onTravelOffStartedFunction = NULL;
}

Cylinder::Cylinder(int pinNumber,long timeOn,long timeOff,long travelOnTime,long travelOffTime):DigitalOutput(pinNumber,timeOn,timeOff) {
  this->travelOnTime = travelOnTime;
  this->travelOffTime = travelOffTime;
  this->paused = false;
  this->onTravelOnStartedFunction = NULL;
  this->onTravelOffStartedFunction = NULL;
}

Cylinder::~Cylinder() {}

void Cylinder::turnOn() {
  digitalWrite(this->pin,HIGH);
  if(!isOn) {    
    isOn = true;    
    currentState = TRAVELING_ON;
    currentStateTime = 0;
    if(onTravelOnStartedFunction != NULL) onTravelOnStartedFunction();   
  }
}

void Cylinder::turnOff() {
  digitalWrite(this->pin,LOW);
  if(isOn) {    
    isOn = false;    
    currentState = TRAVELING_OFF;
    currentStateTime = 0;
    if(onTravelOffStartedFunction != NULL) onTravelOffStartedFunction();    
  }
}

void Cylinder::monitor() {
  switch(currentState) {
    case TRAVELING_ON:
      if(currentStateTime >= travelOnTime) {
        currentStateTime = 0;        
        currentState = ON;
        if(onOnStateFunction != NULL) onOnStateFunction();
        if(onToggleFunction != NULL) onToggleFunction(true);
      }
      break;
    case ON:
      if(timeOn > -1) {
        if(currentStateTime >= timeOn) {
          currentStateTime = 0;
          this->turnOff();
        }
      }
      break;
    case TRAVELING_OFF:
      if(currentStateTime >= travelOffTime) {
        currentStateTime = 0;        
        currentState = OFF;
        if(onOffStateFunction != NULL) onOffStateFunction();
        if(onToggleFunction != NULL) onToggleFunction(false);
      }
      break;
    case OFF:
      if(timeOff > -1) {
        if(currentStateTime >= timeOff) {
          currentStateTime = 0;
          this->turnOn();
        }
      }
      break;
  }
  currentStateTime += (micros() - prevStateTime);
  prevStateTime = micros();
}

void Cylinder::onTravelOnStarted(void (*f)()){
  this->onTravelOnStartedFunction = (*f);
}

void Cylinder::onTravelOffStarted(void (*f)()){
  this->onTravelOffStartedFunction = (*f);
}

void Cylinder::setTravelOnTime(long travelOnTime){
  this->travelOnTime = travelOnTime;
}

long Cylinder::getTravelOnTime(){
  return this->travelOnTime;
}

void Cylinder::setTravelOffTime(long travelOffTime){
  this->travelOffTime = travelOffTime;
}

long Cylinder::getTravelOffTime(){
  return this->travelOffTime;
}

void Cylinder::setPaused(boolean paused){
  this->paused = paused;
}

boolean Cylinder::getPaused(){
  return this->paused;
}

