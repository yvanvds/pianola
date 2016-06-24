#include "Network.h"
#include "ext.h"
#include "p_send.h"

#undef post
#include "juce_osc.h"
#include "juce_core.h"

Network N;

Network::Network() : sender(new juce::OSCSender) {
  if (!sender->connect("127.0.0.1", 34567)) {
    object_post(NULL, "Could not connect to port 34567 on localhost");
  }
}

Network::~Network() {
  delete sender;
}

void Network::sendJoint(p_send * obj, int joint, int pos, int duration) {
  juce::String s = PROJECTNAME;
  s += "/";
  s += obj->id0->s_name;
  s += "/";
  s += obj->id1->s_name;
  s += "/joint";

  if(!sender->send(s, joint, pos, duration)) {
    object_post(NULL, "Unable to send OSC message");
  }
}
