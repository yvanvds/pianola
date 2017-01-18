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
#include "joint.h"
#include "Vector.h"
#include "Utilities.h"

Robot::Robot() {
  socket = nullptr;
  connected = false;
  lastSeen = 60;
  port = 0;
  VecToRot = true;
}

String Robot::getName() {
  return name;
}

String Robot::getIp() {
  return ipAddress;
}

int Robot::getPort() {
	return port;
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

Robot & Robot::setPort(int port) {
	this->port = port;
	return *this;
}

void Robot::assignSocket(DatagramSocket * socket)
{
  this->socket = socket;
}

bool Robot::send(const OSCMessage & message) {
  ToLog(message);
  if(connected) return OSCSender::send(message);
  return false;
}

bool Robot::send(const void * sourceBuffer, int buffersize)
{
  if (socket != nullptr) {
    socket->write(ipAddress, port != 0 ? port : MESSAGE_PORT, sourceBuffer, buffersize);
    return true;
  }
  return false;
}

void Robot::ConvertVecToRotation(Vec & coord, BODYPART part)
{
  joint j;
  j.look(coord);
  coord.x = RadToDeg(j.pitch) / 360 * 255;
  coord.y = RadToDeg(j.roll) / 360 * 255;
  coord.z = RadToDeg(j.yaw) / 360 * 255;
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
