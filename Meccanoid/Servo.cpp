#include "pch.h"
#include "Servo.h"
#include "AdaHat.h"
#include "MainPage.xaml.h"

using namespace Concurrency;
using namespace Windows::UI::Core;

Meccanoid::Servo::Servo(int ID, AdaHat ^ hat)
  : ID(ID)
{
  this->hat = hat;
  currentPos.store(0);
  targetPos.store(0);
  hat->setPWM(ID, 0, currentPos);
}

void Meccanoid::Servo::setPos(int target, float speed)
{
  this->targetPos.store(target);
  this->currentSpeed.store(speed * 100);

  SetTargetAsync();
}

void Meccanoid::Servo::SetTargetAsync()
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]() {
    MainPage::Current->SetServoTarget(ID, targetPos.load(), currentSpeed.load());
  }));
}

void Meccanoid::Servo::SetPosAsync(int pos)
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, pos]() {
    MainPage::Current->SetServoPos(ID, pos);
  }));
}

void Meccanoid::Servo::update(float delta)
{
  float cPos   = currentPos  .load();
  int   tPos   = targetPos   .load();
  float cSpeed = currentSpeed.load();


  if ((int)cPos != tPos) {
    if (cPos < tPos) {
      int oldPos = (int)cPos;
      cPos += delta * cSpeed;
      if (cPos > tPos) cPos = tPos;
      if ((int)cPos != oldPos) {
        hat->setPWM(ID, 0, cPos);
        SetPosAsync(cPos);
      }
    }
    else {
      int oldPos = (int)cPos;
      cPos -= delta * cSpeed;
      if (cPos < tPos) cPos = tPos;
      if ((int)cPos != oldPos) {
        hat->setPWM(ID, 0, cPos);
        SetPosAsync(cPos);
      }
    }
  }
  currentPos.store(cPos);
}

