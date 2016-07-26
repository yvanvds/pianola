/*
  ==============================================================================

    Servo.cpp
    Created: 23 Jul 2016 7:16:47pm
    Author:  yvan

  ==============================================================================
*/

#include "Servo.h"

Servo::Servo()
  : status(false)
  , reverse(false)
  , min(0)
  , max(256)
  ,range(256)
{
  
}

  Servo & Servo::setID(int value)
  {
    ID = value;
    return *this;
  }

  Servo & Servo::setName(const String & value)
{
  name = value;
  return *this;
}

Servo & Servo::setStatus(bool value)
{
  status = value;
  return *this;
}

Servo & Servo::setReverse(bool value)
{
  reverse = value;
  return *this;
}

Servo & Servo::setMin(int value)
{
  min = value;
  range = max - min;
  return *this;
}

Servo & Servo::setMax(int value)
{
  max = value;
  range = max - min;
  return *this;
}

Servo & Servo::reset()
{
  name.clear();
  status = false;
  reverse = false;
  min = 0;
  max = 256;
  return *this;
}

int Servo::calculatePos(int value)
{
  if (reverse) {
    value = 255 - value;
  }

  if (range != 256) {
    float f = value / 256.f;
    f *= range;
    f += min;
    return (int)f;
  }

  return value;
}
