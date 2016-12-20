#ifndef DigitalOutput_h
#define DigitalOutput_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalIO.h"

class DigitalOutput : public DigitalIO {
  
  public:
    DigitalOutput();
    DigitalOutput(int pin);
    DigitalOutput(int pin,long timeOn,long timeOff);
    ~DigitalOutput();
        
    //Action methods
    virtual void turnOn();
    virtual void turnOff();
    virtual void toggle();
    virtual void monitor();
    
    //Set listeners
    void onRepetitionsCompleted(void (*f)());
    
    //Setters/Getters
    void setValue(byte value);
    void setTimeOn(long timeOn);
    long getTimeOn();
    void setTimeOff(long timeOff);
    long getTimeOff();
    void setTime(long timeOn,long timeOff);
    void startRepetitions(int maxTimes,long timeOn,long timeOff);
    void stopRepetitions();
    void blink();
    void pulse(long timeOn);
    
  protected:
  
    long timeOn;
    long timeOff;
    void (*onRepetitionsCompletedFunction)();
    long currentStateTime;
    long prevStateTime;
    long maxTimes;
    long currentTimes;
    virtual void innerTurnOn();
    virtual void innerTurnOff();
};

#endif
