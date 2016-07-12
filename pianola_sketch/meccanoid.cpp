// 
// 
// 

#include "meccanoid.h"

MeccanoidClass::MeccanoidClass() {
  for (byte pin = 0; pin <= _highestPin; pin++) {
    _pin[pin] = nullptr;
  }
  _pinWithHead = nullptr;
}

void MeccanoidClass::initIfNeeded(byte pin) {
  if (pin >= _lowestPin && pin <= _highestPin) {
    if (_pin[pin] == nullptr) {
      _pin[pin] = new pinClass;
      _pin[pin]->init(pin);
      if (_pin[pin]->hasHeadLight()) {
        _pinWithHead = _pin[pin];
      }
    } 
  }
}

void MeccanoidClass::update() {
  int startTime = millis();
  bool printTime = false;
  for (byte pin = _lowestPin; pin <= _highestPin; pin++) {
    if (_pin[pin] != nullptr) {
      if(_pin[pin]->update()) printTime = true;
    }
  }

  if(printTime) {
    int duration = millis() - startTime;
    Serial.println("Servo update: " + String(duration));
  }
}

void MeccanoidClass::actionBreak() {
  for (byte pin = _lowestPin; pin <= _highestPin; pin++) {
    if (_pin[pin] != nullptr) _pin[pin]->actionBreak();
  }
}

void MeccanoidClass::setServoColor(byte pin, byte servo, byte color) {
  if (pin >= _lowestPin && pin <= _highestPin) {
    if (_pin[pin] != nullptr) _pin[pin]->setServoColor(servo, color);
  }
}

void MeccanoidClass::setHeadColor(byte r, byte g, byte b, byte f) {
  if (_pinWithHead != nullptr) _pinWithHead->setHeadColor(r, g, b, f);
}

void MeccanoidClass::setServoPos(byte pin, byte servo, byte pos, byte time) {
  if (pin >= _lowestPin && pin <= _highestPin) {
    if (_pin[pin] != nullptr) _pin[pin]->setServoPos(servo, pos, time);
  }
}



MeccanoidClass Meccanoid;

