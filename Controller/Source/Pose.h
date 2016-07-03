/*
  ==============================================================================

    Pose.h
    Created: 2 Jul 2016 10:36:57pm
    Author:  yvan

  ==============================================================================
*/

#ifndef POSE_H_INCLUDED
#define POSE_H_INCLUDED

#include "JuceHeader.h"
#include "Meccanoid.h"

class Pose {
public:
  void           setName(const String & name);
  const String & getName();

  void addAction(XmlElement * elm);
  bool sendToRobot(int duration, Meccanoid & robot);

private:
  String name;
  
  struct Action {
    String pin;
    int joint;
    int pos;
  };

  OwnedArray<Action> actions;
};



#endif  // POSE_H_INCLUDED
