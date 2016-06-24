// 
// 
// 

#include "pin.h"
#include "command.h"

const unsigned int latchDebounceInterval = 500;

pinClass::pinClass() {
  setup                  = PS_Input;
  latchTriggered         = false   ;
  latchDebounceStartTime = 0       ;
}

bool pinClass::update() {
  switch (setup) {
  case PS_InputLatchingHigh: 
    // check input for high latch trigger
    if (analogRead(ID) > 255 && millis() - latchDebounceStartTime > latchDebounceInterval) {
      latchTriggered = true;
      latchDebounceStartTime = millis();
    }
    return true;

  case PS_InputLatchingLow:
    // check input for low latch trigger
    if (analogRead(ID) < 256 && millis() - latchDebounceStartTime > latchDebounceInterval) {
      latchTriggered = true;
      latchDebounceStartTime = millis();
    }
    return true;
  }

  // if this is a digital pin, other cases will be handled in the derived class
  return false;
}

digitalPinClass::digitalPinClass() {
  setup = PS_Unused;

  for (byte i = 0; i < 4; i++) {
    currentValue[i] = 0;
    startValue  [i] = 0;
    endValue    [i] = 0;
    duration    [i] = 0;
    startTime   [i] = 0;
  }
}

void digitalPinClass::init() {
  byte input;
  byte pos = 0;
  byte timeout = 0;
  bool allDiscovered;

  // Is htis pin already set up for meccanoid use?
  if (setup == PS_Meccanoid) {
    return;
  }

  Serial.println("init started");
  // Send reset
  for (byte i = 0; i < 4; i++) {
    data[i] = 0xFD;
    communicate(i);
  }

  // Set positions and types as unassigned
  for (byte i = 0; i < 4; i++) {
    data[i] = 0xFE;
    type[i] = 255;
  }

  do {
    Serial.println("init pos: " + String(pos));
    input = communicate(pos);
    Serial.print("input result: ");
    Serial.println(input, HEX);
    // if 0xFE is received, then the module exists so get its type
    if (input == 0xFE) {
      Serial.println("test 1");
      data[pos] = 0xFC;
    }

    // if 0x01 is received, the module is a servo, so change its colour to black
    if (input == 0x01 && type[pos] == 255) {
      Serial.println("test 2");
      data[pos] = 0xF0;
      type[pos] = 1;
    }

    // if 0x01 is received, the module is a LED
    if (input == 0x02 && type[pos] == 255) {
      Serial.println("test 3");
      data[pos] = 0x00;
      type[pos] = 2;
    }

    // if 0x00 is received, there is no module at this or higher positions
    if (input == 0x00 && pos > 0) {
      Serial.println("test 4");
      if (type[pos - 1] != 255) {
        data[pos] = 0xFE;
        type[pos] = 0;
      }
    }

    // see if all positions have been discovered
    allDiscovered = true;
    for (byte i = 0; i < 4; i++) {
      if (type[i] == 255) allDiscovered = false;
    }

    // move to the next position
    pos++;
    if (pos == 4) pos = 0;

    timeout++;
    Serial.println("pos: " + String(pos) + " timeout: " + String(timeout));
  } while (!allDiscovered && timeout != 0);

  if (timeout == 0) {
    // this pin is now unused
    setup = PS_Unused;
    Serial.println("Init timeout on pin " + String(ID));
  }
  else {
    for (byte i = 0; i < 4; i++) {
      if (type[i] == 1) {
        // set servo led to black
        data[i] = 0xF0;

        // get servo position
        currentValue[i] = getMotorPos (i);
        endValue    [i] = currentValue[i];
      }

      if (type[i] == 2) {
        // set led to black
        data[i] = 0x00; communicate(i);
        data[i] = 0x40; communicate(i);
      }
    }

    // this pin is now a meccanoid pin
    setup = PS_Meccanoid;
    Serial.println("Found meccanoid on pin " + String(ID));
  }
}

void digitalPinClass::update() {
  // if super update handled current status, just return
  if (pinClass::update()) return;

  // otherwise handle status
  switch (setup) {
  case PS_OutputPWM:
    // does the current value equal the end value?
    if (currentValue[0] != endValue[0]) {
      // calculate new value
      if (millis() - startTime[0] >= duration[0]) {
        currentValue[0] = endValue[0];
      } else {
        currentValue[0] = startValue[0] + (((float)(millis() - startTime[0]) / duration[0]) * (endValue[0] - startValue[0]));
      }
    }
    // set PWM output
    analogWrite(ID, currentValue[0]);
    break;

  case PS_Meccanoid:
    // change servo values
    byte value;
    bool doUpdate = false;

    for (byte i = 0; i < 4; i++) {
      if (type[i] == 1) {
        // does the current value equal the end value?
        if (currentValue[i] != endValue[i]) {
          // calculate new value
          if (millis() - startTime[i] >= duration[i]) {
            value = endValue[i];
          } else {
            value = startValue[i] + (((float)(millis() - startTime[i]) / duration[i]) * (endValue[i] - startValue[i]));
          }

          // set servo value, if ther has been a change
          if (value != currentValue[i]) {
            currentValue[i] = value;
            data[i] = value;
            doUpdate = true;
          }
        }
      }
    }

    if (doUpdate) {
      communicate(0);
    }
    break;
  }
}

