/*
  ==============================================================================

    Meccanoid.cpp
    Created: 7 Jun 2016 7:11:29pm
    Author:  yvan

  ==============================================================================
*/

#include "Meccanoid.h"
#include "JuceHeader.h"
#include "Defines.h"
#include "MonitorWindow.h"
#include "Poses.h"
#include "../../Shared/Messages.h"

Meccanoid::Meccanoid() {
  for (int i = 0; i < SERVO_COUNT; i++) {
    servo[i].setID(i);
  }
}

void Meccanoid::handleMessage(const OSCMessage & message) {
  // we already have tested there are 3 tokens or more
  
	if (message[1].getString().compareIgnoreCase("move") == 0) {
    if (message.size() < 4) {
      ToLog("Invalid pin message");
    }
	// todo: test message size (see VirtualBot::handleMessage)
    else {
      // pin move needs 3 bytes and a float
      // message - pin - position - speed

      MemoryOutputStream out;

      out.writeByte((unsigned char) MESSAGE::SERVO);

      // get the base servo according to name
      Servo * s = getServo(message[2].getString());
      if (s == nullptr) {
        ToLog("Invalid servo identifier: " + message[2].getString());
      }
      else {
        // add offset
        s = getServo(s->getID() + message[3].getInt32());
        if (s == nullptr) return;

        out.writeByte((unsigned char)(s->getID()));
        out.writeByte((unsigned char)(s->calculatePos(message[4].getInt32())));
        out.writeFloatBigEndian(message[5].getFloat32());

        send(out.getData(), out.getDataSize());        
      }
    }
  }
  //else if (tokens[2] == "pinLight") {
    /*if (tokens.size() < 4) {
      ToLog("Invalid led message");
    }
    else {
      int pin = getPin(tokens[3]);
      if (pin == -1) {
        ToLog("Invalid pin identifier: " + tokens[3]);
      }
      else {
        juce::OSCMessage out(OSCAddressPattern("/" + name + "/pinLight"));

        // add pin ID
        out.addInt32(pin);

        // copy arguments (should be joint - position - duration)
        for (int i = 0; i < message.size(); i++) {
          out.addInt32(message[i].getInt32());
        }

        // send message
        send(out);
      }
    }*/
  //}
  //else if (tokens[2] == "headLight") {
    /*juce::OSCMessage out(OSCAddressPattern("/" + name + "/headLight"));
    for (int i = 0; i < message.size(); i++) {
      out.addInt32(message[i].getInt32());
    }
    send(out);*/
  //}
  //else if (tokens[2] == "pose") {
  //  if (message.size() > 1) {
  //    String pose = message[0].getString();
  //    int time = message[1].getInt32();

  //    Poses().sendPoseToRobot(pose, time, *this);
  //  }
  //}
}



void Meccanoid::initialize() {
  unsigned char out[1];
  out[0] = (unsigned char) MESSAGE::INIT;
  send(&out, 1);
}

Servo * Meccanoid::getServo(const String & name)
{
  for (int i = 0; i < SERVO_COUNT; i++) {
    if (servo[i].getName().equalsIgnoreCase(name)) {
      return &servo[i];
    }
  }
  return nullptr;
}

Servo * Meccanoid::getServo(unsigned int ID)
{
  if (ID < SERVO_COUNT) {
    return &servo[ID];
  }
  return nullptr;
}

void Meccanoid::resetServos()
{
  for (int i = 0; i < SERVO_COUNT; i++) {
    servo[i].reset();
  }
}



