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

void Meccanoid::handleMessage(const OSCMessage & message) {
  String partial = message.getAddressPattern().toString().fromFirstOccurrenceOf(name + "/", false, true);
  String action = partial.upToFirstOccurrenceOf("/", false, true);

  if (action.compareIgnoreCase("behaviour") == 0) {
    // Handle behaviours here
  }
  else {
    // direct instruction
    ToLog("message handled on " + name + "with action " + action);
  }
}