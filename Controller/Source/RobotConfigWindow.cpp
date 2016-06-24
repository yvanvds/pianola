/*
  ==============================================================================

    RobotConfigWindow.cpp
    Created: 23 Jun 2016 7:16:51pm
    Author:  yvan

  ==============================================================================
*/

#include "RobotConfigWindow.h"
#include "MonitorWindow.h"


RobotConfigWindow::RobotConfigWindow(Robot * robot) {
  pinGroup = new GroupComponent();
  pinGroup->setText("Pin Config");
  addAndMakeVisible(pinGroup);
  pinGroup->setBounds(10, 10, 280, 300);

  for (int i = 0; i < 10; i++) {
    pinToggle[i] = new ToggleButton();
    String s = "pin";
    s += (i + 2);
    pinToggle[i]->setButtonText(s);
    pinGroup->addAndMakeVisible(pinToggle[i]);
    pinToggle[i]->setBounds(10, 20 + 25 * i, 80, 20);

    pinName[i] = new TextEditor();
    pinName[i]->setBounds(100, 20 + 25 * i, 160, 20);
    pinGroup->addAndMakeVisible(pinName[i]);

    // load values
    if (robot != nullptr) {
      
    }
  }

  // ok/cancel
  okButton = new TextButton();
  okButton->setButtonText("OK");
  addAndMakeVisible(okButton);
  okButton->setBounds(260, 320, 30, 20);
  okButton->addListener(this);

  cancelButton = new TextButton();
  cancelButton->setButtonText("Cancel");
  addAndMakeVisible(cancelButton);
  cancelButton->setBounds(200, 320, 50, 20);

  setLookAndFeel(WindowPtr->getLookAndFeel());
  setSize(300, 400);
}

RobotConfigWindow::~RobotConfigWindow() {

}

void RobotConfigWindow::buttonClicked(Button * b) {
  if (b == okButton) {
    if (robot != nullptr) {
      
    }
  }
}