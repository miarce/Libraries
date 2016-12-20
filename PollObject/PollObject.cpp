#include "PollObject.h"

PollObject::PollObject(long pTime) {
  pollingTime = pTime;
  currentTime = micros();
  onUpdateResult = false;
  maxTimes = -1;
  currentTimes = 0;
  started = true;
  this->onPollFunction = NULL;
  this->onRepetitionsCompletedFunction = NULL;
}

PollObject::~PollObject(){}

long PollObject::getPollingTime() {
  return pollingTime;
}

void PollObject::setPollingTime(long pTime) {
  pollingTime = pTime;
}

void PollObject::poll() {
  if(started) {
    if((micros() - currentTime) >= pollingTime) {
      currentTime = micros();
      onUpdateResult = true;
      if(this->onPollFunction != NULL) this->onPollFunction();
      currentTimes++;
      if(currentTimes >= maxTimes && maxTimes != -1) {
        stop();
        if(onRepetitionsCompletedFunction != NULL) onRepetitionsCompletedFunction();        
      }
    }
  }
}

void PollObject::monitor() {
  poll();
}

boolean PollObject::onUpdate() {
  boolean output = onUpdateResult;
  onUpdateResult = false;
  poll();
  return output;  
}

void PollObject::onPoll(void (*f)()) {
  this->onPollFunction = (*f);
}

void PollObject::onRepetitionsCompleted(void (*f)()) {
  this->onRepetitionsCompletedFunction = (*f);
}

void PollObject::start() {
  start(-1);
}

void PollObject::start(int times) {
  started = true;
  currentTime = micros();
  maxTimes = times;
  currentTimes = 0;
}

void PollObject::stop() {
  started = false;
  maxTimes = -1;
  currentTimes = 0;
}
