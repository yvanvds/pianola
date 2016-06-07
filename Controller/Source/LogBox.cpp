/*
  ==============================================================================

    LogBox.cpp
    Created: 4 Jun 2016 8:37:27pm
    Author:  yvan

  ==============================================================================
*/

#include "LogBox.h"

LogBox::LogBox() {
  setModel(this);
}

int LogBox::getNumRows() {
  return list.size();
}

void LogBox::paintListBoxItem(int row, Graphics & g, int width, int height, bool rowIsSelected) {
  ignoreUnused(rowIsSelected);

  if (isPositiveAndBelow(row, list.size())) {
    g.setColour(Colours::black);
    g.drawText(list[row], Rectangle<int>(width, height).reduced(4, 0), Justification::centredLeft, true);
  }
}

void LogBox::addMessage(const String & message) {
  list.add(message);
  triggerAsyncUpdate();
}

void LogBox::addMessage(const OSCMessage & message, int level) {
  list.add(getIndentationString(level)
    + "- osc mesage, address = '"
    + message.getAddressPattern().toString()
    + "', "
    + String(message.size())
    + " argument(s)");

  if (!message.isEmpty()) {
    for (OSCArgument * arg = message.begin(); arg != message.end(); ++arg) {
      addArgument(*arg, level + 1);
    }
  }
  triggerAsyncUpdate();
}

void LogBox::addMessage(const OSCBundle & message, int level) {
  OSCTimeTag timeTag = message.getTimeTag();

  list.add(getIndentationString(level)
    + "- osc bundle, time tag = "
    + timeTag.toTime().toString(true, true, true, true));

  for (OSCBundle::Element * element = message.begin(); element != message.end(); ++element) {
    if (element->isMessage()) {
      addMessage(element->getMessage(), level + 1);
    }
    else if (element->isBundle()) {
      addMessage(element->getBundle(), level + 1);
    }
  }
  triggerAsyncUpdate();
}

void LogBox::addArgument(const OSCArgument & arg, int level) {
  String typeAsString;
  String valueAsString;
  if (arg.isFloat32()) {
    typeAsString = "float32";
    valueAsString = String(arg.getFloat32());
  }
  else if (arg.isInt32()) {
    typeAsString = "int32";
    valueAsString = String(arg.getInt32());
  }
  else if (arg.isString()) {
    typeAsString = "string";
    valueAsString = String(arg.getString());
  }
  else if (arg.isBlob()) {
    typeAsString = "blob";
    const MemoryBlock & blob = arg.getBlob();
    valueAsString = String::fromUTF8((const char*)blob.getData(), blob.getSize());
  }
  else {
    typeAsString = "(unknown)";
    valueAsString = "";
  }

  list.add(getIndentationString(level + 1) + "- " + typeAsString.paddedRight(' ', 12) + valueAsString);
}

void LogBox::addInvalidPacket(const char *, int dataSize) {
  list.add("- (" + String(dataSize) + "bytes with invalid format)");
}

void LogBox::clear() {
  list.clear();
  triggerAsyncUpdate();
}

void LogBox::handleAsyncUpdate() {
  updateContent();
  scrollToEnsureRowIsOnscreen(list.size() - 1);
  repaint();
}

String LogBox::getIndentationString(int level) {
  return String().paddedRight(' ', 2 * level);
}