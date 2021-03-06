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
  s += "/pinMove/";
  s += obj->id1->s_name;

  if(!sender->send(s, joint, pos, duration)) {
    object_post(NULL, "Unable to send OSC message");
  }
}

void Network::sendServoLight(p_send * obj, int joint, int color) {
  juce::String s = PROJECTNAME;
  s += "/";
  s += obj->id0->s_name;
  s += "/pinLight/";
  s += obj->id1->s_name;

  if (!sender->send(s, joint, color)) {
    object_post(NULL, "Unable to send OSC message");
  }
}

void Network::sendHeadLight(p_send * obj, int r, int g, int b, int f) {
  juce::String s = PROJECTNAME;
  s += "/";
  s += obj->id0->s_name;
  s += "/headLight/";
  s += obj->id1->s_name;

  if (!sender->send(s, r, g, b, f)) {
    object_post(NULL, "Unable to send OSC message");
  }
}

void Network::sendPose(p_send * obj, const char * pose, int time) {
  juce::String s = PROJECTNAME;
  s += "/";
  s += obj->id0->s_name;
  s += "/pose";

  if (!sender->send(s, juce::String(pose), time)) {
    object_post(NULL, "Unable to send OSC message");
  }
}
