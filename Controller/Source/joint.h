/*
  ==============================================================================

    joint.h
    Created: 3 Jan 2017 3:36:07pm
    Author:  yvan

  ==============================================================================
*/

#ifndef JOINT_H_INCLUDED
#define JOINT_H_INCLUDED

#include "Matrix.h"

struct joint {
  float yaw, pitch, roll, dist;
  Matrix matrix;

  joint();

  void look(const Vec & at);
};



#endif  // JOINT_H_INCLUDED
