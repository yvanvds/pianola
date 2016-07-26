#pragma once
#include <atomic>

namespace Meccanoid {
  ref class AdaHat;

  ref class Servo sealed
  {
  public:
    Servo(int ID, AdaHat ^ hat);

    void setPos(int target, float speed);

    void update(float delta);

  private:

    void SetTargetAsync(       );
    void SetPosAsync   (int pos);

    int ID;
    AdaHat ^ hat;
    std::atomic<float> currentPos  ;
    std::atomic<int  > targetPos   ;
    std::atomic<float> currentSpeed;
  };

}

