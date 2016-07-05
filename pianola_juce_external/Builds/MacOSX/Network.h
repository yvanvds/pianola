#pragma once


namespace juce {
  class OSCSender;
}

struct p_send;

struct Network {
public:
  Network();
  ~Network();

  void sendJoint     (p_send * obj, int joint, int pos  , int time       );
  void sendServoLight(p_send * obj, int joint, int color                 );
  void sendHeadLight (p_send * obj, int r    , int g    , int b   , int f);
  void sendPose      (p_send * obj, const char * pose   , int time       );

private:
  juce::OSCSender * sender;

};

extern Network N;