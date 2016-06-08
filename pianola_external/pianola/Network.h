#pragma once


namespace juce {
  class OSCSender;
}

struct p_send;

struct Network {
public:
  Network();
  ~Network();

  void sendTest();

  void send(p_send * obj, int i);
  void send(p_send * obj, float f);

private:
  juce::OSCSender * sender;

};

extern Network N;