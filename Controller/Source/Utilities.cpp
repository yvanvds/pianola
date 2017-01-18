/*
  ==============================================================================

    Utilities.cpp
    Created: 8 Jun 2016 7:26:02pm
    Author:  yvan

  ==============================================================================
*/

#include "Utilities.h"
#include "Defines.h"

void OSCTokenize(Array<String> & tokens, const String & string) {
  tokens.clear();
  if (!string.length()) return;

  String token;
  for (int i = 1; i < string.length(); i++) {
    if (string[i] == '/') {
      tokens.add(token);
      token.clear();
    } else {
      token += string[i];
    }
  }
  tokens.add(token);
}

void SinCos(float & sin, float & cos, float angle)
{
  sin = sinf(angle);
  cos = cosf(angle);
}

  float Angle(float x, float y)
  {
    return atan2f(y, x);
  }

  float Asin(float sin)
  {
    if (sin >= 1) return PID_2;
    if (sin <= -1) return -PID_2;
    return asinf(sin);
  }

  float RadToDeg(float rad)
  {
    return rad*(180/PID);
  }
