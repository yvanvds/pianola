// 
// 
// 

#include "pin.h"

const unsigned int latchDebounceInterval = 500;

pinClass::pinClass() {
  _setup                  = PS_Unused;
  _latchTriggered         = false    ;
  _latchDebounceStartTime = 0        ;
  _hasHeadLight           = false    ;

  for (byte i = 0; i < 4; i++) {
    _currentValue[i] = 0;
    _startValue  [i] = 0;
    _endValue    [i] = 0;
    _duration    [i] = 0;
    _startTime   [i] = 0;
  }


}

void pinClass::init(byte ID) {
  _ID = ID;

  byte pos     = 0;
  byte timeout = 0;
  byte input        ;
  bool allDiscovered;

  // Is this pin already set up for meccanoid use?
  if (_setup == PS_Meccanoid) return;

  // Send reset
  for (byte i = 0; i < 4; i++) {
    _data[i] = 0xFD;
    communicate(i);
  }

  // Set positions and types as unassigned
  for (byte i = 0; i < 4; i++) {
    _data[i] = 0xFE;
    _type[i] =  255;
  }

  do {
    input = communicate(pos);
    // if 0xFE is received, then the module exists so get its type
    if (input == 0xFE) _data[pos] = 0xFC;

    // if 0x01 is received, the module is a servo, so change its colour to black
    if (input == 0x01 && _type[pos] == 255) {
      _data[pos] = 0xF0;
      _type[pos] =    1;
    }

    // if 0x01 is received, the module is a LED
    if (input == 0x02 && _type[pos] == 255) {
      _data[pos]    = 0x00;
      _type[pos]    =    2;
      _hasHeadLight = true;
    }

    // if 0x00 is received, there is no module at this or higher positions
    if (input == 0x00 && pos > 0) {
      if (_type[pos - 1] != 255) {
        _data[pos] = 0xFE;
        _type[pos] =    0;
      }
    }

    // see if all positions have been discovered
    allDiscovered = true;
    for (byte i = 0; i < 4; i++) {
      if (_type[i] == 255) allDiscovered = false;
    }

    // move to the next position
    pos++;
    if (pos == 4) pos = 0;

    timeout++;
  } while (!allDiscovered && timeout != 0);

  if (timeout == 0) {
    // this pin is now unused
    _setup = PS_Unused;
    Serial.println("Init timeout on pin " + String(_ID));
  }
  else {
    for (byte i = 0; i < 4; i++) {
      if (_type[i] == 1) {
        // set servo led to black
        _data[i] = 0xF0;

        // get servo position
        _currentValue[i] =  getMotorPos (i);
        _endValue    [i] = _currentValue[i];
      }

      if (_type[i] == 2) {
        // set led to black
        _data[i] = 0x00; communicate(i);
        _data[i] = 0x40; communicate(i);
      }
    }

    // this pin is now a meccanoid pin
    _setup = PS_Meccanoid;
    Serial.println("Found meccanoid on pin " + String(_ID));
  }
}

void pinClass::update() {

  if (_setup == PS_Meccanoid) {
    // change servo values
    byte value;
    bool doUpdate = false;

    for (byte i = 0; i < 4; i++) {
      if (_type[i] == 1) {
        // does the current value equal the end value?
        if (_currentValue[i] != _endValue[i]) {
          // calculate new value
          if (millis() - _startTime[i] >= _duration[i]) {
            value = _endValue[i];
          } else {
            value = _startValue[i] + (((float)(millis() - _startTime[i]) / _duration[i]) * (_endValue[i] - _startValue[i]));
          }

          // set servo value, if ther has been a change
          if (value != _currentValue[i]) {
            _currentValue[i] = value;
            _data[i] = value;
            doUpdate = true;
          }
        }
      }
    }

    if (doUpdate) {
      communicate(0);
    }
  }
}

byte pinClass::communicate(byte pos) const {
  unsigned int checkSumI;
  byte checkSumB;
  byte input    ;

  // send header
  sendByte(_ID, 0xFF);

  // send 4 data bytes
  for (byte i = 0; i < 4; i++) {
    sendByte(_ID, _data[i]);
  }

  // calculate checksum
  checkSumI = _data[0] + _data[1] + _data[2] + _data[3];
  checkSumI = checkSumI + (checkSumI >> 8);
  checkSumI = checkSumI + (checkSumI << 4);
  checkSumI = checkSumI & 0xF0;
  checkSumB = checkSumI | pos;

  // send checksum
  sendByte(_ID, checkSumB);

  // receive input
  input = recvByte(_ID);
  delay(10);
  return input;
}

void pinClass::sendByte(byte pin, byte data) {
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

byte pinClass::recvByte(byte pin) {
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

byte pinClass::getMotorPos(byte pos) const {
  // Get the servo position - keep getting returned position until two readings match and are non-zero
  byte returnedValue = 0;
  byte lastReturnedValue = 0;
  do {
    lastReturnedValue = returnedValue;
    returnedValue = communicate(pos);
  } while (returnedValue == 0 || returnedValue != lastReturnedValue);

  return returnedValue;
}

void pinClass::actionBreak() {
  if(_setup == PS_Meccanoid) {
    for (byte i = 0; i < 4; i++) {
      if (_type[i] == 1) {
        // get the servo position
        _currentValue[i] =  getMotorPos (i);
        _endValue    [i] = _currentValue[i];
      }
    }
  }
}

void pinClass::setHeadColor(byte r, byte g, byte b, byte f) {
  byte LED1, LED2, LEDPos;

  // find the led position
  for (byte i = 0; i < 4; i++) {
    if (_type[i] == 2) {
      LEDPos = i; break;
    }
  }

  // Combine Red, Green, Blue and Fade values into two bytes: bytLED1 = 0GGGRRR; bytLED2 = 1FFFBBB
  LED1 = 0x3F & (((g << 3) & 0x38) | (r & 0x07));
  LED2 = 0x40 | (((f << 3) & 0x38) | (b & 0x07));

  // Set the colour
  _data[LEDPos] = LED1; communicate(0);
  _data[LEDPos] = LED2; communicate(0);
}

void pinClass::setServoPos(byte servo, byte pos, byte time) {
  // keep values within range
  if (pos <  24) pos =  24;
  if (pos > 232) pos = 232;

  // Get servo position if currently disabled
  if (_data[servo] == 0xFA) {
    _currentValue[servo] = getMotorPos(servo);
  }

  // store the start value, end value, start time and duration
  _startValue[servo] = _currentValue[servo];
  _endValue  [servo] = pos;
  _startTime [servo] = millis();
  _duration  [servo] = (int)time * 100;
}

void pinClass::setServoColor(byte servo, byte color) {
  if (color > 7) color =   7;
  _data[servo] = color + 240;
  communicate(servo);
}
