/*
  ==============================================================================

    LogBox.h
    Created: 4 Jun 2016 8:37:27pm
    Author:  yvan

  ==============================================================================
*/

#ifndef LOGBOX_H_INCLUDED
#define LOGBOX_H_INCLUDED

#include "JuceHeader.h"

class LogBox : public ListBox, private ListBoxModel, private AsyncUpdater {
public:
  LogBox();

  int getNumRows() override;
  void paintListBoxItem(int row, Graphics & g, int width, int height, bool rowIsSelected) override;
  void addMessage(const String & message);
  void addMessage(const OSCMessage & message, int level = 0);
  void addMessage(const OSCBundle & message, int level = 0);
  void addArgument(const OSCArgument & arg, int level);
  void addInvalidPacket(const char *, int dataSize);
  void clear();

  void handleAsyncUpdate() override;

private:
  String getIndentationString(int level);

  StringArray list;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LogBox)
};


#endif  // LOGBOX_H_INCLUDED
