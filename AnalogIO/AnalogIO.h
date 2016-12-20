#ifndef AnalogIO_h
#define AnalogIO_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
#include "IO.h"

class AnalogIO : public IO {
  
  public:  
    //Constructors/Destructors
    AnalogIO();
    AnalogIO(int pin);
    ~AnalogIO();
};

#endif
