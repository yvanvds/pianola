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
#include "../../Shared/Messages.h"
#include "BodyPart.h"
#include "Fifo.h"


class Meccanoid : public Robot, private HighResolutionTimer {
public:
  Meccanoid();

  virtual void handleMessage(const OSCMessage & message);

  void initialize();
  virtual void update();

  Servo * getServo(const    String & name);
  Servo * getServo(unsigned int      ID  );

  void resetServos();

  BodyPart & getBodyPart(const String & name);
  BodyPart & getBodyPart(BODYPART part);

private:
  void hiResTimerCallback() override;

  Servo servo[SERVO_COUNT];
  
  BodyPart part[(unsigned int)BODYPART::NUM];

  Fifo messageBuffer;
};



#endif  // MECCANOID_H_INCLUDED
