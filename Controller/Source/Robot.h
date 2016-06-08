/*
  ==============================================================================

    Robot.h
    Created: 7 Jun 2016 7:11:19pm
    Author:  yvan

  ==============================================================================
*/

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "JuceHeader.h"

class Robot {
public:
  String getName(); Robot & setName(const String & value);
  String getIp  (); Robot & setIp  (const String & value);

  virtual void handleMessage(const Array<String> & tokens, const OSCMessage & message) = 0;

protected:
  String name;
  String ipAddress;
};



#endif  // ROBOT_H_INCLUDED
