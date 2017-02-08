#include "pch.h"
#include "AdaHat.h"
#include "MainPage.xaml.h"
#include <math.h>

using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::I2c;
using namespace Concurrency;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;

Meccanoid::AdaHat::AdaHat()
  : servo(nullptr)
{
}

void Meccanoid::AdaHat::init()
{
  lastTick = GetTickCount64();
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]() {
    startAsync();
  }));
  
}

void Meccanoid::AdaHat::reset() {
  for (int i = 0; i < (int)BODYPART::INVALID; i++) {
    switch ((BODYPART)i) {
    case BODYPART::ARMLU: setRotate((BODYPART)i, 127, 182, 0); break;
    case BODYPART::ARMRU: setRotate((BODYPART)i, 127, 182, 0); break;
    default: setRotate((BODYPART)i, 127, 127, 0); break;
    }
    
    setRelRotate((BODYPART)i, 127, 127, 0);
    setBrown((BODYPART)i, 0, 0);
    setConstraintMultiplier((BODYPART)i, 1.f);
  }
}

void Meccanoid::AdaHat::setRotate(BODYPART part, byte x, byte y, float speed)
{
  switch (part) {
    case BODYPART::HEAD: head.setOrn(x, y, speed); break;
    case BODYPART::ARMLU: leftArmUpper.setOrn(x, y, speed); break;
    case BODYPART::ARMLL: leftArmLower.setOrn(x, y, speed); break;
    case BODYPART::ARMRU: rightArmUpper.setOrn(x, y, speed); break;
    case BODYPART::ARMRL: rightArmLower.setOrn(x, y, speed); break;
    case BODYPART::HANDL: leftHand.setOrn(x, y, speed); break;
    case BODYPART::HANDR: rightHand.setOrn(x, y, speed); break;
    case BODYPART::LEGLU: leftLegUpper.setOrn(x, y, speed); break;
    case BODYPART::LEGLL: leftLegLower.setOrn(x, y, speed); break;
    case BODYPART::LEGRU: rightLegUpper.setOrn(x, y, speed); break;
    case BODYPART::LEGRL: rightLegLower.setOrn(x, y, speed); break;
  }
}

void Meccanoid::AdaHat::setRelRotate(BODYPART part, byte x, byte y, float speed)
{
  switch (part) {
  case BODYPART::HEAD: head.setOrnRelative(x, y, speed); break;
  case BODYPART::ARMLU: leftArmUpper.setOrnRelative(x, y, speed); break;
  case BODYPART::ARMLL: leftArmLower.setOrnRelative(x, y, speed); break;
  case BODYPART::ARMRU: rightArmUpper.setOrnRelative(x, y, speed); break;
  case BODYPART::ARMRL: rightArmLower.setOrnRelative(x, y, speed); break;
  case BODYPART::HANDL: leftHand.setOrnRelative(x, y, speed); break;
  case BODYPART::HANDR: rightHand.setOrnRelative(x, y, speed); break;
  case BODYPART::LEGLU: leftLegUpper.setOrnRelative(x, y, speed); break;
  case BODYPART::LEGLL: leftLegLower.setOrnRelative(x, y, speed); break;
  case BODYPART::LEGRU: rightLegUpper.setOrnRelative(x, y, speed); break;
  case BODYPART::LEGRL: rightLegLower.setOrnRelative(x, y, speed); break;
  }
}

void Meccanoid::AdaHat::setBrown(BODYPART part, int factor, float speed)
{
  switch (part) {
    case BODYPART::HEAD: head.setBrown(factor, speed); break;
    case BODYPART::ARMLU: leftArmUpper.setBrown(factor, speed); break;
    case BODYPART::ARMLL: leftArmLower.setBrown(factor, speed); break;
    case BODYPART::ARMRU: rightArmUpper.setBrown(factor, speed); break;
    case BODYPART::ARMRL: rightArmLower.setBrown(factor, speed); break;
    case BODYPART::HANDL: leftHand.setBrown(factor, speed); break;
    case BODYPART::HANDR: rightHand    .setBrown(factor, speed); break;
    case BODYPART::LEGLU: leftLegUpper .setBrown(factor, speed); break;
    case BODYPART::LEGLL: leftLegLower .setBrown(factor, speed); break;
    case BODYPART::LEGRU: rightLegUpper.setBrown(factor, speed); break;
    case BODYPART::LEGRL: rightLegLower.setBrown(factor, speed); break;
  }
}

