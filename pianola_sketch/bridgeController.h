// bridgeController.h

#ifndef _BRIDGECONTROLLER_h
#define _BRIDGECONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define COUNT_SIZE 16
#define MESSAGE_SIZE 128

class BridgeControllerClass
{
public:
  BridgeControllerClass();

  void start();
  bool peek();
  String getMessage();

private:
  char count[COUNT_SIZE];
  int  previousCount;
  char message[MESSAGE_SIZE];
  bool firstRun;
};

extern BridgeControllerClass BridgeController;

#endif

