/*
  ==============================================================================

    MonitorWindow.h
    Created: 4 Jun 2016 9:07:38pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MONITORWINDOW_H_INCLUDED
#define MONITORWINDOW_H_INCLUDED

#include "JuceHeader.h"
#include "LogBox.h"
#include "Network.h"
#include "MeccaBox.h"
#include "MuteLookAndFeel.h"

class MonitorWindow : public Component, private Button::Listener {
public:

  MonitorWindow();
 ~MonitorWindow();

 void addRobotBoxes();
  void updateRobotGui();

  virtual void paint(Graphics& g) override;
  LogBox * getLog();

  MuteLookAndFeel * getLookAndFeel() { return mlaf.get(); }

private:
  void buttonClicked(Button * b) override;
  void resized      (          ) override;
  void setIpAddress();

  // environment
  ScopedPointer<GroupComponent> detailsGroup       ;
  ScopedPointer<ToggleButton  > toggleConnectButton;
  ScopedPointer<Label         > ipLabel            ;
  ScopedPointer<TextEditor    > ipAddressText      ;
  ScopedPointer<TextButton    > copyIpButton       ;
  ScopedPointer<TextButton    > reloadButton       ;

  // log
  ScopedPointer<GroupComponent> logGroup;
  ScopedPointer<LogBox        > logBox  ;

  // outputs
  OwnedArray<MeccaBox> meccanoids;

  // network
  ScopedPointer<Network> network;

  // looks
  ScopedPointer<MuteLookAndFeel> mlaf;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonitorWindow);
};

// global ptr to window
extern MonitorWindow * WindowPtr;

// helper functions for log screen
void ToLog(const String & message);
void ToLog(const OSCMessage & message);

#endif  // MONITORWINDOW_H_INCLUDED
