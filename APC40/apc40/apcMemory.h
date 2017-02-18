#pragma once
#include "defines.h"

const int CLIPROWS = 5;
const int CLIPCOLUMNS = 8;

struct clipStatus{
  CLIP_LED current;
  CLIP_MODE mode;
};

class apcMemory {
public:
  apcMemory();

  void setClipLed(unsigned int x, unsigned int y, CLIP_LED status);
  CLIP_LED getClipLed(unsigned int x, unsigned int y);

  bool toggle(unsigned int x, unsigned int y);

  void setClipMode(unsigned int x, unsigned int y, CLIP_MODE mode);
  CLIP_MODE getClipMode(unsigned int x, unsigned int y);

private:
  clipStatus clip[CLIPCOLUMNS][CLIPROWS];
};