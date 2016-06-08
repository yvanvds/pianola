#include "Network.h"
#include "ext.h"
#include "p_send.h"

#undef post
#include "juce_osc.h"

Network N;

Network::Network() : sender(new juce::OSCSender) {
  if (!sender->connect("127.0.0.1", 34567)) {
    object_post(NULL, "Could not connect to port 34567 on localhost");
  }
}

Network::~Network() {
  delete sender;
}

void Network::sendTest() {
  if (!sender->send("/pianola/test", 32.f)) {
    object_post(NULL, "Unable to send OSC test message");
  }
  else {
    object_post(NULL, "Test Message sent. (/pianola/test)");
  }
}

void Network::send(p_send * obj, int i) {
  juce::String s = PROJECTNAME;
  s += "/" + toString(obj->id) + "/" + toString(obj->action);
  if (!sender->send(s, i)) {
    object_post(NULL, "Unable to send OSC int message");
  }
}

void Network::send(p_send * obj, float f) {
  juce::String s = PROJECTNAME;
  s += "/" + toString(obj->id) + "/" + toString(obj->action);
  if (!sender->send(s, f)) {
    object_post(NULL, "Unable to send OSC float message");
  }
}

