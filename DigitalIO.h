#ifndef DigitalIO_h
#define DigitalIO_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "IO.h"

class DigitalIO : public IO {
  
  public:  
    //Constructors/Destructors
    DigitalIO();
    DigitalIO(int pin);
    ~DigitalIO();
    
    void onOnState(void (*f)());
    void onOffState(void (*f)());
    void onToggle(void (*f)(boolean));
    virtual void monitor();
    int getCurrentState();
    boolean getIsOn();
    
    //Static const
    static const int OFF = 0;
    static const int ON = 1;
    static const int NONE = -1;
      
  protected:
    void (*onOnStateFunction)();
    void (*onOffStateFunction)();
    void (*onToggleFunction)(boolean);
    boolean isOn;
    int currentState;
    
};

#endif
