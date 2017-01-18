/*
  ==============================================================================

    Matrix.cpp
    Created: 3 Jan 2017 3:02:28pm
    Author:  yvan

  ==============================================================================
*/

#include "Matrix.h"
#include "Utilities.h"

Matrix & Matrix::setPos(const Vec & pos) {
  this->pos = pos;
  x.set(1, 0, 0);
  y.set(0, 1, 0);
  z.set(0, 0, 1);
  return *this;
}

Matrix & Matrix::identity()
{
  x.set(1, 0, 0);
  y.set(0, 1, 0);
  z.set(0, 0, 1);
  pos.zero();
  return *this;
}

void Matrix::mul(const Matrix3 & m, Matrix & dest) const {
  float x = pos.x, y = pos.y, z = pos.z;
  dest.pos.x = x*m.x.x + y*m.y.x + z*m.z.x;
  dest.pos.y = x*m.x.y + y*m.y.y + z*m.z.y;
  dest.pos.z = x*m.x.z + y*m.y.z + z*m.z.z;
  Matrix3::mul(m, dest.orn());
}

Matrix3 & Matrix3::setRotate(const Vec & axis, float angle)
{
  float s, c; SinCos(s, c, -angle);
  float x = axis.x, 
        y = axis.y, 
        z = axis.z, 
        cc = 1 - c, 
        ccx = cc*x, 
        ccy = cc*y, 
        ccz = cc*z, 
        p, q;
  this->x.x = ccx*x + c; this->y.y = ccy*y + c; this->z.z = ccz*z + c;
  p = x*s;               this->z.y = ccz*y + p; this->y.z = ccy*z - p;
  p = y*s; q = ccx*z;    this->x.z =     q + p; this->z.x =     q - p;
  p = z*s; q = ccx*y;    this->y.x =     q + p; this->x.y =     q - p;
  return *this;
}

void Matrix3::mul(const Matrix3 & m, Matrix3 & dest) const
{
  float x, y, z;
  if (&dest == &m)
  {
    x = m.x.x;  y = m.y.x;  z = m.z.x;
    dest.x.x = x*this->x.x + y*this->x.y + z*this->x.z;
    dest.y.x = x*this->y.x + y*this->y.y + z*this->y.z;
    dest.z.x = x*this->z.x + y*this->z.y + z*this->z.z;

    x = m.x.y;  y = m.y.y;  z = m.z.y;
    dest.x.y = x*this->x.x + y*this->x.y + z*this->x.z;
    dest.y.y = x*this->y.x + y*this->y.y + z*this->y.z;
    dest.z.y = x*this->z.x + y*this->z.y + z*this->z.z;

    x = m.x.z;  y = m.y.z;  z = m.z.z;
    dest.x.z = x*this->x.x + y*this->x.y + z*this->x.z;
    dest.y.z = x*this->y.x + y*this->y.y + z*this->y.z;
    dest.z.z = x*this->z.x + y*this->z.y + z*this->z.z;
  }
  else
  {
    x = this->x.x;  y = this->x.y;  z = this->x.z;
    dest.x.x = x*m.x.x + y*m.y.x + z*m.z.x;
    dest.x.y = x*m.x.y + y*m.y.y + z*m.z.y;
    dest.x.z = x*m.x.z + y*m.y.z + z*m.z.z;

    x = this->y.x;  y = this->y.y;  z = this->y.z;
    dest.y.x = x*m.x.x + y*m.y.x + z*m.z.x;
    dest.y.y = x*m.x.y + y*m.y.y + z*m.z.y;
    dest.y.z = x*m.x.z + y*m.y.z + z*m.z.z;

    x = this->z.x;  y = this->z.y;  z = this->z.z;
    dest.z.x = x*m.x.x + y*m.y.x + z*m.z.x;
    dest.z.y = x*m.x.y + y*m.y.y + z*m.z.y;
    dest.z.z = x*m.x.z + y*m.y.z + z*m.z.z;
  }
}
