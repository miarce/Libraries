#ifndef Button_h
#define Button_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

class Button {
  
  public:
    /**
    * Constructor / Destructor
    */
    Button();
    Button(int pinNumber);
    ~Button();
    
    /**
    * Listener assignment
    */
    void onClick(void (*f)());
    void onPress(void (*f)());
    void onDoubleClick(void (*f)());
    void onLongPress(void (*f)());
    void onMultipleClick(void (*f)(int value));
    void onRelease(void (*f)(long clickTime));
    
    /**
    * Monitor the button activity
    */
    virtual void monitor();   
    
    /**
    * Enabled Setter / Getter
    */
    void setEnabled(boolean enabled);
    boolean getEnabled();
    
    /**
    * Long Press Time Setter / Getter
    */
    void setLongPressTime(long seconds);
    long getLongPressTime();
    
  private:
    int pin;
    void (*onClickFunction)();
    void (*onPressFunction)();
    void (*onLongPressFunction)();
    void (*onDoubleClickFunction)();
    void (*onMultipleClickFunction)(int value);
    void (*onReleaseFunction)(long clickTime);
    long clickTime;
    long lastClickTime; //Last click time record
    long prevTime;
    boolean longPressTriggered;
    boolean clickTriggered;
    boolean releaseTriggered;
    long longPressTime;
    long antiBounceTime;
    long releaseTime;
    int clickCount;
    boolean enabled;
    boolean onPressTriggered;    
   
  protected:
    boolean pressed;
    void monitorAction();
};

#endif
