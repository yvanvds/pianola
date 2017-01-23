/*
  ==============================================================================

    Vector.cpp
    Created: 3 Jan 2017 3:02:40pm
    Author:  yvan

  ==============================================================================
*/

#include "Vector.h"
#include "Matrix.h"
#include <math.h>
#include "Utilities.h"

float Vec::normalize() {
  if (float l = length2()) { 
    l = sqrtf(l); 
    (*this) /= l; 
    return l; 
  } 
  return 0;
}

Vec & Vec::mul(const Matrix3 & m)
{
  float _x = x, _y = y, _z = z;
  x = _x*m.x.x + _y*m.y.x + _z*m.z.x;
  y = _x*m.x.y + _y*m.y.y + _z*m.z.y;
  z = _x*m.x.z + _y*m.y.z + _z*m.z.z;
  return *this;
}

  Vec & Vec::operator*=(const Matrix3 & m)
  {
    return mul(m);
  }

  Vec & Vec::rotateOnX(float angle)
  {
    float sin, cos; SinCos(sin, cos, angle);

    y = y * cos - z * sin;
    z = y * sin + z * cos;

    return *this;
  }

  Vec & Vec::rotateOnY(float angle)
  {
    float sin, cos; SinCos(sin, cos, angle);

    x = x * cos - z * sin;
    z = x * sin + z * cos;

    return *this;
  }

  Vec & Vec::rotateOnZ(float angle)
  {
    float sin, cos; SinCos(sin, cos, angle);

    x = x * cos - y * sin;
    y = x * sin + y * cos;

    return *this;
  }

Vec Cross(const Vec & a, const Vec & b) {
  return Vec(a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x);
}

Vec2 & Vec2::rotate(float angle)
{
  float sin, cos; SinCos(sin, cos, angle);
  return set(x*cos - y*sin, x*sin + y*cos);
}

void VecI::read(ScopedPointer<FileInputStream> & source) {
  x = source->readInt();
  y = source->readInt();
  z = source->readInt();
}