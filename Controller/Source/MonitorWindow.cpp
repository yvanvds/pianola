/*
  ==============================================================================

    MonitorWindow.cpp
    Created: 4 Jun 2016 9:07:38pm
    Author:  yvan

  ==============================================================================
*/

#include "MonitorWindow.h"
#include "Network.h"
#include "Defines.h"

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
  , logBox             (new LogBox             )
  , igor               (new OutputBox(I_IGOR  ))
  , george             (new OutputBox(I_GEORGE))
  , network            (new Network  (this    ))
{
 
  // environment
  detailsGroup->setText("Environment");  
  addAndMakeVisible(detailsGroup);

  toggleConnectButton->setButtonText("On/Off");
  toggleConnectButton->addListener(this);
  detailsGroup->addAndMakeVisible(toggleConnectButton);

  ipLabel->setText("Address", dontSendNotification);
  detailsGroup->addAndMakeVisible(ipLabel);

  ipAddressText->setReadOnly(true);
  ipAddressText->setCaretVisible(false);
  setIpAddress();
  detailsGroup->addAndMakeVisible(ipAddressText);

  copyIpButton->setButtonText("Copy");
  detailsGroup->addAndMakeVisible(copyIpButton);

  // log
  logGroup->setText("Log");
  addAndMakeVisible(logGroup);
  logGroup->addAndMakeVisible(logBox);

  // outputs
  addAndMakeVisible(igor);
  addAndMakeVisible(george);


  setSize(720, 500);

  WindowPtr = this;
}

Robot * MonitorWindow::getRobot(IDENTITY i) {
  return network->getRobot(i);
}

MonitorWindow::~MonitorWindow() {
  WindowPtr = nullptr;
}

void MonitorWindow::resized() {
  detailsGroup       ->setBounds( 10, 10, 370, 60);
  toggleConnectButton->setBounds( 10, 20,  70, 30);
  ipLabel            ->setBounds( 90, 20,  50, 30);
  ipAddressText      ->setBounds(150, 20, 140, 30);
  copyIpButton       ->setBounds(300, 20,  50, 30);
  
  logGroup->setBounds(10, 80, 370, 400);
  logBox  ->setBounds(10, 20, 350, 370);

  igor  ->setBounds(400, 10, 300, 60);
  george->setBounds(400, 80, 300, 60);
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
      setIpAddress();
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

  if (b == copyIpButton) {
    SystemClipboard::copyTextToClipboard(ipAddressText->getText());
  }
}

void MonitorWindow::setIpAddress() {
  Array<IPAddress> addr;
  IPAddress::findAllAddresses(addr);
  for (int i = 0; i < addr.size(); i++) {
    // show first address which is not localhost
    if (addr[i].address[0] != 127) {
      String s = addr[i].toString();
      s += ":" + String(OSC_PORT);
      ipAddressText->setText(s);
      return;
    }
  }
  ipAddressText->setText("0.0.0.0");
}

void MonitorWindow::paint(Graphics & g) {
  g.fillAll(Colours::white);
}

LogBox * MonitorWindow::getLog() {
  return logBox.get();
}

void MonitorWindow::updateRobotGui() {
  igor->update();
  george->update();
}