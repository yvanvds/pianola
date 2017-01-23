/*
  ==============================================================================

    Recording.h
    Created: 22 Jan 2017 5:08:20pm
    Author:  yvan

  ==============================================================================
*/

#ifndef RECORDING_H_INCLUDED
#define RECORDING_H_INCLUDED

#include "Defines.h"
#include <vector>
#include "Frame.h"
#include "Robot.h"

enum FILEPART {
  TIME,
  JOINTS,
  USES,
  END,
};

class Recording {
public:

  bool load(const File & file);
  bool equals(const String & name);
  int getIndexBefore(int time);
  bool isLastIndex(int value);
  void sendToBot(int index, const String name);

private:
  void loadJoints(ScopedPointer<FileInputStream> & source);
  
  String name;
  std::vector<Frame> frames;
};

class ActiveRecording {
public:
  void set(Recording & recording, const String & output, float speed);
  bool outputEquals(const String & name);
  bool update();

private:
  Recording * recording;
  String output;
  float speed;

  int currentIndex = -1;
  float currentTime = 0;
};


#endif  // RECORDING_H_INCLUDED
