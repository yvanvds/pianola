#pragma once
#include "Servo.h"
#include "bodyPart.h"
#include "../Shared/Messages.h"

using namespace Windows::Devices::I2c;
using namespace Platform;
using namespace Windows::UI::Xaml;

namespace Meccanoid {

  ref class AdaHat sealed
  {
  internal:
    AdaHat();

    void init();
    void reset();

    void setRotate(BODYPART part, byte x, byte y, float speed);
    void setRelRotate(BODYPART part, byte x, byte y, float speed);
    void setBrown(BODYPART part, int factor, float speed);
    void setConstraintMultiplier(BODYPART part, float value);
    void setConstraints(BODYPART part, byte minX, byte minY, byte maxX, byte maxY);
    void setLimits(BODYPART part, byte minX, byte minY, byte maxX, byte maxY);
    void setServo(byte ID, byte position, float speed);
    void setPWM(int channel, int on, int off);

  private:
    void setPWMFreq(int freq);
    
    void setAllPWM(int on, int off);

    void SetCycleAsync(int delta);

    concurrency::task<void> startAsync();

    void timerTick(Object^ sender, Object^ e);

    String ^ I2C_CONTROLLER_NAME = "I2C1";
    const byte SERVO_HAT_ADDRESS = 0x40;
    const byte REG_MODE1 = 0x00;
    const byte REG_MODE2 = 0x01;
    const byte REG_LED0_ON_L  = 0x06;
    const byte REG_LED0_ON_H  = 0x07;
    const byte REG_LED0_OFF_L = 0x08;
    const byte REG_LED0_OFF_H = 0x09;
    const byte REG_ALL_ON_L = 0xFA;
    const byte REG_ALL_ON_H = 0xFB;
    const byte REG_ALL_OFF_L = 0xFC;
    const byte REG_ALL_OFF_H = 0xFD;
    const byte PRESCALE = 0xFE;

    I2cDevice ^ servoHat;
    Array<Servo^> ^ servo;
    
    DispatcherTimer^ timer;
    long lastTick;

    BodyPart head, leftArmUpper, rightArmUpper, leftArmLower, rightArmLower, leftHand, rightHand;
    BodyPart leftLegUpper, rightLegUpper, leftLegLower, rightLegLower;

  };


}

