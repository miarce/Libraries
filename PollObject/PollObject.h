#ifndef PollObject_h
#define PollObject_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif
//Object with a polling time (microseconds)
class PollObject {  
  public:
    /**
    * Constructor
    */
    PollObject(long pollingTime);
    
    /**
    * Destructor
    */
    ~PollObject();
    
    /**
    * Polling Time getter/setter
    */
    long getPollingTime();
    void setPollingTime(long pollingTime);
    
    /** 
    * Set the function to execute every time the polling time get completed
    */
    void onPoll(void (*f)());
    
    /** 
    * Set the function to execute when the set repetitions complete
    */
    void onRepetitionsCompleted(void (*f)());
    
    /**
    * The function need to be in the main loop
    */
    void monitor();
    
    void start();
    
    void start(int times);
    
    void stop();
    
  private:
    /**
    * Current Time in microseconds
    */
    long currentTime;
    /**
    * Polling Time in microseconds
    */
    long pollingTime;     
    /**
    * This method has to be in the main loop of the program and has to be executed faster than the polling time
    * EDIT: Now the method is used inside the onUpdate so theres no need anymore to have it in the main loop
    */
    void poll();
    
    /**
    * On update result
    */
    boolean onUpdateResult;
    
    void (*onPollFunction)();
    void (*onRepetitionsCompletedFunction)();
    
    /**
    * Returns true when a the object needs to be updated
    * EDIT: Theres no need to use the onUpdate to check for the occurrence, just assign the method to execute with the onPoll event
    */
    boolean onUpdate();
    
    boolean started;
    
    int maxTimes;
    
    int currentTimes;
};
#endif

