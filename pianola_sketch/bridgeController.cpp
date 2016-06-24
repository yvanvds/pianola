// 
// 
// 

#include <Bridge.h>
#include "bridgeController.h"



BridgeControllerClass::BridgeControllerClass()
{
  previousCount = -1;
  memset(count, 0, COUNT_SIZE);
  memset(message, 0, MESSAGE_SIZE);
  firstRun = true;
}

void BridgeControllerClass::start() {
  Bridge.begin();
}

bool BridgeControllerClass::peek() {
  Bridge.get("COUNT", count, COUNT_SIZE);
  int currentCount = atoi(count);
  if(firstRun && currentCount == 0) {
    firstRun = false;
    return true;
  } else if (currentCount > previousCount) {
    previousCount = currentCount;
    return true;
  }
  return false;
}

String BridgeControllerClass::getMessage() {
  Bridge.get("MESSAGE", message, MESSAGE_SIZE);
  return String(message);
}


BridgeControllerClass BridgeController;

