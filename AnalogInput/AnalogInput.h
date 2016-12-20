#ifndef AnalogInput_h
#define AnalogInput_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "AnalogIO.h"

class AnalogInput : public AnalogIO {
  public:
    AnalogInput();
    AnalogInput(int pin);
    ~AnalogInput();
    
    void onChange(void (*f)(int value));
    int getValue(); 
    virtual void monitor();
    void setResolution(int resolution);
    
  protected:
    void (*onChangeFunction)(int value);
    int value;
    int resolution;
  
  private:
    long currentTime;
  
};

#endif
