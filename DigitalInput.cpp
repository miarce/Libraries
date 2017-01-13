#include "DigitalInput.h"

DigitalInput::DigitalInput() : DigitalIO(){

}

DigitalInput::DigitalInput(int pin): DigitalIO(pin) {  
  this->onTriggered = false;
  this->offTriggered = true;
  this->monitor();
}

DigitalInput::~DigitalInput() {
  
}

void DigitalInput::monitor() {
  if(digitalRead(this->pin) == HIGH) {
    this->isOn = true;
    if(!this->onTriggered) {
      if(this->onOnStateFunction != NULL) this->onOnStateFunction();
      if(this->onToggleFunction != NULL) this->onToggleFunction(this->isOn);
    }    
    this->onTriggered = true;
    this->offTriggered = false;
  } else {
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
