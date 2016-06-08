#pragma once

/*
This enum file is shared between de pianola max external and
the controller application.
*/

#ifdef JUCE_APP_VERSION 
// This is the controller applicatioin
#include "JuceHeader.h"
#else
// This is the pianola max external
#include "juce_core.h"
#endif

enum IDENTITY {
  I_NONE   ,
  I_INVALID,
  I_IGOR   ,
  I_GEORGE ,
  I_ALL    ,
  I_NUM    , // indicates the active number of identities used
};

IDENTITY toIdentity(const juce::String & s);
juce::String toString(IDENTITY);
bool isValid(IDENTITY i);

enum ACTION {
  A_NONE     ,
  A_INVALID  ,
  A_SERVO1   ,
  A_SERVO2   ,
  A_SERVO3   ,
  A_SERVO4   ,
  A_SERVO5   ,
  A_SERVO6   ,
  A_SERVO7   ,
  A_SERVO8   ,
  A_NOD      ,
  A_IDLE     ,
};

ACTION toAction(const juce::String & s);
juce::String toString(ACTION);
