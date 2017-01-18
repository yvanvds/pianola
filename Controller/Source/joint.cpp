/*
  ==============================================================================

    joint.cpp
    Created: 3 Jan 2017 3:36:07pm
    Author:  yvan

  ==============================================================================
*/

#include "joint.h"
#include "Utilities.h"

joint::joint() {
  yaw = 0;
  pitch = 0;
  roll = 0;
  dist = 1;
  matrix.setPos(Vec(0, 0, -1));
}

void joint::look(const Vec & at) {
  matrix.z = at;
  dist = matrix.z.normalize();
  matrix.x = Cross(Vec(0, 1, 0), matrix.z);

  if (!dist || !matrix.x.normalize()) {
    matrix.identity();
  }
  else {
    matrix.x *= Matrix3().setRotate(matrix.z, 0);
    matrix.y = Cross(matrix.z, matrix.x);
  }
  matrix.pos = 0;
  this->yaw = -Angle(matrix.z.z, matrix.z.x);
  this->pitch = Asin(matrix.z.y);
}

