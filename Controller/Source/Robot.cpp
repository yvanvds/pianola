/*
  ==============================================================================

    Robot.cpp
    Created: 7 Jun 2016 7:11:19pm
    Author:  yvan

  ==============================================================================
*/

#include "Robot.h"
#include "Defines.h"
#include "JuceHeader.h"

Robot::Robot() {
  connected = false;
  lastSeen = 60;
}

String Robot::getName() {
  return name;
}

String Robot::getIp() {
  return ipAddress;
}

Robot & Robot::setName(const String & value) {
  name = value;
  return *this;
}

Robot & Robot::setIp(const String & value) {
  ipAddress = value;
  disconnect();
  connect(ipAddress, OSC_PORT);
  return *this;
}

bool Robot::send(const OSCMessage & message) {
  return OSCSender::send(message);
}

Robot & Robot::update() {
  lastSeen++;
  return *this;
}

Robot & Robot::resetLastSeen() {
  lastSeen = 0;
  return *this;
}
