/*
  ==============================================================================

    MeccaBox.h
    Created: 12 Jun 2016 5:56:59pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MECCABOX_H_INCLUDED
#define MECCABOX_H_INCLUDED

#include "JuceHeader.h"
#include "Meccanoid.h"
#include "../../pianola_external/pianola/Enums.h"

class MeccaBox : public Component, private AsyncUpdater, public ButtonListener {
public:
  MeccaBox(Meccanoid * ptr);

  virtual void resized();
  virtual void paint(Graphics & g);

  void update();

  void buttonClicked    (Button * buttonThatWasClicked) override;
  void handleAsyncUpdate(                             ) override;

private:
  ScopedPointer<Drawable> image;
  ScopedPointer<Label> nameLabel;
  ScopedPointer<ImageButton> initButton;

  String name;
  Meccanoid * meccaPtr;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeccaBox);
};



#endif  // OUTPUTBOX_H_INCLUDED
