// bridgeMessage.h

#ifndef _BRIDGEMESSAGE_h
#define _BRIDGEMESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define COUNT_SIZE 16
#define MESSAGE_SIZE 64

class bridgeMessage {
public:
  bridgeMessage();
  void setID(byte ID);

  bool peek();
  String getMessage();

private:
  String countID;
  String messageID;

  char count[COUNT_SIZE];
  char message[MESSAGE_SIZE];

  int previousCount;
};


#endif

