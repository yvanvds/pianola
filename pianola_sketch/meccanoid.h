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
  
  void initIfNeeded(byte pin);
	void update      (        );
  void actionBreak (        ); 
  void setHeadColor (byte r  , byte g    , byte b    , byte f   );
  void setServoPos  (byte pin, byte servo, byte pos  , byte time);
  void setServoColor(byte pin, byte servo, byte color           );

private:
  static const byte _lowestPin  = 2 ;
  static const byte _highestPin = 13;

  pinClass * _pin[_highestPin + 1];
  pinClass * _pinWithHead;
};

extern MeccanoidClass Meccanoid;

#endif