void Meccanoid::AdaHat::setConstraintMultiplier(BODYPART part, float value)
{
  switch (part) {
    case BODYPART::HEAD: head.setConstraintMultiplier(value); break;
    case BODYPART::ARMLU: leftArmUpper.setConstraintMultiplier(value); break;
    case BODYPART::ARMLL: leftArmLower.setConstraintMultiplier(value); break;
    case BODYPART::ARMRU: rightArmUpper.setConstraintMultiplier(value); break;
    case BODYPART::ARMRL: rightArmLower.setConstraintMultiplier(value); break;
    case BODYPART::HANDL: leftHand.setConstraintMultiplier(value); break;
    case BODYPART::HANDR: rightHand.setConstraintMultiplier(value); break;
    case BODYPART::LEGLU: leftLegUpper.setConstraintMultiplier(value); break;
    case BODYPART::LEGLL: leftLegLower.setConstraintMultiplier(value); break;
    case BODYPART::LEGRU: rightLegUpper.setConstraintMultiplier(value); break;
    case BODYPART::LEGRL: rightLegLower.setConstraintMultiplier(value); break;
  }
}

void Meccanoid::AdaHat::setConstraints(BODYPART part, byte minX, byte minY, byte maxX, byte maxY)
{
  switch (part) {
    case BODYPART::HEAD: head.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMLU: leftArmUpper.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMLL: leftArmLower.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMRU: rightArmUpper.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMRL: rightArmLower.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::HANDL: leftHand.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::HANDR: rightHand.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGLU: leftLegUpper .setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGLL: leftLegLower .setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGRU: rightLegUpper.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGRL: rightLegLower.setOrnConstraints({ minX, minY }, { maxX, maxY }); break;
  }
}

void Meccanoid::AdaHat::setLimits(BODYPART part, byte minX, byte minY, byte maxX, byte maxY)
{
  switch (part) {
    case BODYPART::HEAD: head.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMLU: leftArmUpper.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMLL: leftArmLower.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMRU: rightArmUpper.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::ARMRL: rightArmLower.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::HANDL: leftHand.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::HANDR: rightHand.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGLU: leftLegUpper.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGLL: leftLegLower.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGRU: rightLegUpper.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
    case BODYPART::LEGRL: rightLegLower.setOrnLimits({ minX, minY }, { maxX, maxY }); break;
  }
}

void Meccanoid::AdaHat::setOffset(BODYPART part, int x, int y)
{
  switch (part) {
    case BODYPART::HEAD: head.setOffset(x, y); break;
    case BODYPART::ARMLU: leftArmUpper.setOffset(x, y); break;
    case BODYPART::ARMLL: leftArmLower.setOffset(x, y); break;
    case BODYPART::ARMRU: rightArmUpper.setOffset(x, y); break;
    case BODYPART::ARMRL: rightArmLower.setOffset(x, y); break;
    case BODYPART::HANDL: leftHand.setOffset(x, y); break;
    case BODYPART::HANDR: rightHand.setOffset(x, y); break;
    case BODYPART::LEGLU: leftLegUpper.setOffset(x, y); break;
    case BODYPART::LEGLL: leftLegLower.setOffset(x, y); break;
    case BODYPART::LEGRU: rightLegUpper.setOffset(x, y); break;
    case BODYPART::LEGRL: rightLegLower.setOffset(x, y); break;
  }
}

void Meccanoid::AdaHat::setServo(byte ID, byte position, float speed)
{
  int pos = position;
  pos = 150 + (pos / 256.f * 450);
  if (servo != nullptr && ID >= 0 && ID < 16) {
    servo[ID]->setPos(pos, speed);
  }
}

void Meccanoid::AdaHat::setPWMFreq(int freq)
{
  double preScale = 25000000.0;
  preScale /= 4096;
  preScale /= (float)freq;
  preScale -= 1.0;

  preScale = floor(preScale + .5);

  auto command = ref new Array<byte>(1);
  auto buffer = ref new Array<byte>(2);

  command[0] = REG_MODE1;
  
  auto result = servoHat->ReadPartial(command);
  auto action = (byte)((result.BytesTransferred & 0x7F) | 0x10);

  buffer[0] = REG_MODE1; buffer[1] = (byte) action                         ; servoHat->Write(buffer);
  buffer[0] = PRESCALE ; buffer[1] = (byte) preScale                       ; servoHat->Write(buffer);
  buffer[0] = REG_MODE1; buffer[1] = (byte) result.BytesTransferred        ; servoHat->Write(buffer);
  buffer[0] = REG_MODE1; buffer[1] = (byte)(result.BytesTransferred | 0x80); servoHat->Write(buffer);
}

