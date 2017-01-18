/*
  ==============================================================================

    Utilities.h
    Created: 8 Jun 2016 7:26:02pm
    Author:  yvan

  ==============================================================================
*/

#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "JuceHeader.h"
#include <math.h>

void OSCTokenize(Array<String> & tokens, const String & string);

void SinCos(float & sin, float & cos, float angle);

float Angle(float x, float y);
float Asin(float sin);

float RadToDeg(float value);


#endif  // UTILITIES_H_INCLUDED
