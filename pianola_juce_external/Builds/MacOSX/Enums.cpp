#include "Enums.h"
#include <ctype.h>

IDENTITY toIdentity(const juce::String & s) {
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

ACTION toAction(const juce::String & s) {
  if (s.compareIgnoreCase("none"     ) == 0) return A_NONE     ;
  if (s.compareIgnoreCase("servo1"   ) == 0) return A_SERVO1   ;
  if (s.compareIgnoreCase("servo2"   ) == 0) return A_SERVO2   ;
  if (s.compareIgnoreCase("servo3"   ) == 0) return A_SERVO3   ;
  if (s.compareIgnoreCase("servo4"   ) == 0) return A_SERVO4   ;
  if (s.compareIgnoreCase("servo5"   ) == 0) return A_SERVO5   ;
  if (s.compareIgnoreCase("servo6"   ) == 0) return A_SERVO6   ;
  if (s.compareIgnoreCase("servo7"   ) == 0) return A_SERVO7   ;
  if (s.compareIgnoreCase("servo8"   ) == 0) return A_SERVO8   ;
  if (s.compareIgnoreCase("nod"      ) == 0) return A_NOD      ;
  if (s.compareIgnoreCase("idle"     ) == 0) return A_IDLE     ;
  return A_INVALID;
}

juce::String toString(ACTION a) {
  switch (a) {
    case A_NONE  : return "none"  ;
    case A_SERVO1: return "servo1";
    case A_SERVO2: return "servo2";
    case A_SERVO3: return "servo3";
    case A_SERVO4: return "servo4";
    case A_SERVO5: return "servo5";
    case A_SERVO6: return "servo6";
    case A_SERVO7: return "servo7";
    case A_SERVO8: return "servo8";
    case A_NOD   : return "nod"   ;
    case A_IDLE  : return "idle"  ;
    default       : return juce::String();
  }
}

