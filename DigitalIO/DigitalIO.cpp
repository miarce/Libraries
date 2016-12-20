#include "DigitalIO.h"

DigitalIO::DigitalIO() : IO() {
}

DigitalIO::DigitalIO(int pin) : IO(pin) {
  this->isOn = false;
  this->onOnStateFunction = NULL;
  this->onOffStateFunction = NULL;
  this->onToggleFunction = NULL;
  this->currentState = OFF;
}

DigitalIO::~DigitalIO(){
}

void DigitalIO::onOnState(void (*f)()){
  this->onOnStateFunction = (*f);
}

void DigitalIO::onOffState(void (*f)()){
  this->onOffStateFunction = (*f);
}

void DigitalIO::onToggle(void (*f)(boolean)){
  this->onToggleFunction = (*f);
}

void DigitalIO::monitor() {
}

int DigitalIO::getCurrentState() {
  return this->currentState;
}

boolean DigitalIO::getIsOn() {
  return this->isOn;
}
