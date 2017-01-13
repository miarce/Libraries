#ifndef StopWatch_h
#define StopWatch_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

class StopWatch {
  
  public:
    StopWatch();
    ~StopWatch();
        
    //Action methods
    virtual void start();
    virtual void stop();
    virtual void reset();
    virtual void monitor();
    
    //Set listeners
    void onReset(void (*f)());
    void onStarted(void (*f)());
    void onStopped(void (*f)());
    void onChange(void (*f)());
    
    //Setters/Getters
    long getSeconds();
    long getMinutes();
    long getHours();
    long getDays();
    boolean getStarted();
    
  protected:
  
    boolean started;
    void (*onResetFunction)();
    void (*onStartedFunction)();
    void (*onStoppedFunction)();
    void (*onChangeFunction)();
    long currentSeconds;
    long currentMinutes;
    long currentHours;
    long currentDays;
    long currentTime;
};

#endif
