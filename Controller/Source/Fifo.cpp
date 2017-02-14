/*
  ==============================================================================

    Fifo.cpp
    Created: 14 Feb 2017 6:19:58pm
    Author:  yvan

  ==============================================================================
*/

#include "Fifo.h"

Fifo::Fifo() : readPos(0), writePos(0) {}

int Fifo::size()
{
  if(readPos == writePos) return 0;
  if (readPos < writePos) return writePos - readPos;
  else return (128 - readPos) + writePos;
}

MemoryOutputStream * Fifo::getReader()
{
  if(!hasData()) return nullptr;
  return &buffer[readPos];
}

MemoryOutputStream * Fifo::getWriter() {
  // return nullptr when buffer is full
  if (writePos == 127 && readPos == 0) return nullptr;
  if (writePos + 1 == readPos) return nullptr;

  // all ok, return a buffer
  buffer[writePos].reset();
  return &buffer[writePos];
}

void Fifo::readDone()
{
  if (readPos == 127) readPos = 0;
  else readPos++;
}

void Fifo::writeDone() {
  if (writePos == 127) writePos = 0;
  else writePos++;
}


