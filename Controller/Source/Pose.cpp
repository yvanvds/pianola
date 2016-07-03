/*
  ==============================================================================

    Pose.cpp
    Created: 2 Jul 2016 10:36:57pm
    Author:  yvan

  ==============================================================================
*/

#include "Pose.h"

void Pose::setName(const String & name) {
  this->name = name;
}

const String & Pose::getName() {
  return name;
}

void Pose::addAction(XmlElement * elm) {
  Action * a = actions.add(new Action);
  a->pin = elm->getStringAttribute("pin");
  a->joint = elm->getIntAttribute("joint");
  a->pos = elm->getIntAttribute("pos");
}

bool Pose::sendToRobot(int duration, Meccanoid & robot) {
  for (int i = 0; i < actions.size(); i++) {
    juce::OSCMessage message(OSCAddressPattern("/" + robot.getName() + "/pinMove"));
    message.addInt32(robot.getPin(actions[i]->pin));
    message.addInt32(actions[i]->joint);
    message.addInt32(actions[i]->pos);
    message.addInt32(duration);
    
    robot.send(message);
  }
  return true;
}