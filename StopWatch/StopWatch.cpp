#include "StopWatch.h"

/**************************************************************************************
*
* Constructor / Destructor
*
**************************************************************************************/

StopWatch::StopWatch(){
  this->currentSeconds = 0;
  this->currentMinutes = 0;
  this->currentHours = 0;
  this->currentDays = 0;
  this->started = false;
}

StopWatch::~StopWatch(){}

/**************************************************************************************
*
* Action Methods
*
**************************************************************************************/

void StopWatch::start() {
  this->currentTime = millis();
  this->started = true;
  if(this->onChangeFunction != NULL) this->onChangeFunction();
  if(this->onStartedFunction != NULL) this->onStartedFunction();
}

void StopWatch::stop() {
  this->started = false;
  if(this->onChangeFunction != NULL) this->onChangeFunction();
  if(this->onStoppedFunction != NULL) this->onStoppedFunction();
}

void StopWatch::reset() {
  this->currentSeconds = 0;
  this->currentMinutes = 0;
  this->currentHours = 0;
  this->currentDays = 0;
  if(this->onChangeFunction != NULL) this->onChangeFunction();
  if(this->onResetFunction != NULL) this->onResetFunction();
}

void StopWatch::monitor() {    
  if(this->started) {
    if((millis() - this->currentTime) >= 1000) { //Check for a second    
      this->currentTime = millis();
      this->currentSeconds++;
      //If 60 seconds have passed add a minute
      if(this->currentSeconds == 60) {
        this->currentMinutes++;
        this->currentSeconds = 0;
      }
      //If 60 minutes have passed add an hour
      if(this->currentMinutes == 60) {
        this->currentHours++;
        this->currentMinutes = 0;
      }
      //If 24 hours have passed add a day
      if(this->currentHours == 24) {
        this->currentDays++;
        this->currentHours = 0;
      }
      if(this->onChangeFunction != NULL) this->onChangeFunction();
    }    
  }
}

/**************************************************************************************
*
* Setters / Getters
*
**************************************************************************************/

long StopWatch::getSeconds() {
  return this->currentSeconds;
}

long StopWatch::getMinutes() {
  return this->currentMinutes;
}

long StopWatch::getHours() {
  return this->currentHours;
}

long StopWatch::getDays() {
  return this->currentDays;
}

boolean StopWatch::getStarted() {
  return this->started;
}

/**************************************************************************************
*
* Event handlers set
*
**************************************************************************************/

void StopWatch::onStarted(void (*f)()){
  this->onStartedFunction = (*f);
}

void StopWatch::onReset(void (*f)()){
  this->onResetFunction = (*f);
}

void StopWatch::onStopped(void (*f)()){
  this->onStoppedFunction = (*f);
}

void StopWatch::onChange(void (*f)()){
  this->onChangeFunction = (*f);
}


