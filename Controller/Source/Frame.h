/*
  ==============================================================================

    Frame.h
    Created: 22 Jan 2017 5:55:29pm
    Author:  yvan

  ==============================================================================
*/

#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include "Vector.h"

struct Frame {
  int64 time;

  VecI head, torsoUpper, torsoLower;
  VecI ArmLU, ArmLL, HandL;
  VecI ArmRU, ArmRL, HandR;
  VecI LegLU, LegLL, FootL;
  VecI LegRU, LegRL, FootR;
};



#endif  // FRAME_H_INCLUDED
