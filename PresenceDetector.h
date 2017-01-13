#ifndef PresenceDetector_h
#define PresenceDetector_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalInput.h"

class PresenceDetector : public DigitalInput {
  
  public:
    PresenceDetector();
    PresenceDetector(int analogPin);
    PresenceDetector(int analogPin,int objectMinReference,int objectMaxReference);
    ~PresenceDetector();
    virtual void monitor();
    void onObjectDetected(void (*f)());
    void onObjectLost(void (*f)());
    boolean getIsPresent();
  
  protected:
    int objectMaxReference;
    int objectMinReference;
    
  private:
    long currentTime;
    
};

#endif
