/*
  ==============================================================================

    KinectPlayer.h
    Created: 22 Jan 2017 5:09:12pm
    Author:  yvan

  ==============================================================================
*/

#ifndef KINECTPLAYER_H_INCLUDED
#define KINECTPLAYER_H_INCLUDED

#include "Defines.h"
#include <vector>
#include "Recording.h"
#include "Robot.h"

class KinectPlayer : private Timer {
public:
  KinectPlayer();
 ~KinectPlayer();

  void init(); // load all files

  void play(const String recording, float speed, const String output);

  void send(const String & output, BODYPART part, const VecI & rot);

private:
  void timerCallback() override;

  std::vector<Recording> recordings;
  std::vector<ActiveRecording> activeRecordings;
  OSCSender sender;
  ReadWriteLock lock;
};

KinectPlayer & Player();


#endif  // KINECTPLAYER_H_INCLUDED
