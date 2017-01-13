#include "DigitalOutput.h"

DigitalOutput::DigitalOutput():DigitalIO() {
}

DigitalOutput::DigitalOutput(int pin):DigitalIO(pin) {
  DigitalOutput(pin,-1,-1);
}

DigitalOutput::DigitalOutput(int pin,long timeOn,long timeOff):DigitalIO(pin) {
  this->timeOn = timeOn;
  this->timeOff = timeOff;
  this->currentState = OFF;
  this->isOn = false;
  this->onOnStateFunction = NULL;
  this->onOffStateFunction = NULL;
  this->onToggleFunction = NULL;  
  this->prevStateTime = millis();
  this->maxTimes = -1;
  this->currentTimes = 0;
  pinMode(pin,OUTPUT);
}

DigitalOutput::~DigitalOutput() {}

void DigitalOutput::setValue(byte value) {
  if(value == HIGH) 
  innerTurnOn();
  else
  innerTurnOff();
}

void DigitalOutput::turnOn() {  
  this->timeOn = -1;
  this->timeOff = -1;  
  this->innerTurnOn();
}

void DigitalOutput::turnOff() {  
  this->timeOn = -1;
  this->timeOff = -1;
  this->maxTimes = -1;
  this->innerTurnOff();
}

void DigitalOutput::innerTurnOn() {
  if(this->currentState == OFF) {
    digitalWrite(pin,HIGH);
    this->isOn = true;
    this->currentState = ON;
    this->currentStateTime = micros();
    if(onOnStateFunction != NULL) onOnStateFunction();
    if(onToggleFunction != NULL) onToggleFunction(this->isOn);
  }
}

void DigitalOutput::innerTurnOff() {
  if(this->currentState == ON) {
    digitalWrite(pin,LOW); 
    this->isOn = false;    
    this->currentState = OFF;
    this->currentStateTime = micros();
    if(onOffStateFunction != NULL) onOffStateFunction();
    if(onToggleFunction != NULL) onToggleFunction(this->isOn);    
    //Check for max repetitions
    if(maxTimes > -1) {
      currentTimes++;
      if(currentTimes >= maxTimes) {
        currentTimes = 0;
        maxTimes = -1;
        timeOn = -1;
        timeOff = -1;
        if(onRepetitionsCompletedFunction != NULL) onRepetitionsCompletedFunction();
      }
    }    
  }
}

void DigitalOutput::toggle(){
  if(currentState == ON) {
    this->turnOff();
  } else {
    this->turnOn();
  }
}

void DigitalOutput::startRepetitions(int times,long timeOn,long timeOff) {
  digitalWrite(pin,HIGH); 
  this->isOn = true;    
  this->currentState = ON;
  this->timeOn = timeOn;
  this->timeOff = timeOff;
  this->maxTimes = times;
  this->currentTimes = 0;
  this->currentStateTime = micros();
}

void DigitalOutput::stopRepetitions() {
  this->turnOff();
}

void DigitalOutput::pulse(long timeOn) {
  this->startRepetitions(1,timeOn,-1);
}

void DigitalOutput::monitor() {
  switch(currentState) {
    case ON:
      if(timeOn > -1) {
        if(micros() - currentStateTime >= timeOn) {
          currentStateTime = micros();
          this->innerTurnOff();
        }
      }
      break;
    case OFF:
      if(timeOff > -1) {
        if(micros() - currentStateTime >= timeOff) {
          currentStateTime = micros();
          this->innerTurnOn();
        }
      }
      break;
  }
}

void DigitalOutput::onRepetitionsCompleted(void (*f)()){
  this->onRepetitionsCompletedFunction = (*f);
}

void DigitalOutput::blink() {
  digitalWrite(pin,HIGH); 
  this->isOn = true;    
  this->currentState = ON;
  this->currentStateTime = micros();
  this->timeOn = 250000;
  this->timeOff = 250000;
  this->maxTimes = -1;
  this->currentTimes = 0;
}

void DigitalOutput::setTime(long timeOn,long timeOff){
  this->timeOn = timeOn;
  this->timeOff = timeOff;
  currentStateTime = micros();
}

void DigitalOutput::setTimeOn(long timeOn){
  this->timeOn = timeOn;
}

long DigitalOutput::getTimeOn(){
  return this->timeOn;
}

void DigitalOutput::setTimeOff(long timeOff){
  this->timeOff = timeOff;
}

long DigitalOutput::getTimeOff(){
  return this->timeOff;
}

