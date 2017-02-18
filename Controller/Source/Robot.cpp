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
  bufferSize = 0;
}

String Robot::getName() {
  return name;
}

String Robot::getIp() {
  return ipAddress;
}

int Robot::getPort() {
	return port.get();
}

Robot & Robot::setName(const String & value) {
  name = value;
  return *this;
}

Robot & Robot::setIp(const String & value) {
  const ScopedWriteLock l(lock);
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
    const ScopedReadLock l(lock);
    socket->write(ipAddress, port.get() != 0 ? port.get() : MESSAGE_PORT, sourceBuffer, buffersize);
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

void Robot::update() {
  lastSeen++;
  connected =  (lastSeen < 30);
  bufferSize = messageBuffer.size();
}

void Robot::timerCallback() {
  MemoryOutputStream * out = messageBuffer.getReader();
  if (out != nullptr) {
    send(out->getData(), out->getDataSize());
    messageBuffer.readDone();
  }
}

Robot & Robot::resetLastSeen() {
  lastSeen = 0;
  return *this;
}
