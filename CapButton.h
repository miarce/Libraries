#ifndef CapButton_h
#define CapButton_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "Button.h"
#include "CapSense.h"

class CapButton : public Button 
{
  
  public:
    
    CapButton(int sendPin,int recPin);
    ~CapButton();   
    void monitor(); 
    
  private:
    int sendPin;
    int recPin;  
    CapSense cap;  
};

#endif
