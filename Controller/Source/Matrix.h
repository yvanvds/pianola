/*
  ==============================================================================

    Matrix.h
    Created: 3 Jan 2017 3:02:28pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "Vector.h"

struct Matrix3 {
  Vec x, y, z;
  Matrix3() {}
  Matrix3& setRotate(const Vec & axis, float angle);

  void mul(const Matrix3 & matrix, Matrix3 &dest) const;
};

struct Matrix : public Matrix3 {
  Vec pos;
  Matrix() {}
  Matrix& setPos(const Vec & pos);
  Matrix& identity();

  Matrix3& orn() { return *this; }
  const Matrix3& orn() const { return *this; }

  void mul(const Matrix3 & matrix, Matrix & dest) const;
  Matrix& mul(const Matrix3 &matrix) { mul(matrix, *this); return *this; }

  Matrix& operator*=(const Matrix3 &m) { return mul(m); }
};



#endif  // MATRIX_H_INCLUDED
