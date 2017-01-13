#include "Button.h"

Button::Button(int pinNumber) {
  this->pin = pinNumber;
  this->pressed = false;
  this->onPressTriggered = false;
  this->clickTime = 0;
  this->prevTime = micros();
  this->longPressTriggered = false;
  this->longPressTime = 3000000;  
  this->antiBounceTime = 30000;
  this->enabled = true;
  this->releaseTime = 0;
  this->clickTriggered = false;  
  this->clickCount = 0;
  this->onClickFunction = NULL;
  this->onDoubleClickFunction = NULL;
  this->onLongPressFunction = NULL;
  this->releaseTriggered = true;
  pinMode(this->pin,INPUT);
}

Button::Button() {
  Button(-1);
}

Button::~Button() {  
}

void Button::onClick(void (*f)()) {
  this->onClickFunction = (*f);
}

void Button::onPress(void (*f)()) {
  this->onPressFunction = (*f);
}

void Button::onDoubleClick(void (*f)()) {
  this->onDoubleClickFunction = (*f);
}

void Button::onLongPress(void (*f)()) {
  this->onLongPressFunction = (*f);    
}

void Button::onRelease(void (*f)(long clickTime)) {
  this->onReleaseFunction = (*f);    
}

void Button::onMultipleClick(void (*f)(int value)) {
  this->onMultipleClickFunction = (*f);    
}

void Button::monitor() {
  pressed = (digitalRead(this->pin)==HIGH);
  monitorAction();
}

void Button::monitorAction() {
  long now = micros();
  if(this->enabled) {
    if(pressed) {
      if(onPressTriggered == false) {
        onPressTriggered = true;
        if(this->onPressFunction != NULL) this->onPressFunction();
      }
      this->clickTime += (now - this->prevTime);
      this->lastClickTime = this->clickTime;
      this->prevTime = now;
      if(this->clickTime > this->longPressTime && !this->longPressTriggered) {
        this->longPressTriggered =true;   
        if(this->onLongPressFunction != NULL) this->onLongPressFunction();
        this->clickCount = 0;
        this->clickTriggered = false;        
      }
      this->releaseTriggered = false;
      this->releaseTime = 0;
    } else {
      onPressTriggered = false;
      if(this->clickTime > this->antiBounceTime && this->clickTime < this->longPressTime) {
        this->clickTriggered = true;
        this->clickCount++;
      }
      this->releaseTime += (now - this->prevTime);
      if(this->clickTriggered && this->releaseTime > 120000) {
        if(this->clickCount < 2) {
          if(this->onClickFunction != NULL) this->onClickFunction();
        } else {
          if(this->onDoubleClickFunction != NULL) this->onDoubleClickFunction();          
        }
        if(this->onMultipleClickFunction != NULL) this->onMultipleClickFunction(clickCount);
        this->clickTriggered = false;
        this->clickCount = 0;
      }
      if(this->releaseTime > 120000) {
        if(!releaseTriggered) {
          releaseTriggered = true;
          if(this->onReleaseFunction != NULL) this->onReleaseFunction(this->lastClickTime);
        }
      }
      this->clickTime = 0;
      this->prevTime = now;
      this->longPressTriggered = false;      
    }
  } else {
    this->clickTime = 0;
    this->prevTime = now;
    this->longPressTriggered = false; 
  }
}

void Button::setLongPressTime(long seconds) {
  this->longPressTime = seconds * 1000000;
}

long Button::getLongPressTime() {
  return this->longPressTime / 1000000;
}

void Button::setEnabled(boolean enabled) {
  this->enabled = enabled;
}

boolean Button::getEnabled() {
  return this->enabled;
}
