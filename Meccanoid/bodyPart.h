#pragma once
#include "MyMath.h"
#include "Interpolator.h"

namespace Meccanoid {
  ref class AdaHat;

  ref class BodyPart sealed {
  public:
    BodyPart() : ready(false) { InitializeCriticalSectionEx(&lock, 10, 0); }
   virtual ~BodyPart() { DeleteCriticalSection(&lock); }

  internal:
    void init(const VecI & ID, AdaHat ^ hat);
    void setOrn(int x, int y, float time);
    void setOrnRelative(int x, int y, float time);
    void setOrnConstraints(const VecI & min, const VecI & max);
    void setOrnLimits(const VecI & min, const VecI & max);
    void setConstraintMultiplier(float value);

    void setBrown(int factor, float speed);
    void findBrownTarget();

    void update(float delta);
  private:
    bool ready;
    VecI ID;

    CRITICAL_SECTION lock;

    // orientation
    Interpolator<Vec> iOrn;
    Interpolator<Vec> iRelative;
    VecI ornMin, ornMax; // constraints
    VecI limitMin, limitMax; // hardware limitss
    float constraintMultiplier;

    // brown values
    float brownFactor;
    float brownSpeed;
    Interpolator<Vec> iBrown;

    AdaHat ^ hat;
  };

}

