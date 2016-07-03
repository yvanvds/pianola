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
#include "MuteLookAndFeel.h"
#include "Robots.h"

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
{

  network = new Network(this);
  
 
  // environment
  detailsGroup->setText("Environment");  
  addAndMakeVisible(detailsGroup);

  toggleConnectButton->setButtonText("On/Off");
  toggleConnectButton->addListener(this);
  detailsGroup->addAndMakeVisible(toggleConnectButton);
  toggleConnectButton->setToggleState(true, NotificationType::dontSendNotification);
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

  setSize(720, 500);
  mlaf = new MuteLookAndFeel();
  this->setLookAndFeel(mlaf);

  WindowPtr = this;

  network->connect();
  setIpAddress();
}

void MonitorWindow::addRobotBoxes() {
  // meccanoids
  int offset = 10;

  for (int i = 0; i < Robots().countMeccanoids(); i++) {
    Meccanoid * m = Robots().getMeccanoid(i);
    MeccaBox * box = meccanoids.add(new MeccaBox(m));
    addAndMakeVisible(box);
    box->setBounds(400, offset, 300, 60);
    offset += 70;
  }
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
  g.fillAll(Colour(50, 50, 50));
}

LogBox * MonitorWindow::getLog() {
  return logBox.get();
}

void MonitorWindow::updateRobotGui() {
  for (int i = 0; i < meccanoids.size(); i++) {
    meccanoids[i]->update();
  }
}