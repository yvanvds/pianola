/*
  ==============================================================================

    Robot.cpp
    Created: 7 Jun 2016 7:11:19pm
    Author:  yvan

  ==============================================================================
*/

#include "Robot.h"

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
  return *this;
}