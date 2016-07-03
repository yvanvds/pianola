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

Meccanoid::Meccanoid() {
  for (int i = 0; i < 13; i++) {
    pinStatus[i] = false;
  }
}

void Meccanoid::handleMessage(const Array<String> & tokens, const OSCMessage & message) {
  // we already have tested there are 3 tokens or more
  ToLog("message handled on " + name + " with action " + tokens[2]);
  if (tokens[2] == "pinMove") {
    if (tokens.size() < 4) {
      ToLog("Invalid pin message");
    }
    else {
      int pin = getPin(tokens[3]);
      if (pin == -1) {
        ToLog("Invalid pin identifier: " + tokens[3]);
      }
      else {
        // construct pin message
        juce::OSCMessage out(OSCAddressPattern("/" + name + "/pinMove"));
        
        // add pin ID
        out.addInt32(pin);

        // copy arguments (should be joint - position - duration)
        for (int i = 0; i < message.size(); i++) {
          out.addInt32(message[i].getInt32());
        }

        // send message
        send(out);
      }
    }
  }
  else if (tokens[2] == "pinLight") {
    if (tokens.size() < 4) {
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
    }
  }
  else if (tokens[2] == "headLight") {
    juce::OSCMessage out(OSCAddressPattern("/" + name + "/headLight"));
    for (int i = 0; i < message.size(); i++) {
      out.addInt32(message[i].getInt32());
    }
    send(out);
  }
  else if (tokens[2] == "pose") {
    if (message.size() > 1) {
      String pose = message[0].getString();
      int time = message[1].getInt32();

      Poses().sendPoseToRobot(pose, time, *this);
    }
  }
}


bool Meccanoid::getPinStatus(int pin) {
  return pinStatus[pin];
}

Meccanoid & Meccanoid::setPinStatus(int pin, bool status) {
  pinStatus[pin] = status;
  return *this;
}

const String & Meccanoid::getPinName(int pin) {
  return pinName[pin];
}

Meccanoid & Meccanoid::setPinName(int pin, const String & name) {
  pinName[pin] = name;
  return *this;
}

int Meccanoid::getPin(const String & name) {
  for (int i = 0; i < 13; i++) {
    if (pinName[i] == name) return i;
  }
  return -1;
}

void Meccanoid::initialize() {
  int current = 1;
  for (int i = 0; i < 13; i++) {
    if (pinStatus[i]) {
      juce::OSCMessage message("/" + getName() + "/init");
      message.addInt32(current);
      message.addInt32(i);
      send(message);
      current++;
    }
  }

  if (current > 4) {
    ToLog("Warning on " + name + ": only 3 pins are currently supported");
  }
}