byte digitalPinClass::communicate(byte pos) {
  unsigned int checkSumI;
  byte checkSumB;
  byte input;

  // send header
  sendByte(ID, 0xFF);

  // send 4 data bytes
  for (byte i = 0; i < 4; i++) {
    sendByte(ID, data[i]);
  }

  // calculate checksum
  checkSumI = data[0] + data[1] + data[2] + data[3];
  checkSumI = checkSumI + (checkSumI >> 8);
  checkSumI = checkSumI + (checkSumI << 4);
  checkSumI = checkSumI & 0xF0;
  checkSumB = checkSumI | pos;

  // send checksum
  sendByte(ID, checkSumB);

  // receive input
  input = recvByte(ID);
  delay(10);
  return input;
}

void digitalPinClass::sendByte(byte pin, byte data) {
  const unsigned int delay = 417;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW); delayMicroseconds(delay);   // Start bit - 417us LOW

  for (byte mask = 00000001; mask > 0; mask <<= 1) {  // Iterate through bit mask
    if (data & mask) {                                // If bitwise AND resolves to true
      digitalWrite(pin, HIGH);                        // Send 1
    }
    else {                                            // If bitwise AND resolves to false
      digitalWrite(pin, LOW);                         // Send 0
    }
    delayMicroseconds(delay);                         // Delay
  }

  digitalWrite(pin, HIGH); delayMicroseconds(delay);  // Stop bit - 417us HIGH
  digitalWrite(pin, HIGH); delayMicroseconds(delay);  // Stop bit - 417us HIGH
}

byte digitalPinClass::recvByte(byte pin) {
  byte temp = 0;

  pinMode(pin, INPUT); delay(1.5);

  // Iterate through bit mask
  for (byte mask = 00000001; mask > 0; mask <<= 1) {
    if (pulseIn(pin, HIGH, 2500) > 400) {
      temp |= mask;
    }
  }

  return temp;
}

byte digitalPinClass::getMotorPos(byte pos) {
  // Get the servo position - keep getting returned position until two readings match and are non-zero
  byte returnedValue = 0;
  byte lastReturnedValue = 0;
  do {
    lastReturnedValue = returnedValue;
    returnedValue = communicate(pos);
  } while (returnedValue == 0 || returnedValue != lastReturnedValue);

  return returnedValue;
}

void digitalPinClass::actionBreak() {
  switch (setup) {
  case PS_OutputPWM: 
    endValue[0] = currentValue[0]; 
    break;
  
  case PS_Meccanoid:
    for (byte i = 0; i < 4; i++) {
      if (type[i] == 1) {
        // get the servo position
        currentValue[i] = getMotorPos(i);
        endValue[i] = currentValue[i];
      }
    }
    break;
  }
}

void digitalPinClass::setLedColor() {
  int r = Command.get(2).toInt();
  int g = Command.get(3).toInt();
  int b = Command.get(4).toInt();
  int f = Command.get(5).toInt();

  byte LED1, LED2, LEDPos;

  // find the led position
  for (byte i = 0; i < 4; i++) {
    if (type[i] == 2) {
      LEDPos = i; break;
    }
  }

  // Combine Red, Green, Blue and Fade values into two bytes: bytLED1 = 0GGGRRR; bytLED2 = 1FFFBBB
  LED1 = 0x3F & (((g << 3) & 0x38) | (r & 0x07));
  LED2 = 0x40 | (((f << 3) & 0x38) | (b & 0x07));

  // Set the colour
  data[LEDPos] = LED1; communicate(0);
  data[LEDPos] = LED2; communicate(0);
}

void digitalPinClass::setMotorPos() {
  byte servo = Command.get(2).toInt();
  byte pos   = Command.get(3).toInt();

  // keep values within range
  if (pos <  24) pos =  24;
  if (pos > 232) pos = 232;

  // Get servo position if currently disabled
  if (data[servo] == 0xFA) {
    currentValue[servo] = getMotorPos(servo);
  }

  // store the start value, end value, start time and duration
  startValue[servo] = currentValue[servo];
  endValue  [servo] = pos;
  startTime [servo] = millis();
  duration  [servo] = Command.get(4).toInt();
}

void digitalPinClass::setServoColor() {
  byte servo = Command.get(2).toInt();
  byte color = Command.get(3).toInt();
  if (color > 7) color = 7;

  data[servo] = color + 240;
  communicate(servo);
}
