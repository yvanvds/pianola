/*
  ==============================================================================

    KinectPlayer.cpp
    Created: 22 Jan 2017 5:09:12pm
    Author:  yvan

  ==============================================================================
*/

#include "KinectPlayer.h"
#include <vector>
#include "MonitorWindow.h"


KinectPlayer::KinectPlayer()
{

}

KinectPlayer::~KinectPlayer()
{
  stopTimer();
}

void KinectPlayer::init() {
  File recordDir = File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
  recordDir = recordDir.getParentDirectory();
  recordDir = recordDir.getChildFile("recordings");

  if (recordDir.isDirectory()) {
    Array<File> files;
    int count = recordDir.findChildFiles(files, File::TypesOfFileToFind::findFiles, false, "*.rot");

    for (int i = 0; i < count; i++) {
      recordings.emplace_back();
      recordings.back().load(files[i]);
    }
  }
  if (!sender.connect("127.0.0.1", OSC_PORT)) {
    ToLog("Error: Kinect cannot connect to osc.");
  }
  startTimer(10);
}

void KinectPlayer::play(const String recording, float speed, const String output) {
  const ScopedWriteLock scopedLock(lock);
  for (int i = 0; i < recordings.size(); i++) {
    if (recordings[i].equals(recording)) {
      // remove current recording for this output
      for (auto it = activeRecordings.begin(); it != activeRecordings.end();) {
        if (it->outputEquals(output)) {
          
          it = activeRecordings.erase(it);
        }
        else {
          ++it;
        }
      }

      // add new recording
      activeRecordings.emplace_back();
      activeRecordings.back().set(recordings[i], output, speed);
      return;
    }
  }
}

String ToString(BODYPART part) {
  switch (part) {
  case BODYPART::HEAD: return "head"; break;
  case BODYPART::TORSO_UPPER: return "torsoUpper"; break;
  case BODYPART::TORSO_LOWER: return "torsoLower"; break;
  case BODYPART::ARMLU: return "armLeftUpper"; break;
  case BODYPART::ARMLL: return "armLeftLower"; break;
  case BODYPART::HANDL: return "handLeft"; break;
  case BODYPART::ARMRU: return "armRightUpper"; break;
  case BODYPART::ARMRL: return "armRightLower"; break;
  case BODYPART::HANDR: return "handRight"; break;
  case BODYPART::LEGLU: return "legLeftUpper"; break;
  case BODYPART::LEGLL: return "legLeftLower"; break;
  case BODYPART::FOOTL: return "footLeft"; break;
  case BODYPART::LEGRU: return "legRightUpper"; break;
  case BODYPART::LEGRL: return "legRightLower"; break;
  case BODYPART::FOOTR: return "footRight"; break;
  }
}

void KinectPlayer::send(const String & output, BODYPART part, const VecI & rot)
{
  sender.send("/kinect", output, String("relrotate"), ToString(part), (int)(127 + rot.x), (int)(127 + rot.y), (int)(127 + rot.z), 10.f);
}



void KinectPlayer::timerCallback()
{
  const ScopedWriteLock scopedLock(lock);
  for (auto it = activeRecordings.begin(); it != activeRecordings.end();) {
    if (!it->update()) {
      it = activeRecordings.erase(it);
    }
    else {
      ++it;
    }
  }
}

KinectPlayer & Player()
{
  static KinectPlayer p;
  return p;
}
