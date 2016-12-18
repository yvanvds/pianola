#include "pch.h"
#include "MyMath.h"

Vec Lerp(const Vec & a, const Vec & b, float pos)
{
  Vec result;
  result.x = Lerp(a.x, b.x, pos);
  result.y = Lerp(a.y, b.y, pos);
  return result;
}


