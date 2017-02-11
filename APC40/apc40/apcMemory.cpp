#include "apcMemory.h"

apcMemory::apcMemory()
{
  // set lights to off
  for (int i = 0; i < CLIPROWS; i++) {
    for (int j = 0; j < CLIPCOLUMNS; j++) {
      clipLed[j][i] = CL_OFF;
    }
  }
}

void apcMemory::setClipLed(unsigned int x, unsigned int y, CLIP_LED status)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    clipLed[x][y] = status;
  }
}

CLIP_LED apcMemory::getClipLed(unsigned int x, unsigned int y)
{
  if (x < CLIPCOLUMNS && y < CLIPROWS) {
    return clipLed[x][y];
  }
  return CL_INVALID;
}
