// meccanoid.h

#ifndef _MECCANOID_h
#define _MECCANOID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pin.h"

enum CommandResponse : byte {
  CR_Unknown,
  CR_OK,
  CR_None
};

class MeccanoidClass
{
public:
  MeccanoidClass();
  
  void init(byte pin);
	void update();
  void actionBreak(); // break long running commands
  void setLedColor(byte pin);
  void setMotorPos(byte pin);
  void setServoColor(byte pin);

private:
  static const byte lowestDigitalPin  = 2 ;
  static const byte highestDigitalPin = 13;
  static const byte lowestAnalogPin   = 0 ;
  static const byte highestAnalogPin  = 5 ;

  digitalPinClass digitalPin[highestDigitalPin + 1];
  pinClass        analogPin [highestAnalogPin  + 1];

};

extern MeccanoidClass Meccanoid;

#endif

