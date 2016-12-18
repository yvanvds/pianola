#include "pch.h"
#include "bodyPart.h"
#include "AdaHat.h"

using namespace Concurrency;
using namespace Windows::UI::Core;

void Meccanoid::BodyPart::init(const VecI & ID, AdaHat ^ hat)
{
  EnterCriticalSection(&lock);
  this->ID = ID;
  this->hat = hat;

  hat->setPWM(ID.x, 127, 0);
  hat->setPWM(ID.y, 127, 0);

  iOrn.set({ 128, 128 }, 0);
  iRelative.set({ 0,0 }, 0);
  brownFactor = 0;
  brownSpeed = 0;

  ornMin.x = 127;
  ornMax.x = 127;
  ornMin.y = 127;
  ornMax.y = 127;

  limitMin.x = limitMin.y = limitMax.x = limitMax.y = 127;

  constraintMultiplier = 1;

  ready = true;
  LeaveCriticalSection(&lock);
}

void Meccanoid::BodyPart::setOrn(int x, int y, float time)
{
  x -= 127;  
  if (x < 0) {
    if (x < -limitMin.x) x = -limitMin.x;
    x = (ornMin.x == 0 ? 0 : x / (127.f / ornMin.x) * constraintMultiplier);
  }
  else {
    if (x > limitMax.x) x = limitMax.x;
    x = (ornMax.x == 0 ? 0 : x / (127.f / ornMax.x) * constraintMultiplier);
  }
  x += 127;

  y -= 127;  
  if (y < 0) {
    if (y < -limitMin.y) y = -limitMin.y;
    y = (ornMin.y == 0 ? 0 : y / (127.f / ornMin.y) * constraintMultiplier);
  }
  else {
    if (y > limitMax.y) y = limitMax.y;
    y = (ornMax.y == 0 ? 0 : y / (127.f / ornMax.y) * constraintMultiplier);
  }
  y += 127;

  EnterCriticalSection(&lock);
  iOrn.set({ (float)x,(float)y }, time);
  LeaveCriticalSection(&lock);
}

void Meccanoid::BodyPart::setOrnRelative(int x, int y, float time)
{
  x -= 127;
  y -= 127;
  EnterCriticalSection(&lock);
  iRelative.set({ (float)x,(float)y }, time);
  LeaveCriticalSection(&lock);
}

void Meccanoid::BodyPart::setOrnConstraints(const VecI & min, const VecI & max)
{
  ornMin = min;
  ornMax = max;
}

void Meccanoid::BodyPart::setOrnLimits(const VecI & min, const VecI & max) {
  limitMin = min;
  limitMax = max;
}

void Meccanoid::BodyPart::setConstraintMultiplier(float value)
{
  EnterCriticalSection(&lock);
  constraintMultiplier = value;
  LeaveCriticalSection(&lock);
}

void Meccanoid::BodyPart::setBrown(int factor, float speed)
{
  EnterCriticalSection(&lock);
  brownFactor = factor;
  brownSpeed = speed;

  findBrownTarget();
  LeaveCriticalSection(&lock);
}

void Meccanoid::BodyPart::findBrownTarget()
{
  iBrown.set(
    { 
      RandomF(-brownFactor, brownFactor), 
      RandomF(-brownFactor, brownFactor) 
    }, 
    brownSpeed + RandomF(-brownSpeed * 0.5, brownSpeed * 0.5)
  );
}

void Meccanoid::BodyPart::update(float delta)
{
  EnterCriticalSection(&lock);
  Vec orn = iOrn.update(delta);
  Vec relative = iRelative.update(delta);

  if (iBrown.targetReached()) findBrownTarget();
  Vec brown = iBrown.update(delta);
  LeaveCriticalSection(&lock);

  float x = orn.x + relative.x + brown.x;
  float y = orn.y + relative.y + brown.y;

  x -= 127; y -= 127;
  if (x < -limitMin.x) x = -limitMin.x;
  if (x > limitMax.x) x = limitMax.x;
  if (y < -limitMin.y) y = -limitMin.y;
  if (y > limitMax.y) y = limitMax.y;
  x += 127; y += 127;

  // convert to PWM value
  x = 150 + (x / 256.f * 450);
  y = 150 + (y / 256.f * 450);

  hat->setPWM(ID.x, 0, x);
  hat->setPWM(ID.y, 0, y);
}


