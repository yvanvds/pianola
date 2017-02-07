/*
  ==============================================================================

    BodyPart.cpp
    Created: 12 Dec 2016 6:29:34pm
    Author:  yvan

  ==============================================================================
*/

#include "BodyPart.h"
#include <cmath>


ORN StrToOrn(const String & s) {
  if (s.equalsIgnoreCase("x")) return ORN::X;
  if (s.equalsIgnoreCase("y")) return ORN::Y;
  if (s.equalsIgnoreCase("rot")) return ORN::ROT;
  return ORN::NONE;
}

void BodyPart::init(BODYPART id) {
  _id = id;
  _limitFirstMin = _limitFirstMax = _limitSecondMin = _limitSecondMax = 127;
  _constraintFirstMin = _constraintFirstMax = _constraintSecondMin = _constraintSecondMax = 127;
  _offsetFirst = _offsetSecond = 0;
  _first = _second = ORN::NONE;
}

void BodyPart::readConfig(XmlElement * elm)
{
  XmlElement * child = elm->getFirstChildElement();
  while (child != nullptr) {
    String name = child->getTagName();
    // set servo mapping
    if (name.equalsIgnoreCase("servo")) {
      _first = NONE;
      _second = NONE;
      if (child->hasAttribute("first")) {
        _first = StrToOrn(child->getStringAttribute("first"));
      }
      if (child->hasAttribute("second")) {
        _second = StrToOrn(child->getStringAttribute("second"));
      }
    }

    // set servo reversals
    if (name.equalsIgnoreCase("reverse")) {
      _reverseFirst = false;
      _reverseSecond = false;
      if (child->hasAttribute("first")) {
        _reverseFirst = child->getBoolAttribute("first");
      }
      if (child->hasAttribute("second")) {
        _reverseSecond = child->getBoolAttribute("second");
      }
    }

    // set offset
    if (name.equalsIgnoreCase("offset")) {
      _offsetFirst = 0;
      _offsetSecond = 0;
      if (child->hasAttribute("first")) {
        _offsetFirst = child->getIntAttribute("first");
      }
      if (child->hasAttribute("second")) {
        _offsetSecond = child->getIntAttribute("second");
      }
    }

    if (name.equalsIgnoreCase("firstConstraint")) {
      _constraintFirstMin = _constraintFirstMax = 127;
      if (child->hasAttribute("min")) {
        _constraintFirstMin = abs(child->getIntAttribute("min"));
      }
      if (child->hasAttribute("max")) {
        _constraintFirstMax = abs(child->getIntAttribute("max"));
      }
    }

    if (name.equalsIgnoreCase("secondConstraint")) {
      _constraintSecondMin = _constraintSecondMax = 127;
      if (child->hasAttribute("min")) {
        _constraintSecondMin = abs(child->getIntAttribute("min"));
      }
      if (child->hasAttribute("max")) {
        _constraintSecondMax = abs(child->getIntAttribute("max"));
      }
    }

    if (name.equalsIgnoreCase("firstLimit")) {
      _limitFirstMin = _limitFirstMax = 127;
      if (child->hasAttribute("min")) {
        _limitFirstMin = abs(child->getIntAttribute("min"));
      }
      if (child->hasAttribute("max")) {
        _limitFirstMax = abs(child->getIntAttribute("max"));
      }
    }

    if (name.equalsIgnoreCase("secondLimit")) {
      _limitSecondMin = _limitSecondMax = 127;
      if (child->hasAttribute("min")) {
        _limitSecondMin = abs(child->getIntAttribute("min"));
      }
      if (child->hasAttribute("max")) {
        _limitSecondMax = abs(child->getIntAttribute("max"));
      }
    }


    // get another one
    child = child->getNextElement();
  }
}

void BodyPart::writeOrn(MemoryOutputStream & out, const OSCMessage & message)
{
  out.writeByte((unsigned char)MESSAGE::JOINTROTATE);
  out.writeByte((unsigned char)_id);

  // write first axis
  if (_first != ORN::NONE) {
    int value = message[3 + (int)_first].getInt32();
    value < 0 ? value = 0 : value > 255 ? value = 255 : value;

    if (_reverseFirst) out.writeByte((unsigned char)(255 - value));
    else out.writeByte((unsigned char)(value));
  }
  else out.writeByte(0);
  
  // write second axis
  if (_second != ORN::NONE) {
    int value = message[3 + (int)_second].getInt32();
    value < 0 ? value = 0 : value > 255 ? value = 255 : value;

    if (_reverseSecond) out.writeByte((unsigned char)(255 - value));
    else out.writeByte((unsigned char)(value));
  }
  else out.writeByte(0);

  out.writeFloatBigEndian(message[6].getFloat32());
}

void BodyPart::writeRelOrn(MemoryOutputStream & out, const OSCMessage & message)
{
  out.writeByte((unsigned char)MESSAGE::JOINTRELROTATE);
  out.writeByte((unsigned char)_id);

  // write first axis
  if (_first != ORN::NONE) {
    int value = message[3 + (int)_first].getInt32();
    value < 0 ? value = 0 : value > 255 ? value = 255 : value;

    if (_reverseFirst) out.writeByte((unsigned char)(255 - value));
    else out.writeByte((unsigned char)(value));
  }
  else out.writeByte(0);

  // write second axis
  if (_second != ORN::NONE) {
    int value = message[3 + (int)_second].getInt32();
    value < 0 ? value = 0 : value > 255 ? value = 255 : value;

    if (_reverseSecond) out.writeByte((unsigned char)(255 - value));
    else out.writeByte((unsigned char)(value));
  }
  else out.writeByte(0);

  out.writeFloatBigEndian(message[6].getFloat32());
}

void BodyPart::writeConstraint(MemoryOutputStream & out, const OSCMessage & message)
{
  out.writeByte((unsigned char)MESSAGE::CONSTRAIN);
  out.writeByte((unsigned char)_id);
  out.writeFloatBigEndian(message[3].getFloat32());
}

void BodyPart::writeBrown(MemoryOutputStream & out, const OSCMessage & message)
{
  out.writeByte((unsigned char)MESSAGE::BROWN);
  out.writeByte((unsigned char)_id);
  out.writeByte((unsigned char)message[3].getInt32());
  float test = message[4].getFloat32();
  out.writeFloatBigEndian(test);
}

void BodyPart::writeConstraints(MemoryOutputStream & out) {
  out.writeByte((unsigned char)MESSAGE::SETCONSTRAINTS);
  out.writeByte((unsigned char)_id);
  out.writeByte((unsigned char)_constraintFirstMin);
  out.writeByte((unsigned char)_constraintFirstMax);
  out.writeByte((unsigned char)_constraintSecondMin);
  out.writeByte((unsigned char)_constraintSecondMax);
}

void BodyPart::writeLimits(MemoryOutputStream & out) {
  out.writeByte((unsigned char)MESSAGE::SETLIMITS);
  out.writeByte((unsigned char)_id);
  out.writeByte((unsigned char)_limitFirstMin);
  out.writeByte((unsigned char)_limitFirstMax);
  out.writeByte((unsigned char)_limitSecondMin);
  out.writeByte((unsigned char)_limitSecondMax);
}

void BodyPart::writeOffset(MemoryOutputStream & out)
{
  out.writeByte((unsigned char)MESSAGE::JOINTOFFSET);
  out.writeByte((unsigned char)_id);
  out.writeIntBigEndian(_offsetFirst);
  out.writeIntBigEndian(_offsetSecond);
}
