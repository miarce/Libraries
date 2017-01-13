#ifndef StepperMotor_h
#define StepperMotor_h
#define MOTOR_TYPE_UNIPOLAR 0
#define MOTOR_TYPE_BIPOLAR 1
#include <Arduino.h>
class StepperMotor{
  public:
    StepperMotor(byte motorType,byte p1,byte p2,byte p3,byte p4,long pollingTime);
    ~StepperMotor();
    /// Actions
    void moveTo(long absolutePosition);
    void move(long relativePosition);
    boolean monitor();
    void stop();
    void setSendOutput(boolean sendOutput);
    /// Setters and Getters
    long getCurrentPosition();
    long getDestinyPosition();  
    void setCurrentStep(byte currentStep);
    byte getCurrentStep();
    void setHome(long homePosition);
    void setData(byte motorType,byte p1,byte p2,byte p3,byte p4,long pollingTime);
    void setPollingTime(long pollingTime);
    void setMotorType(byte motorType);
    void goHome();    
    void onMovementCompleted(void (*f)());
    void reset();
    
  protected:
    void turnOff();
    void stepForward();
    void stepBackward();
    byte motorPins[4];
    long currentPosition;
    byte currentStep;
    long destinyPosition;
    long homePosition;
    byte motorType;
    long currentTime; //Microseconds
    long pollingTime; //Milliseconds
    long sPollingTime;
    void setStepState();
    void moveForward();
    void moveBackward();
    long onHoldTime;
    boolean sendOutput;  
    boolean monitorStatus;
    void (*onMovementCompletedFunction)();
    boolean movementCompleted;
    boolean stopped;
};
#endif
