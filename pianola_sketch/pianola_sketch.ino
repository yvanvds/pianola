
#include "pin.h"
#include "meccanoid.h"
#include <Bridge.h>
#include "bridgeController.h"
#include "command.h"


void setup()
{
  Serial.begin(9600);
  // Wait for serial port
  while(!Serial) {}
  Serial.println("Serial Ready.");
  
  BridgeController.start();
  Serial.println("Bridge Started.");

  Meccanoid.init(2);
  Serial.println("Meccanoid Initialised.");
  Serial.println("Waiting for input.");
}

void loop()
{
  delay(10);
  Meccanoid.update();
  
  if (BridgeController.peek()) {
    Command.update();
    //Command.print();
  }
}
