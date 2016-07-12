#include "pin.h"
#include "meccanoid.h"
#include <Bridge.h>
#include "bridgeController.h"

int previousTime = 0;

void setup()
{
  // startup serial console
  Serial.begin(9600);
  while(!Serial) {}
  Serial.println("Serial Ready.");

  // the bridge controller will listen for input from the yun
  BridgeController.start();
  Serial.println("Waiting for input...");
}

void loop()
{
  delay(1);

  // the bridgecontroller will forward output
  // from the yun script to the serial console
  BridgeController.update();

  // update the meccanoid if needed
  Meccanoid.update();

  int updateDuration = millis() - previousTime;
  //if(updateDuration > 100) 
  //Serial.println("update needed " + String(updateDuration) + "Ms");
  previousTime = millis();
}
