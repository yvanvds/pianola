/*
  ==============================================================================

    Fifo.h
    Created: 14 Feb 2017 6:19:58pm
    Author:  yvan

  ==============================================================================
*/

#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include "JuceHeader.h"
#include <atomic>

class Fifo{
public:
  Fifo();

  bool hasData() { return readPos != writePos; }
  int size();
  MemoryOutputStream * getReader();
  MemoryOutputStream * getWriter();
  void readDone();
  void writeDone();

private:
  MemoryOutputStream buffer[128];
  std::atomic<int> readPos;
  std::atomic<int> writePos;
};



#endif  // FIFO_H_INCLUDED
