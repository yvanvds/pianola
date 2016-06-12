/*
  ==============================================================================

    outputBox.h
    Created: 12 Jun 2016 5:56:59pm
    Author:  yvan

  ==============================================================================
*/

#ifndef OUTPUTBOX_H_INCLUDED
#define OUTPUTBOX_H_INCLUDED

#include "JuceHeader.h"
#include "Robot.h"
#include "../../pianola_external/pianola/Enums.h"

class OutputBox : public Component, private AsyncUpdater {
public:
  OutputBox(IDENTITY i);

  virtual void resized();
  virtual void paint(Graphics & g);

  void update();

  void handleAsyncUpdate() override;

private:
  ScopedPointer<Drawable> image;
  ScopedPointer<Label> name;

  IDENTITY identity;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputBox);
};



#endif  // OUTPUTBOX_H_INCLUDED
