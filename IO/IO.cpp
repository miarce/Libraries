#include "IO.h"

IO::IO() {
}

IO::IO(int pin) {
  this->pin = pin;
}

IO::~IO() {
}

int IO::getPin() {
  return this->pin;
}
