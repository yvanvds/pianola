/*
  ==============================================================================

    MeccaConfigWindow.h
    Created: 23 Jun 2016 7:16:51pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MECCACONFIGWINDOW_H_INCLUDED
#define MECCACONFIGWINDOW_H_INCLUDED

#include "JuceHeader.h"
#include "MuteLookAndFeel.h"
#include "Meccanoid.h"

class MeccaConfigWindow : public Component, private Button::Listener {
public:
  MeccaConfigWindow(Meccanoid * robot);
 ~MeccaConfigWindow();

 

private:
  void buttonClicked(Button * b) override;

  ScopedPointer<GroupComponent> pinGroup;
  ScopedPointer<ToggleButton> pinToggle[10];
  ScopedPointer<TextEditor> pinName[10];

  ScopedPointer<TextButton> okButton;
  ScopedPointer<TextButton> cancelButton;
  Meccanoid * robot;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeccaConfigWindow);
};


#endif  // ROBOTCONFIGWINDOW_H_INCLUDED
