/*
  ==============================================================================

    Poses.h
    Created: 2 Jul 2016 10:36:26pm
    Author:  yvan

  ==============================================================================
*/

#ifndef POSES_H_INCLUDED
#define POSES_H_INCLUDED

#include "JuceHeader.h"
#include "Pose.h"
#include "Meccanoid.h"

class poses {
public:
  poses();
  void addPose(XmlElement * content);
  bool sendPoseToRobot(const String & pose, int duration, Meccanoid & robot);

private:
  OwnedArray<Pose> list;
};

poses & Poses();


#endif  // POSES_H_INCLUDED
