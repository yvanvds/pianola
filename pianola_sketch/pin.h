// pin.h

#ifndef _PIN_h
#define _PIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum PinSetup : byte {
  PS_Unused,
  PS_Input,
  PS_InputLatchingHigh,
  PS_InputLatchingLow,
  PS_Output,
  PS_OutputPWM,
  PS_Meccanoid
};

class pinClass {
public:
  pinClass();
  
  void setID(byte ID) { this->ID = ID; }
  bool update();

protected:
  PinSetup setup;
  byte ID;
  
  // latch
  bool          latchTriggered        ;
  unsigned long latchDebounceStartTime;
};

class digitalPinClass : public pinClass {
public:
  digitalPinClass();

  void init();
  void update();

  byte getMotorPos(byte pos);
  void actionBreak  ();
  void setLedColor  ();
  void setMotorPos  ();
  void setServoColor();

private:
  byte communicate(byte pos);

  static void sendByte        (byte pin, byte data);
  static byte recvByte        (byte pin           );
  

  // state
  byte currentValue[4];
  byte startValue  [4];
  byte endValue    [4];

  unsigned int  duration [4];
  unsigned long startTime[4];

  byte data[4];
  byte type[4];
};

#endif

