#ifndef DigitalInput_h
#define DigitalInput_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalIO.h"

class DigitalInput : public DigitalIO {
  public:
    DigitalInput();
    DigitalInput(int pin);
    ~DigitalInput();
    virtual void monitor();    
    
  protected:
    boolean onTriggered;
    boolean offTriggered;
  
};

#endif
