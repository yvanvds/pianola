/*
  ==============================================================================

    Vector.h
    Created: 3 Jan 2017 3:02:40pm
    Author:  yvan

  ==============================================================================
*/

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "Defines.h"

struct Matrix3;

struct Vec2 {
  union {
    struct { float x, y; };
    struct { float c[2]; };
  };

  Vec2() {}
  Vec2(float r) { set(r); }
  Vec2(float x, float y) { set(x, y); }

  Vec2 & set(float r) { x = y = r; return *this; }
  Vec2 & set(float x, float y) { this->x = x; this->y = y; return *this; }

  Vec2 & rotate(float angle);
};

struct VecI {
  float x, y, z;

  VecI() : x(0), y(0), z(0) {}

  void read(ScopedPointer<FileInputStream> & source);
};

struct Vec {
  union {
    struct { float x, y, z; };
    struct { float c[3]; };
  };

  Vec() {}
  Vec(float r) { set(r); }
  Vec(float x, float y, float z) { set(x, y, z); }

  Vec & zero() { x = y = z = 0; return *this; }
  Vec & set(float r) { x = y = z = r; return *this; }
  Vec & set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; return *this; }
  
  float length2() const { return x*x + y*y + z*z; }
  float normalize();
  Vec & mul(const Matrix3 & m);

  Vec& operator/=(float r) { x /= r; y /= r; z /= r; return *this; }
  Vec& operator*=(const Matrix3 &m);
  friend Vec operator-(const Vec &a, const Vec &b) { return Vec(a.x - b.x, a.y - b.y, a.z - b.z); }

  Vec2 xy() const { return Vec2(x, y); }
  Vec2 xz() const { return Vec2(x, z); }
  Vec2 yx() const { return Vec2(y, x); }

  Vec& rotateOnX(float angle);
  Vec& rotateOnY(float angle);
  Vec& rotateOnZ(float angle);
};

Vec Cross(const Vec & a, const Vec & b);

#endif  // VECTOR_H_INCLUDED
