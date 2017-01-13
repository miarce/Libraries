#include "AnalogInput.h"

AnalogInput::AnalogInput() : AnalogIO(){

}

AnalogInput::AnalogInput(int pin): AnalogIO(pin) {  
  this->currentTime = micros();
  this->monitor();
}

AnalogInput::~AnalogInput() {
  
}

void AnalogInput::monitor() {
  if((micros() - this->currentTime) > 50000) {
    if(abs(analogRead(this->pin) - value) > resolution) {
      value = analogRead(this->pin);
      if(this->onChangeFunction != NULL) this->onChangeFunction(value);      
    }
    this->currentTime = micros();
  }
}

int AnalogInput::getValue() {
  value = analogRead(this->pin);
  return value;
}


void AnalogInput::onChange(void (*f)(int value)){
  this->onChangeFunction = (*f);
}

void AnalogInput::setResolution(int resolution) {
  this->resolution = resolution;
}
