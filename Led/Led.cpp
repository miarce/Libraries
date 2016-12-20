#include "Led.h"

Led::Led(int pin) : DigitalOutput(pin) {
  
}

Led::Led(int pin,long timeOn, long timeOff) : DigitalOutput(pin,timeOn, timeOff) {
  
}

Led::~Led() {
  
}
