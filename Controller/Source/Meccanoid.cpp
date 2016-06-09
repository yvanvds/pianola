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

void Meccanoid::handleMessage(const Array<String> & tokens, const OSCMessage & message) {
  // we already have tested there are 3 tokens or more
  ToLog("message handled on " + name + "with action " + tokens[2]);
  if (tokens[2].startsWith("servo")) {
    forwardMessage(message, tokens[2]);
  }
}

void Meccanoid::forwardMessage(const OSCMessage & message, const String & action) {
  OSCMessage out = message;
  out.setAddressPattern("/" + name + "/" + action);
  send(out);
}