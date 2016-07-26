/*
  ==============================================================================

    Meccanoid.h
    Created: 7 Jun 2016 7:11:29pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MECCANOID_H_INCLUDED
#define MECCANOID_H_INCLUDED

#include "Robot.h"
#include "JuceHeader.h"
#include "Servo.h"
#include "Defines.h"



class Meccanoid : public Robot {
public:
  Meccanoid();

  virtual void handleMessage(const Array<String> & tokens, const OSCMessage & message);

  void initialize();

  Servo * getServo(const    String & name);
  Servo * getServo(unsigned int      ID  );

  void resetServos();

private:

  Servo servo[SERVO_COUNT];

};



#endif  // MECCANOID_H_INCLUDED
