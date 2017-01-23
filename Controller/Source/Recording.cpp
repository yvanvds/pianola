/*
  ==============================================================================

    Recording.cpp
    Created: 22 Jan 2017 5:08:20pm
    Author:  yvan

  ==============================================================================
*/

#include "Recording.h"
#include "../../Shared/Messages.h"
#include "MonitorWindow.h"
#include "KinectPlayer.h"

bool Recording::load(const File & file)
{
  name = file.getFileNameWithoutExtension();

  ScopedPointer<FileInputStream> source = file.createInputStream();
  if (!source->openedOk()) return false;

  int numFrames = source->readInt();
  
  for(int i = 0; i < numFrames; i++) {
    frames.emplace_back();

    FILEPART part = (FILEPART)source->readInt();
    while (part != FILEPART::END) {

      switch (part) {
      case FILEPART::TIME: {
        int64 time = source->readInt64();
        frames.back().time = time;
        break;
      }

      case FILEPART::JOINTS: {
        loadJoints(source);
        break;
      }
      }

      part = (FILEPART)source->readInt();
    }
  }

  ToLog("Kinect recording " + name + " loaded.");
}

void Recording::loadJoints(ScopedPointer<FileInputStream>& source)
{
  BODYPART part = (BODYPART)source->readInt();
  while (part != BODYPART::INVALID) {

    switch (part) {
      case BODYPART::HEAD: frames.back().head.read(source); break;
      case BODYPART::TORSO_UPPER: frames.back().torsoUpper.read(source); break;
      case BODYPART::TORSO_LOWER: frames.back().torsoLower.read(source); break;
      case BODYPART::ARMLU: frames.back().ArmLU.read(source); break;
      case BODYPART::ARMLL: frames.back().ArmLL.read(source); break;
      case BODYPART::HANDL: frames.back().HandL.read(source); break;
      case BODYPART::ARMRU: frames.back().ArmRU.read(source); break;
      case BODYPART::ARMRL: frames.back().ArmRL.read(source); break;
      case BODYPART::HANDR: frames.back().HandR.read(source); break;
      case BODYPART::LEGLU: frames.back().LegLU.read(source); break;
      case BODYPART::LEGLL: frames.back().LegLL.read(source); break;
      case BODYPART::FOOTL: frames.back().FootL.read(source); break;
      case BODYPART::LEGRU: frames.back().LegRU.read(source); break;
      case BODYPART::LEGRL: frames.back().LegRL.read(source); break;
      case BODYPART::FOOTR: frames.back().FootR.read(source); break;
    }

    part = (BODYPART)source->readInt();
  }
}

bool Recording::equals(const String & name) {
  return this->name.equalsIgnoreCase(name);
}

int Recording::getIndexBefore(int time)
{
  int result = -1;
  for (int i = 0; i < frames.size(); i++) {
    if (frames[i].time > time) {
      result = i - 1;
      break;
    }
    // special case for last frame
    else if (i == frames.size() - 1 && frames[i].time < time) {
      result = i;
    }
  }

  return result;
}

bool Recording::isLastIndex(int value)
{
  return value == (frames.size() - 1);
}

void Recording::sendToBot(int index, const String name)
{
  if (index < 0 || index >= frames.size()) return;
  Frame & f = frames[index];
  Player().send(name, BODYPART::HEAD, f.head);
  Player().send(name, BODYPART::TORSO_UPPER, f.torsoUpper);
  Player().send(name, BODYPART::TORSO_LOWER, f.torsoLower);
  Player().send(name, BODYPART::ARMLU, f.ArmLU);
  Player().send(name, BODYPART::ARMLL, f.ArmLL);
  Player().send(name, BODYPART::HANDL, f.HandL);
  Player().send(name, BODYPART::ARMRU, f.ArmRU);
  Player().send(name, BODYPART::ARMRL, f.ArmRL);
  Player().send(name, BODYPART::HANDR, f.HandR);
  Player().send(name, BODYPART::LEGLU, f.LegLU);
  Player().send(name, BODYPART::LEGLL, f.LegLL);
  Player().send(name, BODYPART::FOOTL, f.FootL);
  Player().send(name, BODYPART::LEGRU, f.LegRU);
  Player().send(name, BODYPART::LEGRL, f.LegRL);
  Player().send(name, BODYPART::FOOTR, f.FootR);
}



void ActiveRecording::set(Recording & recording, const String & output, float speed)
{
  this->recording = &recording;
  this->output = output;
  this->speed = speed;
}

bool ActiveRecording::outputEquals(const String & name) {
  return this->output.equalsIgnoreCase(name);
}

bool ActiveRecording::update() {
  currentTime += 10 * speed;
  int newIndex = recording->getIndexBefore(currentTime);
  if (newIndex > currentIndex) {
    recording->sendToBot(newIndex, output);
  }

  currentIndex = newIndex;
  return !recording->isLastIndex(currentIndex);
}