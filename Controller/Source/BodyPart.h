/*
  ==============================================================================

    BodyPart.h
    Created: 12 Dec 2016 6:29:34pm
    Author:  yvan

  ==============================================================================
*/

#ifndef BODYPART_H_INCLUDED
#define BODYPART_H_INCLUDED

#include "Defines.h"
#include "../../Shared/Messages.h"

enum ORN {
  X,
  Y,
  ROT,
  NONE,
};

class BodyPart {
public:
  void init(BODYPART id);
  void orn(ORN first, ORN second = ORN::NONE) { _first = first; _second = second; }
  void reverse(bool first, bool second = false) { _reverseFirst = first; _reverseSecond = second; }

  bool valid() { return _id != BODYPART::INVALID; }
  void readConfig(XmlElement * elm);

  void writeOrn(MemoryOutputStream & out, const OSCMessage & message);
  void writeRelOrn(MemoryOutputStream & out, const OSCMessage & message);
  void writeConstraint(MemoryOutputStream & out, const OSCMessage & message);
  void writeBrown(MemoryOutputStream & out, const OSCMessage & message);

  void writeConstraints(MemoryOutputStream & out); // sends on init
  void writeLimits(MemoryOutputStream & out);

private:
  BODYPART _id;
  ORN _first, _second;
  bool _reverseFirst, _reverseSecond;
  unsigned int _constraintFirstMin, _constraintFirstMax, _constraintSecondMin, _constraintSecondMax;
  unsigned int _limitFirstMin, _limitFirstMax, _limitSecondMin, _limitSecondMax;
  int _offsetFirst, _offsetSecond;
};




#endif  // BODYPART_H_INCLUDED
