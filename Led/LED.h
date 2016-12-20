#ifndef Led_h
#define Led_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalOutput.h"

class Led: public DigitalOutput {
  
  public:
    Led(int pin);
    Led(int pin,long timeOn, long timeOff);
    ~Led();
    
};

#endif

