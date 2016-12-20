#include "StepperMotor.h"

StepperMotor::StepperMotor(byte mType,byte p1,byte p2,byte p3,byte p4,long pTime){
  currentPosition = 0;
  currentStep = 0;
  homePosition = 0;
  destinyPosition = 0;
  currentTime = micros();
  onHoldTime = 0;
  sendOutput = true;
  setData(mType,p1,p2,p3,p4,pTime);
  pinMode(p1,OUTPUT);
  pinMode(p2,OUTPUT);
  pinMode(p3,OUTPUT);
  pinMode(p4,OUTPUT);
  this->onMovementCompletedFunction = NULL;
  this->stopped = true;
  setStepState();
}

StepperMotor::~StepperMotor(){}

void StepperMotor::setData(byte mType,byte p1,byte p2,byte p3,byte p4,long pTime) {
  pollingTime = pTime;
  sPollingTime = pTime;
  motorType = mType;
  motorPins[0] = p1;
  motorPins[1] = p2;
  motorPins[2] = p3;
  motorPins[3] = p4;
}

void StepperMotor::setSendOutput(boolean sOutput) {
  sendOutput = sOutput;
}

void StepperMotor::stepForward(){
  destinyPosition++;
}

void StepperMotor::stepBackward(){
  destinyPosition--;
}

void StepperMotor::moveForward(){
  currentStep = (currentStep>=3)? 0:currentStep+1;
  currentPosition++;
  setStepState();
}

void StepperMotor::moveBackward(){
  currentStep = (currentStep<=0)? 3:currentStep-1;
  currentPosition--;
  setStepState();
}

byte StepperMotor::getCurrentStep() {
  return currentStep;
}

void StepperMotor::setCurrentStep(byte cStep) {
  currentStep = cStep;
}

void StepperMotor::stop(){
  reset();
}

long StepperMotor::getCurrentPosition(){
  return currentPosition;
}

long StepperMotor::getDestinyPosition(){
  return destinyPosition;
}

void StepperMotor::setHome(long hPosition){
  homePosition = hPosition;
}

void StepperMotor::goHome(){
  stopped = false;
  destinyPosition = homePosition;
}

void StepperMotor::moveTo(long absolutePosition){
  movementCompleted = false;
  stopped = false;
  destinyPosition = absolutePosition;
}

void StepperMotor::move(long relativePosition){
  movementCompleted = false;
  stopped = false;
  destinyPosition = currentPosition + relativePosition;
}

void StepperMotor::setPollingTime(long pTime) {
  pollingTime = pTime;
}

void StepperMotor::setMotorType(byte mType) {
  motorType = mType;
}

/// Checks the current destiny against the curren position and take action if needed
boolean StepperMotor::monitor() { 
  if((onHoldTime) >= pollingTime) {
    monitorStatus = (destinyPosition==currentPosition);
    onHoldTime = 0;
    if(destinyPosition != currentPosition) {
      pollingTime = sPollingTime;
      movementCompleted = false;
      if(destinyPosition < currentPosition) {
        moveBackward();
      } else {
        moveForward();
      }
    } else {
      turnOff();
      if(movementCompleted == false) {
        if(this->onMovementCompletedFunction != NULL && this->stopped == false) {
          this->onMovementCompletedFunction();
        }
        stopped = false;
        movementCompleted = true;
      }
    }      
  } else {
    onHoldTime += micros()-currentTime;
  }
  currentTime = micros();
  return monitorStatus;
}

void StepperMotor::turnOff() {  
  if(sendOutput) { 
    currentStep = 1;
    pollingTime = 25000;
    if(digitalRead(motorPins[0]) == HIGH || digitalRead(motorPins[0]) == HIGH || digitalRead(motorPins[0]) == HIGH || digitalRead(motorPins[0]) == HIGH) {
      digitalWrite(motorPins[0],LOW);
      digitalWrite(motorPins[1],LOW);
      digitalWrite(motorPins[2],LOW);
      digitalWrite(motorPins[3],LOW);
    } else {
      setStepState();
    }
  }
}

void StepperMotor::setStepState() {
  if(sendOutput) {
    if(motorType == MOTOR_TYPE_BIPOLAR) {
      switch(currentStep) {
        case 0:
          digitalWrite(motorPins[0],HIGH);
          digitalWrite(motorPins[1],LOW);
          digitalWrite(motorPins[2],HIGH);
          digitalWrite(motorPins[3],LOW);
          break;
          
        case 1:
          digitalWrite(motorPins[0],HIGH);
          digitalWrite(motorPins[1],LOW);
          digitalWrite(motorPins[2],LOW);
          digitalWrite(motorPins[3],HIGH);
          break;
          
        case 2:
          digitalWrite(motorPins[0],LOW);
          digitalWrite(motorPins[1],HIGH);
          digitalWrite(motorPins[2],LOW);
          digitalWrite(motorPins[3],HIGH); 
          break;
          
        case 3:
          digitalWrite(motorPins[0],LOW);
          digitalWrite(motorPins[1],HIGH);
          digitalWrite(motorPins[2],HIGH);
          digitalWrite(motorPins[3],LOW); 
          break;
      }
    } else {
      switch(currentStep) {
        case 0:
          digitalWrite(motorPins[0],HIGH);
          digitalWrite(motorPins[1],LOW);
          digitalWrite(motorPins[2],LOW);
          digitalWrite(motorPins[3],LOW);
          break;
          
        case 1:
          digitalWrite(motorPins[0],LOW);
          digitalWrite(motorPins[1],HIGH);
          digitalWrite(motorPins[2],LOW);
          digitalWrite(motorPins[3],LOW);
          break;
          
        case 2:
          digitalWrite(motorPins[0],LOW);
          digitalWrite(motorPins[1],LOW);
          digitalWrite(motorPins[2],HIGH);
          digitalWrite(motorPins[3],LOW); 
          break;
          
        case 3:
          digitalWrite(motorPins[0],LOW);
          digitalWrite(motorPins[1],LOW);
          digitalWrite(motorPins[2],LOW);
          digitalWrite(motorPins[3],HIGH); 
          break;
      }  
    }
  }
}

void StepperMotor::onMovementCompleted(void (*f)()){
  this->onMovementCompletedFunction = (*f);
}

void StepperMotor::reset() {
  destinyPosition = 0;
  currentPosition = 0;
  this->stopped = true;
}
