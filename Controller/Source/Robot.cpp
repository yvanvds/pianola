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
#include "MonitorWindow.h"

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
  connected = connect(ipAddress, OSC_PORT);
  return *this;
}

bool Robot::send(const OSCMessage & message) {
  ToLog(message);
  if(connected) return OSCSender::send(message);
  return false;
}

Robot & Robot::update() {
  lastSeen++;
  connected =  (lastSeen < 30);
  return *this;
}

Robot & Robot::resetLastSeen() {
  lastSeen = 0;
  return *this;
}
