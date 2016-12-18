#pragma once
#include "MyMath.h"

template<class T>
class Interpolator
{
public:
  void set(const T & newTarget, float speed) {
    start = current;
    pos = 0;
    target = newTarget;
    this->speed = speed;
    if (speed == 0) current = start = target;
  }

  void overrideStart(const T & newStart) {
    start = newStart;
  }

  const T & update(float delta) // update and return the current value
  {
    if (speed > 0) {
      pos += delta * speed;
      if (pos < 0) pos = 0;
      if (pos > 1) pos = 1;
      current = Lerp(start, target, pos);
    }
    return current;
  }

  const T & operator()() // return current value
  {
    return current;
  }

  bool targetReached() {
    return pos == 1;
  }

private:
  T start;
  T target;
  T current;

  float speed;
  float pos;
};

