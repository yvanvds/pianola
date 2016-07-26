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

    servo = ref new Array<Servo^>(16);
    for (int i = 0; i < 16; i++) {
      servo[i] = ref new Servo(i, this);
    }

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

  for (int i = 0; i < 16; i++) {
    servo[i]->update(fDelta);
  }
  
}

