#include "apcMemory.h"

apcMemory::apcMemory()
{
  // set lights to off
  for (int i = 0; i < CLIPROWS; i++) {
    for (int j = 0; j < CLIPCOLUMNS; j++) {
      clip[j][i].current = CL_OFF;
      clip[j][i].mode = CM_OFF;
    }
  }
}

void apcMemory::setClipLed(unsigned int x, unsigned int y, CLIP_LED status)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    clip[x][y].current = status;
  }
}

CLIP_LED apcMemory::getClipLed(unsigned int x, unsigned int y)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    return clip[x][y].current;
  }
  return CL_INVALID;
}

bool apcMemory::toggle(unsigned int x, unsigned int y)
{
  if (clip[x][y].mode == CM_TOGGLE_ORANGE_GREEN) {
    if (clip[x][y].current == CL_ORANGE) {
      clip[x][y].current = CL_GREEN;
      return true;
    }
    else {
      clip[x][y].current = CL_ORANGE;
      return false;
    }
  }
  else if (clip[x][y].mode == CM_TOGGLE_ORANGE_RED) {
    if (clip[x][y].current == CL_ORANGE) {
      clip[x][y].current = CL_RED;
      return true;
    }
    else {
      clip[x][y].current = CL_ORANGE;
      return false;
    }
  }
}

void apcMemory::setClipMode(unsigned int x, unsigned int y, CLIP_MODE mode)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    clip[x][y].mode = mode;
    switch (mode) {
      case CM_OFF: clip[x][y].current = CL_OFF; break;
      case CM_SINGLE_ORANGE_GREEN: clip[x][y].current = CL_ORANGE; break;
      case CM_SINGLE_ORANGE_RED: clip[x][y].current = CL_ORANGE; break;
      case CM_TOGGLE_ORANGE_GREEN: clip[x][y].current = CL_ORANGE; break;
      case CM_TOGGLE_ORANGE_RED: clip[x][y].current = CL_ORANGE; break;
    }
  }
}

CLIP_MODE apcMemory::getClipMode(unsigned int x, unsigned int y)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    return clip[x][y].mode;
  }
  return CM_INVALID;
}


