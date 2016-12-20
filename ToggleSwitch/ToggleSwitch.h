#ifndef ToggleSwitch_h
#define ToggleSwitch_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalInput.h"

class ToggleSwitch : public DigitalInput {
  
  public:
    ToggleSwitch();
    ToggleSwitch(int pin);
    ~ToggleSwitch();
    virtual void monitor(); 
    void setAntibounceTime(long antibounceTime);
    long getAntibounceTime();
    
  protected:
    long antibounceTime;
    
  private:
    long onTime;
    long offTime;
    long prevTime;
};

#endif
