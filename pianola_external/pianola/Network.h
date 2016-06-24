#pragma once


namespace juce {
  class OSCSender;
}

struct p_send;

struct Network {
public:
  Network();
  ~Network();

  void sendJoint(p_send * obj, int joint, int pos, int duration);

private:
  juce::OSCSender * sender;

};

extern Network N;