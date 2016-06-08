#include "Enums.h"
#include <ctype.h>

IDENTITY toIdentity(const char * str) {
  juce::String s(str);

  if (s.compareIgnoreCase("none"  ) == 0) return I_NONE  ;
  if (s.compareIgnoreCase("igor"  ) == 0) return I_IGOR  ;
  if (s.compareIgnoreCase("george") == 0) return I_GEORGE;
  if (s.compareIgnoreCase("all"   ) == 0) return I_ALL   ;
  return I_INVALID;
}

juce::String toString(IDENTITY i) {
  switch (i) {
    case I_NONE  : return "none"  ;
    case I_IGOR  : return "igor"  ;
    case I_GEORGE: return "george";
    case I_ALL   : return "all"   ;
    default      : return juce::String();
  }
}

bool isValid(IDENTITY i) {
  return (i != I_NONE && i != I_INVALID);
}

ROBOT_PART toRobotPart(const char * str) {
  juce::String s(str);

  if (s.compareIgnoreCase("none"     ) == 0) return RP_NONE     ;
  if (s.compareIgnoreCase("servo1"   ) == 0) return RP_SERVO1   ;
  if (s.compareIgnoreCase("servo2"   ) == 0) return RP_SERVO2   ;
  if (s.compareIgnoreCase("servo3"   ) == 0) return RP_SERVO3   ;
  if (s.compareIgnoreCase("servo4"   ) == 0) return RP_SERVO4   ;
  if (s.compareIgnoreCase("servo5"   ) == 0) return RP_SERVO5   ;
  if (s.compareIgnoreCase("servo6"   ) == 0) return RP_SERVO6   ;
  if (s.compareIgnoreCase("servo7"   ) == 0) return RP_SERVO7   ;
  if (s.compareIgnoreCase("servo8"   ) == 0) return RP_SERVO8   ;
  if (s.compareIgnoreCase("behaviour") == 0) return RP_BEHAVIOUR;

  return RP_INVALID;
}

juce::String toString(ROBOT_PART p) {
  switch (p) {
    case RP_NONE  : return "none"  ;
    case RP_SERVO1: return "servo1";
    case RP_SERVO2: return "servo2";
    case RP_SERVO3: return "servo3";
    case RP_SERVO4: return "servo4";
    case RP_SERVO5: return "servo5";
    case RP_SERVO6: return "servo6";
    case RP_SERVO7: return "servo7";
    case RP_SERVO8: return "servo8";
    default       : return juce::String();
  }
}

BEHAVIOUR toBehaviour(const char * str) {
  juce::String s(str);

  if (s.compareIgnoreCase("none") == 0) return B_NONE;
  if (s.compareIgnoreCase("nod" ) == 0) return B_NOD ;
  if (s.compareIgnoreCase("idle") == 0) return B_IDLE;

  return B_INVALID;
}

juce::String toString(BEHAVIOUR b) {
  switch (b) {
    case B_NONE: return "none";
    case B_NOD : return "nod" ;
    case B_IDLE: return "idle";
    default    : return juce::String();
  }
}