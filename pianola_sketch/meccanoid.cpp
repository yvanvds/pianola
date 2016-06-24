// 
// 
// 

#include "meccanoid.h"

MeccanoidClass::MeccanoidClass() {
  for (byte pin = 0; pin <= highestDigitalPin; pin++) {
    digitalPin[pin].setID(pin);
  }

  for (byte pin = 0; pin <= highestAnalogPin; pin++) {
    analogPin[pin].setID(pin);
  }
}

void MeccanoidClass::init(byte pin) {
  if (pin >= lowestDigitalPin && pin <= highestDigitalPin) {
    digitalPin[pin].init();
  }
}

void MeccanoidClass::update() {
  for (byte pin = lowestDigitalPin; pin <= highestDigitalPin; pin++) {
    digitalPin[pin].update();
  }

  for (byte pin = lowestAnalogPin; pin <= highestAnalogPin; pin++) {
    analogPin[pin].update();
  }
}

void MeccanoidClass::actionBreak() {
  for (byte pin = lowestDigitalPin; pin <= highestDigitalPin; pin++) {
    digitalPin[pin].actionBreak();
  }
}

void MeccanoidClass::setLedColor(byte pin) {
  if (pin >= lowestDigitalPin && pin <= highestDigitalPin) {
    digitalPin[pin].setLedColor();
  }
}

void MeccanoidClass::setServoColor(byte pin) {
  if (pin >= lowestDigitalPin && pin <= highestDigitalPin) {
    digitalPin[pin].setServoColor();
  }
}

void MeccanoidClass::setMotorPos(byte pin) {
  if (pin >= lowestDigitalPin && pin <= highestDigitalPin) {
    digitalPin[pin].setMotorPos();
  }
}



MeccanoidClass Meccanoid;

