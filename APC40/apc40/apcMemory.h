#pragma once
#include "defines.h"

const int CLIPROWS = 5;
const int CLIPCOLUMNS = 8;


class apcMemory {
public:
  apcMemory();

  void setClipLed(unsigned int x, unsigned int y, CLIP_LED status);
  CLIP_LED getClipLed(unsigned int x, unsigned int y);

private:
  CLIP_LED clipLed[CLIPCOLUMNS][CLIPROWS];
};