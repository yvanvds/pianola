/*
  ==============================================================================

    Servo.h
    Created: 23 Jul 2016 7:16:47pm
    Author:  yvan

  ==============================================================================
*/

#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

#include "JuceHeader.h"

class Servo {
public:
  Servo();

  Servo & setID     (      int      value);       int      getID     () { return ID     ; }
  Servo & setName   (const String & value); const String & getName   () { return name   ; }
  Servo & setStatus (      bool     value);       bool     getStatus () { return status ; }
  Servo & setReverse(      bool     value);       bool     getReverse() { return reverse; }
  Servo & setMin    (      int      value);       int      getMin    () { return min    ; }
  Servo & setMax    (      int      value);       int      getMax    () { return max    ; }

  Servo & reset();
  int calculatePos(int value);

private:
  int ID;
  String name;
  bool status;

  bool reverse;
  int min, max;
  int range;
};




#endif  // SERVO_H_INCLUDED
