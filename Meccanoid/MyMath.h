#pragma once
#include <stdlib.h>

value struct Vec {
  float x;
  float y;
};

value struct VecI {
  int x;
  int y;
};

// linear interpolation
inline float Lerp(float a, float b, float pos) { return (1 - pos)*a + pos*b; }
Vec Lerp(const Vec & a, const Vec & b, float pos);

// random
inline int RandomI(int min, int max) { return rand() % (max - min) + min; }
inline float RandomF(float min, float max) { return min + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (max - min))); }
