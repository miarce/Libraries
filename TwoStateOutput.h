#ifndef TwoStateOutput_h
#define TwoStateOutput_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalOutput.h"

class TwoStateOutput : public DigitalOutput {
  
  public:
    TwoStateOutput();
    TwoStateOutput(int pin);
    TwoStateOutput(int pin,long timeOn,long timeOff);
    ~TwoStateOutput();
};

#endif
