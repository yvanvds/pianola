#pragma once
#include "juce_core.h"

enum IDENTITY {
  I_NONE   ,
  I_INVALID,
  I_IGOR   ,
  I_GEORGE ,
  I_ALL    ,
};

IDENTITY toIdentity(const char * str);
juce::String toString(IDENTITY);
bool isValid(IDENTITY i);

enum ROBOT_PART {
  RP_NONE     ,
  RP_INVALID  ,
  RP_SERVO1   ,
  RP_SERVO2   ,
  RP_SERVO3   ,
  RP_SERVO4   ,
  RP_SERVO5   ,
  RP_SERVO6   ,
  RP_SERVO7   ,
  RP_SERVO8   ,
  RP_BEHAVIOUR, // combination of parts
};

ROBOT_PART toRobotPart(const char * str);
juce::String toString(ROBOT_PART);

enum BEHAVIOUR {
  B_NONE   ,
  B_INVALID,
  B_NOD    ,
  B_IDLE   ,
};

BEHAVIOUR toBehaviour(const char * str);
juce::String toString(BEHAVIOUR);