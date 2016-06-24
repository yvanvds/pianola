// command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum Cmd {
  CSetMotorPos,
  CSetServoLedColor,
  CSetLedColor,
  CGetMotorPos,
  CDisableServo,
  CMotorStep,
  CMotorDisable,
  CAnalogRead,
  CAnalogWrite,
  CDigitalRead,
  CDigitalWrite,
  CAcknowledge,
  CAnalogPinMode,
  CDigitalPinMode,
  CInitialise,
  CVersion,
  CBreak,
};

class CommandClass
{
 public:
   void update();
   String get(byte index);
   void print();

private:
  String message;
};

extern CommandClass Command;

#endif

