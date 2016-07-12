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
  
  void init  (byte ID);
  bool update(       );

  byte getMotorPos  (byte servo                                  ) const;
  void setServoColor(byte servo, byte color                      );
  void setServoPos  (byte servo, byte pos  , byte time           );
  void setHeadColor (byte r    , byte g    , byte b   , byte f   );
  bool hasHeadLight () const { return _hasHeadLight; }
  void actionBreak  ();

private:
  byte communicate(byte pos) const;

  static void sendByte(byte pin, byte data);
  static byte recvByte(byte pin           );

  // state
  byte _currentValue[4];
  byte _startValue  [4];
  byte _endValue    [4];

  unsigned int  _duration [4];
  unsigned long _startTime[4];

  byte _data[4];
  byte _type[4];

  bool _hasHeadLight;

  PinSetup _setup;
  byte     _ID   ;

  // latch
  bool          _latchTriggered        ;
  unsigned long _latchDebounceStartTime;
};

#endif

