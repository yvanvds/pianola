// bridgeController.h

#ifndef _BRIDGECONTROLLER_h
#define _BRIDGECONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Bridge.h>

#define MESSAGE "M"

enum MESSAGEBYTE : byte {
  MB_CHANGE, // content has changed 
  MB_PIN_ID1, // ID of first pin (will be initialized if needed)
  MB_ID1_SERVO0_POS, // desired position of first servo [24 - 232]
  MB_ID1_SERVO0_TIME, // desired time to reach position in millis / 100 [0 - 255]
  MB_ID1_SERVO0_LIGHT, // light color of this servo [0-7]
  MB_ID1_SERVO1_POS, // same for other servo's
  MB_ID1_SERVO1_TIME,
  MB_ID1_SERVO1_LIGHT,
  MB_ID1_SERVO2_POS,
  MB_ID1_SERVO2_TIME,
  MB_ID1_SERVO2_LIGHT,
  MB_PIN_ID2, // same for other pins
  MB_ID2_SERVO0_POS,
  MB_ID2_SERVO0_TIME,
  MB_ID2_SERVO0_LIGHT,
  MB_ID2_SERVO1_POS,
  MB_ID2_SERVO1_TIME,
  MB_ID2_SERVO1_LIGHT,
  MB_ID2_SERVO2_POS,
  MB_ID2_SERVO2_TIME,
  MB_ID2_SERVO2_LIGHT,
  MB_PIN_ID3,
  MB_ID3_SERVO0_POS,
  MB_ID3_SERVO0_TIME,
  MB_ID3_SERVO0_LIGHT,
  MB_ID3_SERVO1_POS,
  MB_ID3_SERVO1_TIME,
  MB_ID3_SERVO1_LIGHT,
  MB_ID3_SERVO2_POS,
  MB_ID3_SERVO2_TIME,
  MB_ID3_SERVO2_LIGHT,
  MB_LIGHT_R, // red color byte for head light
  MB_LIGHT_G, // green
  MB_LIGHT_B, // blue
  MB_LIGHT_F, // alpha / intensity
  MB_NUM, // total number of bytes in a message
};

class BridgeControllerClass
{
public:
  BridgeControllerClass();

  void start ();
  void update();

private:
  Process p;
  
  char newMessages[MB_NUM];
  char oldMessages[MB_NUM];
};

extern BridgeControllerClass BridgeController;

#endif

