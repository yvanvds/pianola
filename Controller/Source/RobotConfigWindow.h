/*
  ==============================================================================

    RobotConfigWindow.h
    Created: 23 Jun 2016 7:16:51pm
    Author:  yvan

  ==============================================================================
*/

#ifndef ROBOTCONFIGWINDOW_H_INCLUDED
#define ROBOTCONFIGWINDOW_H_INCLUDED

#include "JuceHeader.h"
#include "MuteLookAndFeel.h"
#include "Robot.h"

class RobotConfigWindow : public Component, private Button::Listener {
public:
  RobotConfigWindow(Robot * robot);
 ~RobotConfigWindow();

 

private:
  void buttonClicked(Button * b) override;

  ScopedPointer<GroupComponent> pinGroup;
  ScopedPointer<ToggleButton> pinToggle[10];
  ScopedPointer<TextEditor> pinName[10];

  ScopedPointer<TextButton> okButton;
  ScopedPointer<TextButton> cancelButton;
  Robot * robot;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RobotConfigWindow);
};


#endif  // ROBOTCONFIGWINDOW_H_INCLUDED
