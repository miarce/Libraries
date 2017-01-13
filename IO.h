#ifndef IO_h
#define IO_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

class IO {
  
    public:  
      //Constructors/Destructors
      IO();
      IO(int pin);
      ~IO();      
      int getPin();
    
    protected:
      int pin;
    
};

#endif
