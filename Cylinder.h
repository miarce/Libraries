 #ifndef Cylinder_h
#define Cylinder_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "DigitalOutput.h"

class Cylinder : public DigitalOutput
{
  
  public:
  
    Cylinder(int pin);
    Cylinder(int pin,long timeOn,long timeOff);
    Cylinder(int pin,long timeOn,long timeOff,long travelOnTime,long travelOffTime);
    ~Cylinder();
    
    //Static const
    static const int TRAVELING_ON = 2;
    static const int TRAVELING_OFF = 3;
    
    //Action methods
    void turnOn();
    void turnOff();
    
    //Set listeners
    void onTravelOnStarted(void (*f)());
    void onTravelOffStarted(void (*f)());
    
    //Setters/Getters    
    void setTravelOnTime(long travelOnTime);
    long getTravelOnTime();
    void setTravelOffTime(long travelOffTime);
    long getTravelOffTime();
    
    void setPaused(boolean paused);
    boolean getPaused();
    void monitor();    
    
  protected:

    long travelOnTime;
    long travelOffTime;
    boolean paused;
    void (*onTravelOnStartedFunction)();
    void (*onTravelOffStartedFunction)();
    
};

#endif