void Meccanoid::AdaHat::setPWM(int channel, int on, int off) {
  if (channel < 0) return;

  auto b = ref new Array<byte>(2);
  b[0] = (byte)(REG_LED0_ON_L  + (4 * channel)); b[1] = (byte(on   & 0xFF)); servoHat->Write(b);
  b[0] = (byte)(REG_LED0_ON_H  + (4 * channel)); b[1] = (byte(on  >>    8)); servoHat->Write(b);
  b[0] = (byte)(REG_LED0_OFF_L + (4 * channel)); b[1] = (byte(off  & 0xFF)); servoHat->Write(b);
  b[0] = (byte)(REG_LED0_OFF_H + (4 * channel)); b[1] = (byte(off >>    8)); servoHat->Write(b);
}


void Meccanoid::AdaHat::setAllPWM(int on, int off) {
  auto b = ref new Array<byte>(2);
  b[0] = REG_ALL_ON_L ; b[1] = (byte(on   & 0xFF)); servoHat->Write(b);
  b[0] = REG_ALL_ON_H ; b[1] = (byte(on  >>    8)); servoHat->Write(b);
  b[0] = REG_ALL_OFF_L; b[1] = (byte(off  & 0xFF)); servoHat->Write(b);
  b[0] = REG_ALL_OFF_H; b[1] = (byte(off >>    8)); servoHat->Write(b);
}

void Meccanoid::AdaHat::SetCycleAsync(int delta)
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, delta]() {
    MainPage::Current->SetCycle(delta);
  }));
}

concurrency::task<void> Meccanoid::AdaHat::startAsync()
{
  String ^ deviceSelector = I2cDevice::GetDeviceSelector(I2C_CONTROLLER_NAME);
  return create_task(DeviceInformation::FindAllAsync(deviceSelector))
    .then([this](DeviceInformationCollection ^ devices) {

    auto settings = ref new I2cConnectionSettings(SERVO_HAT_ADDRESS);
    settings->BusSpeed = I2cBusSpeed::FastMode;

    return I2cDevice::FromIdAsync(devices->GetAt(0)->Id, settings);
  }).then([this](I2cDevice ^ hat) {
    servoHat = hat;
    setPWMFreq(60);

    head         .init({  0, 1 }, this); // head is on pins 0 and 1
    leftArmUpper .init({  2, 3 }, this);
    rightArmUpper.init({  4, 5 }, this);
    leftArmLower .init({  6,-1 }, this);
    rightArmLower.init({  7,-1 }, this);
    leftHand     .init({ -1,-1 }, this);
    rightHand    .init({ -1,-1 }, this);
    leftLegUpper .init({  8, 9 }, this);
    rightLegUpper.init({ 10,11 }, this);
    leftLegLower .init({ 12,-1 }, this);
    rightLegLower.init({ 13,-1 }, this);

    timer = ref new DispatcherTimer();
    timer->Interval = TimeSpan{ 20 * 1000 * 10 }; // 20ms
    timer->Tick += ref new EventHandler<Object^>(this, &Meccanoid::AdaHat::timerTick);
    timer->Start();
  });
}

void Meccanoid::AdaHat::timerTick(Object ^ sender, Object ^ e)
{
  long tick = GetTickCount64();
  int delta = tick - lastTick;
  lastTick = tick;
  SetCycleAsync(delta);
  float fDelta = delta / 1000.f;

  head         .update(fDelta);
  leftArmUpper .update(fDelta);
  rightArmUpper.update(fDelta);
  leftArmLower .update(fDelta);
  rightArmLower.update(fDelta);
  leftHand     .update(fDelta);
  rightHand    .update(fDelta);
  leftLegUpper .update(fDelta);
  rightLegUpper.update(fDelta);
  leftLegLower .update(fDelta);
  rightLegLower.update(fDelta);
}

