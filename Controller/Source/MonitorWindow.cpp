/*
  ==============================================================================

    MonitorWindow.cpp
    Created: 4 Jun 2016 9:07:38pm
    Author:  yvan

  ==============================================================================
*/

#include "MonitorWindow.h"
#include "Network.h"

// global ptr to window
MonitorWindow * WindowPtr = nullptr;

// wrapper functions for easy logging to screen
void ToLog(const String & message) {
  if (WindowPtr) WindowPtr->getLog()->addMessage(message);
}

void ToLog(const OSCMessage & message) {
  if (WindowPtr) WindowPtr->getLog()->addMessage(message);
}

// MonitorWindow class

MonitorWindow::MonitorWindow()
  : detailsGroup       (new GroupComponent)
  , toggleConnectButton(new ToggleButton  )
  , ipLabel            (new Label         )
  , ipAddressText      (new TextEditor    )
  , copyIpButton       (new TextButton    )
  , logGroup           (new GroupComponent)
  , logBox             (new LogBox        )
  , network            (new Network(this) )
{
 
  // environment
  detailsGroup->setText("Environment");  
  addAndMakeVisible(detailsGroup);

  toggleConnectButton->setButtonText("On/Off");
  toggleConnectButton->addListener(this);
  detailsGroup->addAndMakeVisible(toggleConnectButton);

  ipLabel->setText("Address & Port", dontSendNotification);
  detailsGroup->addAndMakeVisible(ipLabel);

  ipAddressText->setReadOnly(true);
  ipAddressText->setCaretVisible(false);
  ipAddressText->setText("0.0.0.0:0000");
  detailsGroup->addAndMakeVisible(ipAddressText);

  copyIpButton->setButtonText("Copy");
  detailsGroup->addAndMakeVisible(copyIpButton);

  // log
  logGroup->setText("Log");
  addAndMakeVisible(logGroup);
  logGroup->addAndMakeVisible(logBox);


  setSize(700, 500);

  WindowPtr = this;
}

MonitorWindow::~MonitorWindow() {
  WindowPtr = nullptr;
}

void MonitorWindow::resized() {
  detailsGroup       ->setBounds( 10, 10, 370, 60);
  toggleConnectButton->setBounds( 10, 20,  70, 30);
  ipLabel            ->setBounds( 90, 20,  90, 30);
  ipAddressText      ->setBounds(190, 20, 100, 30);
  copyIpButton       ->setBounds(300, 20,  50, 30);
  
  logGroup->setBounds(10, 80, 370, 400);
  logBox->setBounds(10, 20, 350, 370);
}

void MonitorWindow::buttonClicked(Button * b) {
  
  if (b == toggleConnectButton) {
    // toggle OSC connection server 

    if (b->getToggleState()) {
      // connect to OSC udp port
      network->connect();
      if (!network->isConnected()) {
        // connect failed
        toggleConnectButton->setToggleState(false, juce::NotificationType::dontSendNotification);
      }
    }
    else {
      // disconnect from OSC udp port
      network->disconnect();
      if (network->isConnected()) {
        // disconnect failed!
        toggleConnectButton->setToggleState(true, juce::NotificationType::dontSendNotification);
      }
    }
    
  }
}

void MonitorWindow::paint(Graphics & g) {
  g.fillAll(Colours::white);
}

LogBox * MonitorWindow::getLog() {
  return logBox.get();
}