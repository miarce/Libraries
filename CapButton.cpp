#include "CapButton.h"

CapButton::CapButton(int sendPin,int recPin) : Button(-1) {
  this->sendPin = sendPin;
  this->recPin = recPin;
  this->cap = CapSense((uint8_t) sendPin,(uint8_t) recPin);
}

CapButton::~CapButton() {
}

void CapButton::monitor() {
  pressed = (cap.capSense(50) > 130);
  monitorAction();
}

