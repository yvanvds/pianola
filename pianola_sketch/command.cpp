#include "command.h"
#include "bridgeController.h"
#include "meccanoid.h"


void CommandClass::update()
{
  message = BridgeController.getMessage();
  int command = get(0).toInt();

  switch (command) {
  case CSetMotorPos     : Meccanoid.setMotorPos  (get(1).toInt()); break;
  case CSetServoLedColor: Meccanoid.setServoColor(get(1).toInt()); break;
  case CSetLedColor     : Meccanoid.setLedColor  (get(1).toInt()); break;
  case CGetMotorPos: 

    break;

  case CDisableServo:

    break;

  case CMotorStep:

    break;

  case CMotorDisable:

    break;

  case CAnalogRead:

    break;

  case CAnalogWrite:

    break;

  case CDigitalRead:

    break;

  case CDigitalWrite:

    break;

  case CAcknowledge:

    break;

  case CAnalogPinMode:

    break;

  case CDigitalPinMode:

    break;

  case CInitialise: Meccanoid.init       (get(1).toInt()); break;
  case CVersion   :                                        break;
  case CBreak     : Meccanoid.actionBreak(              ); break;
  }
}

String CommandClass::get(byte index) {
  byte found = 0;
  int idx[] = {0, -1};
  byte max = message.length() - 1;

  for(byte i = 0; i <= max && found <= index; i++) {
    if(message.charAt(i) == ' ' || i == max) {
      found++;
      idx[0] = idx[1] + 1;
      idx[1] = (i == max) ? i + 1 : i;
    }
  }
  return found > index ? message.substring(idx[0], idx[1]) : "none";
}

void CommandClass::print() {
  for (int i = 0; i < 6; i++) {
    Serial.println(String("part ") + String(i) + String(": ") + get(i));
  }
}


CommandClass Command;

